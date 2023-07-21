#include "Display.hpp"
#include <stdexcept>

#include <fmt/format.h>

XDisplay::XDisplay(std::string_view name) : _display(XOpenDisplay(name.data()))
{
    if(!_display)
        throw std::runtime_error(fmt::format("Failed to get display {}", name));
}

XDisplay::~XDisplay()
{
    XCloseDisplay(_display);
}

XDisplay::operator Display *()
{
    return _display;
    _display = nullptr;
}

XDisplay::operator const Display *() const
{
    return (const Display*)_display;
}
