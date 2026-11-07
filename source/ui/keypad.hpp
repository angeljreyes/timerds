#pragma once

#include "../time/timer.hpp"
#include "scene.hpp"

namespace timerds::ui {
using time::Timer;

class Keypad : public Scene {
private:
    Timer &m_timer;

public:
    static constexpr u32 gap = 8;

    Keypad(Timer &timer);

    void handleSelection(u32 keys);
};
}
