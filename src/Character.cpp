#include "Character.hpp"
#include <X11/Xlib.h>
#include <X11/keysym.h>

XCharacter::XCharacter(long key, std::string_view text, long state) : _key(key), _text(text.data()), _state(state) {}

bool XCharacter::isDelete() const
{
    return _key == XK_Delete;
}

bool XCharacter::isBackspace() const
{
    return _key == XK_BackSpace;
}

bool XCharacter::isLeftArrow() const
{
    return _key == XK_Left || _key == XK_KP_Left;
}

bool XCharacter::isRightArrow() const
{
    return _key == XK_Right || _key == XK_KP_Right;
}

bool XCharacter::isUpArrow() const
{
    return _key == XK_Up || _key == XK_KP_Up;
}

bool XCharacter::isDownArrow() const
{
    return _key == XK_Down || _key == XK_KP_Down;
}

bool XCharacter::isPrintable() const
{
    return _key >= XK_KP_Space && _key <= XK_KP_9
            || _key >= XK_space && _key <= XK_asciitilde;
}

bool XCharacter::isShiftPressed() const
{
    return _state & ShiftMask;
}

std::string_view XCharacter::getText() const
{
    using namespace std::literals;
    if (!isPrintable()) return ""sv;
    return _text;
}
