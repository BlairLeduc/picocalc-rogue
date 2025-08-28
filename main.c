#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "hardware/watchdog.h"

#include <drivers/audio.h>
#include <drivers/fat32.h>
#include <drivers/font.h>
#include <drivers/lcd.h>
#include <drivers/southbridge.h>

#include <curses.h>

#include "rogue.h"
#include "config.h"
#include "score.h"


extern int rogue_main(int argc, char **argv, char **envp);
extern bool on_keyboard_timer(repeating_timer_t *rt);
extern repeating_timer_t key_timer;
extern bool PDC_check_key(void);
extern int PDC_get_key(void);
extern void PDC_flushinp(void);
extern char **environ;

static char* argv_restore[] = {
    "rogue",
    "-r"
};

#define MAX_ENV_VARS 16
static char* environment[MAX_ENV_VARS + 1] = {0};

void picocalc_reboot(int status)
{
    watchdog_reboot(0, 0, 0); // Reboot the device
}

void rogue_exit(int status)
{
    lcd_clear_screen();
    picocalc_reboot(status);
}

int main(int argc, char **argv, char **envp)
{
    char buffer[68];
    static char *reason[] = {
        "killed",
        "quit",
        "A total winner",
        "killed with Amulet"
    };

    // Initialise PicoCalc hardware
    sb_init();
    audio_init();
    lcd_init();
    fat32_init();

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
    snprintf(buffer, sizeof(buffer), "Version %s. Port to PicoCalc v%s.", release, PICOCALC_ROGUE_VERSION);
    lcd_putstr((64 - strlen(buffer)) >> 1, 4, buffer);

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
                    (int) (scp - top_ten + 1), scp->sc_score,
                    scp->sc_name, reason[scp->sc_flags],
                    scp->sc_level, killname((char) scp->sc_monster, TRUE));
            }
            else
            {
                snprintf(buffer, sizeof(buffer),
                    "%2d  %5d  %s: %s on level %d.",
                    (int) (scp - top_ten + 1), scp->sc_score,
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

    fat32_file_t file;
    bool found_save = false;
    if (fat32_open(&file, "/Rogue/rogue.save") == FAT32_OK)
    {
        // File opened successfully
        fat32_close(&file);
        found_save = true;
    }

    // New Game | Continue
    int options = 1;
    int selected = 0;

    if (!found_save)
    {
        lcd_set_reverse(true);
    }
    lcd_putstr(26, 25, " New Game ");
    if (!found_save)
    {
        lcd_set_reverse(false);
    }
    if (found_save)
    {
        options++;
        selected = 1;
        lcd_set_reverse(true);
        lcd_putstr(26, 26, " Continue ");
        lcd_set_reverse(false);
    }

    PDC_flushinp();

    int ch = 0;
    do
    {
        ch = PDC_get_key();
        if (ch == 'k' && selected > 0)
        {
            // Move selection up
            lcd_set_reverse(false);
            lcd_putstr(26, 25 + selected, (selected == 0) ? " New Game " : " Continue ");
            selected--;
            lcd_set_reverse(true);
            lcd_putstr(26, 25 + selected, (selected == 0) ? " New Game " : " Continue ");
            lcd_set_reverse(false);
        }
        else if (ch == 'j' && selected < options - 1)
        {
            // Move selection down
            lcd_set_reverse(false);
            lcd_putstr(26, 25 + selected, (selected == 0) ? " New Game " : " Continue ");
            selected++;
            lcd_set_reverse(true);
            lcd_putstr(26, 25 + selected, (selected == 0) ? " New Game " : " Continue ");
            lcd_set_reverse(false);
        }
    } while (ch != '\n' && ch != ' ');

    lcd_enable_cursor(true);

    if (selected == 1)
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
