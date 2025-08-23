#include <stdio.h>

#include <drivers/audio.h>
#include <drivers/fat32.h>
#include <drivers/font.h>
#include <drivers/lcd.h>
#include <drivers/southbridge.h>

#include <pico/bootrom.h>
#include <boot/picoboot_constants.h>

#include <curses.h>

#include "rogue.h"
#include "config.h"

extern int rogue_main(int argc, char **argv, char **envp);

static char* argv_restore[] = {
    "rogue",
    "-r"
};

static char* environment[] = {};

int main(int argc, char **argv, char **envp)
{
    sb_init();
    audio_init();
    lcd_init();
    fat32_init();

    lcd_set_font(&font_5x10);

    fat32_file_t file;
    if (fat32_open(&file, "/Rogue/rogue.save") == FAT32_OK)
    {
        // File opened successfully
        fat32_close(&file);
        argc = 2;
        argv = argv_restore;
    }

    rogue_main(argc, argv, environment);
    rom_reboot(REBOOT2_FLAG_REBOOT_TYPE_NORMAL, 100, 0, 0);
}

void rogue_exit(int status)
{
    // Perform any necessary cleanup here
    msg("Turn off the PicoCalc now.");
    while (1)
    {
       tight_loop_contents();
    }
}