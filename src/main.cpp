#include <thread>

#include <fmt/format.h>

#include "Display.hpp"
#include "Window.hpp"
#include "EventDispatcher.hpp"

int main()
{
    using namespace std::chrono_literals;

    XDisplay disp("");
    XWindowBase win(disp, 1920, 1080);
    EventDispatcher dispatcher(disp);
    dispatcher.registerWindow(&win);
    dispatcher.run();
    
    return 0;
}
