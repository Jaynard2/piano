#pragma once
#include <string>
#include <string_view>

class XCharacter
{
public:
    XCharacter(long key, std::string_view text, long state);

    bool isDelete() const;
    bool isBackspace() const;
    bool isLeftArrow() const;
    bool isRightArrow() const;
    bool isUpArrow() const;
    bool isDownArrow() const;
    bool isPrintable() const;
    bool isShiftPressed() const;

    std::string_view getText() const;

private:
    long _key;
    std::string _text;
    long _state;

};
