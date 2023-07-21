#include "EventDispatcher.hpp"
#include <algorithm>

#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/Xutil.h>

EventDispatcher::EventDispatcher(XDisplay& disp) : _disp(disp), _windows(), _run(true) {}

void EventDispatcher::registerWindow(XWindowBase *win)
{
    if(std::find(std::begin(_windows), std::end(_windows), win) != std::end(_windows))
        return;

    _windows.push_back(win);
}

void EventDispatcher::unregisterWindow(XWindowBase *win)
{
    std::remove(std::begin(_windows), std::end(_windows), win);
}

void EventDispatcher::run()
{
    XEvent ev;
    while(_run)
    {
        XNextEvent(_disp, &ev);
        auto iter = std::find_if(std::begin(_windows), std::end(_windows), [&ev](auto win) { return *win == ev.xany.window; });
        if(iter != std::end(_windows))
        {
            auto curWin = *iter;
            switch(ev.type)
            {
            case Expose:
                curWin->onExpose();
                break;
            case ButtonPress:
                if(ev.xbutton.button & Button1)
                    curWin->onLeftClickDown(ev.xbutton.x, ev.xbutton.y);
                else if(ev.xbutton.button & Button2)
                    curWin->onRightClickDown(ev.xbutton.x, ev.xbutton.y);
                break;
            case ButtonRelease:
                if(ev.xbutton.button & Button1)
                    curWin->onLeftClickUp(ev.xbutton.x, ev.xbutton.y);
                else if(ev.xbutton.button & Button2)
                    curWin->onRightClickUp(ev.xbutton.x, ev.xbutton.y);
                break;
            case EnterNotify:
                curWin->onMouseEnter(ev.xcrossing.x, ev.xcrossing.y);
                break;
            case LeaveNotify:
                curWin->onMouseExit(ev.xcrossing.x, ev.xcrossing.y);
                break;
            case MotionNotify:
                curWin->onMouseMove(ev.xmotion.x, ev.xmotion.y);
                break;
            case FocusIn:
                curWin->onFocus();
                break;
            case FocusOut:
                curWin->onLostFocus();
                break;
            case KeyPress:
            case KeyRelease:
                {
                    char buff[11];
                    KeySym keysym;
                    XComposeStatus stat;
                    int count = XLookupString(&ev.xkey, buff, 10, &keysym, &stat);
                    buff[count] = 0;
                    if(ev.type == KeyPress)
                        curWin->onKeyPress({keysym, buff, ev.xkey.state});
                    else
                        curWin->onKeyRelease({keysym, buff, ev.xkey.state});
                    break;
                }
            case DestroyNotify:
                curWin->onDestroy();
                break;
            case MapNotify:
                curWin->onShow();
                break;
            case UnmapNotify:
                curWin->onHide();
                break;
            case ClientMessage:
                {
                    Atom a = XInternAtom(_disp, "WM_DELETE_WINDOW", false);
                    if(a == ev.xclient.data.l[0])
                        curWin->destroy();
                    break;
                }
            }
        }
    }
}

void EventDispatcher::stop()
{
    _run = false;
}
