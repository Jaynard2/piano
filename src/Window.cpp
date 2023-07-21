#include "Window.hpp"

XWindowBase::XWindowBase(XDisplay &disp, unsigned int width, unsigned int height) : _win(XCreateSimpleWindow(disp, DefaultRootWindow((Display*)disp), 0, 0, width, height, 0, 0, 0)), _disp(disp)
{
    XMapWindow(disp, _win);
}

XWindowBase::~XWindowBase()
{
    XDestroyWindow(_disp, _win);
}

XWindowBase::operator Window()
{
    return _win;
}

bool XWindowBase::operator==(Window win)
{
    return win == _win;
}
