#pragma once
#include <X11/Xlib.h>

#include "Display.hpp"
#include "Character.hpp"

class XWindowBase
{
public:
    XWindowBase(XDisplay &disp, unsigned int width = 200, unsigned int height = 100);
    virtual ~XWindowBase();

    operator Window();
    bool operator==(Window win);

    virtual void show()    {}
    virtual void hide()    {}
    virtual void create()  {}
    virtual void destroy() {}
    virtual void refresh() {}

    virtual void onExpose()                     {}
    virtual void onShow()                       {}
    virtual void onHide()                       {}
    virtual void onLeftClickDown(int x, int y)  {}
    virtual void onRightClickDown(int x, int y) {}
    virtual void onLeftClickUp(int x, int y)    {}
    virtual void onRightClickUp(int x, int y)   {}
    virtual void onMouseEnter(int x, int y)     {}
    virtual void onMouseExit(int x, int y)      {}
    virtual void onMouseMove(int x, int y)      {}
    virtual void onFocus()                      {}
    virtual void onLostFocus()                  {}
    virtual void onKeyPress(XCharacter c)       {}
    virtual void onKeyRelease(XCharacter c)     {}
    virtual void onCreate()                     {}
    virtual void onDestroy()                    {}

private:
    Window _win;
    XDisplay &_disp;
};
