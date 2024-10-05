#include <ApoFrame.h>

ApoFrame::ApoFrame()
{
}

void ApoFrame::render()
{
}

void ApoFrame::set_position(int &x, int &y)
{
    _x = x;
    _y = y;
}

void ApoFrame::set_size(int &w, int &h)
{
    _w = w;
    _h = h;
}
