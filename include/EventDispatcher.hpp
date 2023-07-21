#pragma once
#include <list>

#include "Window.hpp"
#include "Display.hpp"

class EventDispatcher
{
public:
    EventDispatcher(XDisplay& disp);

    void registerWindow(XWindowBase* win);
    void unregisterWindow(XWindowBase* win);

    void run();
    void stop();

private:
    XDisplay& _disp;
    std::list<XWindowBase*> _windows;
    bool _run;

};
