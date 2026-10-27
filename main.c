#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <sys/time.h>

#include "hardware/watchdog.h"
#include "pico/rand.h"

#include <drivers/audio.h>
#include <drivers/fat32.h>
#include <drivers/font.h>
#include <drivers/lcd.h>
#include <drivers/southbridge.h>

#include <curses.h>

#include "rogue.h"
#include "config.h"
#include "score.h"

#if PICO_RP2350
#include "picocalc_shell.h"
#endif

extern int rogue_main(int argc, char **argv, char **envp);
extern bool on_keyboard_timer(repeating_timer_t *rt);
extern repeating_timer_t key_timer;
extern bool PDC_check_key(void);
extern int PDC_get_key(void);
extern void PDC_flushinp(void);
extern char **environ;

static char *argv_restore[] = {
    "rogue",
    "-r"};

static char *power_off_msgs[] = {
    "Nice session!",
    "Play again soon!",
    "Until next time!",
    "Great effort!",
    "Great job!",
    "Goodbye!",
    "That was fun!",
    "You did great!",
    "Continue tomorrow?",
    "Adventure resumes on your return.",
    "Thanks for playing! Continue anytime."};

#define MAX_ENV_VARS 16
static char *environment[MAX_ENV_VARS + 1] = {0};

static char *menu_labels[] = {
    " New Game ",
    " Continue ",
    "   Exit   "};

void picocalc_reboot(int status)
{
    watchdog_reboot(0, 0, 0); // Reboot the device
}

// Whether UF2 Loader can load /BOOT2350.UF2 (the shell or the loader's menu)
static bool loader_available(void)
{
#if !PICO_RP2350
    return false;
#elif PICO_NO_FLASH
    // Running from SRAM, so stage3 loaded us; only the card matters
    return picocalc_shell_card_present();
#else
    return picocalc_shell_loader_present() && picocalc_shell_card_present();
#endif
}

// Reboot into /BOOT2350.UF2; call loader_available() first
static void return_to_loader(void)
{
#if PICO_RP2350
    // As picocalc_shell_exit(), less its check for a program in flash
    watchdog_hw->scratch[1] = PICOCALC_SHELL_BOOT_SD;
    watchdog_hw->scratch[2] = 0;
    watchdog_hw->scratch[0] = PICOCALC_SHELL_LOADER_MAGIC;
    watchdog_reboot(0, 0, 0);
    while (1)
    {
        tight_loop_contents();
    }
#endif
}

// Set the clock from the time the shell keeps, as local time; without it, time() counts from 1970
static void set_clock(void)
{
#ifdef PICOCALC_SHELL_HAS_TIME
    int64_t utc_ms;
    int offset_min;
    if (picocalc_shell_time(&utc_ms, &offset_min))
    {
        struct timeval tv = {.tv_sec = (time_t)(utc_ms / 1000 + offset_min * 60)};
        settimeofday(&tv, NULL);
    }
#endif
}

// Show why the saved game could not be restored, and wait for a key
void rogue_restore_failed(const char *reason)
{
    static const char *prompt = "Your saved game has been kept. Press any key.";

    lcd_enable_cursor(false);
    lcd_set_font(&font_5x10);
    lcd_clear_screen();
    lcd_putstr((64 - strlen(reason)) >> 1, 14, reason);
    lcd_putstr((64 - strlen(prompt)) >> 1, 16, prompt);

    PDC_flushinp();
    PDC_get_key();
}

void rogue_exit(int status)
{
    lcd_enable_cursor(false);
    lcd_clear_screen();

    // Saved or quit: return to the loader, or power off, after time to read the message
    bool to_loader = status && loader_available();
    bool power_off = status && !to_loader && sb_is_power_off_supported();

    if (to_loader || power_off)
    {
        char *msg = power_off_msgs[get_rand_32() % (sizeof(power_off_msgs) / sizeof(char *))];
        lcd_putstr((64 - strlen(msg)) >> 1, 16, msg);
    }

    if (to_loader)
    {
        sleep_ms(5000);
        return_to_loader();
    }

    if (power_off)
    {
        sb_write_power_off_delay(6);
        while (1)
        {
            tight_loop_contents();
        }
    }

#if PICO_NO_FLASH
    // A reboot would start the program in flash, not this one
    if (loader_available())
    {
        return_to_loader();
    }
#endif

    picocalc_reboot(status);
}

int main(int argc, char **argv, char **envp)
{
    char buffer[68];
    static char *reason[] = {
        "killed",
        "quit",
        "A total winner",
        "killed with Amulet"};

    // Initialise PicoCalc hardware
    sb_init();
    audio_init();
    lcd_init();
    fat32_init();
    set_clock();

    // poll every 100 ms for key events
    add_repeating_timer_ms(100, on_keyboard_timer, NULL, &key_timer);

    lcd_enable_cursor(false);
    lcd_set_font(&font_8x10);
    lcd_clear_screen();

    // Show title
    lcd_set_bold(true);
    lcd_putstr(1, 2, "Rogue: Exploring the Dungeons of Doom");
    lcd_set_bold(false);

    // Show version
    lcd_set_font(&font_5x10);
    snprintf(buffer, sizeof(buffer), "Version %s", release);
    lcd_putstr((64 - strlen(buffer)) >> 1, 4, buffer);
    snprintf(buffer, sizeof(buffer), "PicoCalc v%s Port Copyright 2025 Blair Leduc", PICOCALC_ROGUE_VERSION);
    lcd_putstr((64 - strlen(buffer)) >> 1, 5, buffer);

    SCORE *top_ten = (SCORE *)calloc(numscores, sizeof(SCORE));
    if (top_ten)
    {
        // Display top ten scores
        lcd_putstr(24, 8, "Top Ten Scores");
        lcd_putstr(4, 10, "Score");
        lcd_putstr(11, 10, "Name                                                ");

        SCORE *endp = &top_ten[numscores];
        open_score();
        rd_score(top_ten);

        int y = 11;
        for (SCORE *scp = top_ten; scp < endp; scp++)
        {
            if (scp->sc_score == 0)
                break;

            if (scp->sc_flags == 0 || scp->sc_flags == 3)
            {
                snprintf(buffer, sizeof(buffer),
                         "%2d  %5d  %s: %s on level %d by %s.",
                         (int)(scp - top_ten + 1), scp->sc_score,
                         scp->sc_name, reason[scp->sc_flags],
                         scp->sc_level, killname((char)scp->sc_monster, TRUE));
            }
            else
            {
                snprintf(buffer, sizeof(buffer),
                         "%2d  %5d  %s: %s on level %d.",
                         (int)(scp - top_ten + 1), scp->sc_score,
                         scp->sc_name, reason[scp->sc_flags],
                         scp->sc_level);
            }
            lcd_putstr(0, y++, buffer);
        }
        free(top_ten);
    }
    else
    {
        lcd_putstr(14, 8, "Error allocating memory for scores.");
    }

    // Show battery status, bottom corner
    int raw_level = sb_read_battery();
    snprintf(buffer, sizeof(buffer), "Battery: %d%%%s", raw_level & 0x7F, (raw_level & 0x80) ? " (Charging)" : "");
    lcd_putstr(64 - strlen(buffer), 31, buffer);

    strncpy(home, md_gethomedir(), MAXSTR);

    strcpy(file_name, home);
    strcat(file_name, "rogue.save");

    fat32_file_t file;
    bool found_save = false;
    if (fat32_open(&file, file_name) == FAT32_OK)
    {
        // File opened successfully
        fat32_close(&file);
        found_save = true;
    }

    // New Game | Continue | Exit
    int items[3];
    int options = 0;
    items[options++] = 0;
    if (found_save)
    {
        items[options++] = 1;
    }
    if (loader_available())
    {
        items[options++] = 2;
    }
    int selected = found_save ? 1 : 0;

    for (int i = 0; i < options; i++)
    {
        lcd_set_reverse(i == selected);
        lcd_putstr(26, 25 + i, menu_labels[items[i]]);
    }
    lcd_set_reverse(false);

    PDC_flushinp();

    int ch = 0;
    do
    {
        ch = PDC_get_key();
        if (ch == 'k' && selected > 0)
        {
            // Move selection up
            lcd_set_reverse(false);
            lcd_putstr(26, 25 + selected, menu_labels[items[selected]]);
            selected--;
            lcd_set_reverse(true);
            lcd_putstr(26, 25 + selected, menu_labels[items[selected]]);
            lcd_set_reverse(false);
        }
        else if (ch == 'j' && selected < options - 1)
        {
            // Move selection down
            lcd_set_reverse(false);
            lcd_putstr(26, 25 + selected, menu_labels[items[selected]]);
            selected++;
            lcd_set_reverse(true);
            lcd_putstr(26, 25 + selected, menu_labels[items[selected]]);
            lcd_set_reverse(false);
        }
    } while (ch != '\n' && ch != ' ');

    if (items[selected] == 2)
    {
        lcd_clear_screen();
        return_to_loader();
    }

    lcd_enable_cursor(true);

    if (items[selected] == 1)
    {
        // Tell rogue to load the saved game
        argc = 2;
        argv = argv_restore;
    }

    FILE *envFile = fopen("/Rogue/rogue.env", "r");
    if (envFile)
    {
        // read environment variables
        char line[256];
        int pos = 0;
        while (fgets(line, sizeof(line), envFile))
        {
            // ignore the whitespace at the start of the line
            char *trimmed = line;
            while (isspace(*trimmed))
            {
                trimmed++;
            }
            if (strlen(trimmed) == 0 || trimmed[0] == '#' || strchr(trimmed, '=') == NULL)
            {
                continue; // Skip empty lines, comments, and invalid lines
            }

            char *envLine = malloc(strlen(trimmed) + 1);
            if (envLine)
            {
                strcpy(envLine, trimmed);
                environment[pos++] = envLine;
            }
            if (pos >= MAX_ENV_VARS)
            {
                break;
            }
        }
        fclose(envFile);
    }

    environ = environment;

    // Start the original rogue main
    rogue_main(argc, argv, environment);

    // Clean up
    rogue_exit(0);
}
