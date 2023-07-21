#pragma once
#include <X11/Xlib.h>
#include <string_view>

class XDisplay
{
public:
    XDisplay(std::string_view name);
    ~XDisplay();

    operator Display*();
    operator const Display*() const;

private:
    Display* _display;

};
