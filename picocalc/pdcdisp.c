#include "pdcpicocalc.h"
#include "rogue.h"

void PDC_gotoyx(int y, int x)
{
    lcd_erase_cursor();
    lcd_move_cursor(x, y);
    lcd_draw_cursor();
}

void PDC_doupdate(void)
{

}

void PDC_transform_line(int lineno, int x, int len, const chtype *srcp)
{
    PDC_LOG(("PDC_transform_line() - called: lineno=%d\n", lineno));

    if (!len)
        return;

    if (len == 1)
    {
        lcd_putc(x, lineno, *srcp & 0x7F);
        return;
    }

    char buffer[NUMCOLS + 1];
    char *bptr = buffer;

    for (int i = 0; i < len && i < NUMCOLS; i++)
    {
       *bptr++ = *srcp++ & 0x7F;
    }
    *bptr = '\0';

    // Now we can use the buffer
    lcd_putstr(x, lineno, buffer);
}