#include "pdcpicocalc.h"

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

    uint8_t col = x;
    uint8_t row = lineno;
    for (int i = 0; i < len; i++)
    {
        lcd_putc(col + i, row, srcp[i] & 0x7F);
    }
}