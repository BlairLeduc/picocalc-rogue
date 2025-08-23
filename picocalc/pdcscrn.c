#include "pdcpicocalc.h"

#include <pico/bootrom.h>

#include <drivers/font.h>
#include <drivers/fat32.h>
#include <drivers/southbridge.h>
#include <boot/picoboot_constants.h>

void PDC_scr_close(void)
{
    PDC_LOG(("PDC_scr_close() - called\n"));
    rom_reboot(REBOOT2_FLAG_REBOOT_TYPE_NORMAL, 100, 0, 0);
}

int PDC_scr_open(void)
{
    PDC_LOG(("PDC_scr_open() - called\n"));

    sb_init();
    audio_init();
    lcd_init();
    fat32_init();

    lcd_set_font(&font_5x10);

    SP->orig_attr = FALSE;
    SP->audible = TRUE;
    SP->mono = TRUE;
    SP->termattrs = A_UNDERLINE | A_REVERSE | A_BOLD;
    SP->_preserve = FALSE;

    return OK;
}

int PDC_resize_screen(int nlines, int ncols)
{
    PDC_LOG(("PDC_resize_screen() - called. Lines: %d Cols: %d\n",
             nlines, ncols));

    if (ncols > 40)
    {
        lcd_set_font(&font_5x10);
    }
    else
    {
        lcd_set_font(&font_8x10);
    }

    return OK;
}

void PDC_reset_prog_mode(void)
{
    PDC_LOG(("PDC_reset_prog_mode() - called.\n"));
}

void PDC_reset_shell_mode(void)
{
    PDC_LOG(("PDC_reset_shell_mode() - called.\n"));
}

void PDC_restore_screen_mode(int i)
{
}

void PDC_save_screen_mode(int i)
{
}

bool PDC_can_change_color(void)
{
    return FALSE;
}

int PDC_color_content(short color, short *red, short *green, short *blue)
{
    return OK;
}

int PDC_init_color(short color, short red, short green, short blue)
{
    return OK;
}