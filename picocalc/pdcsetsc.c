#include "pdcpicocalc.h"

int PDC_curs_set(int visibility)
{
    int ret_vis;

    PDC_LOG(("PDC_curs_set() - called: visibility=%d\n", visibility));

    ret_vis = SP->visibility;
    SP->visibility = visibility;
    lcd_erase_cursor();
    lcd_enable_cursor(visibility > 0);

    return ret_vis;
}
