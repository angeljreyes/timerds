#pragma once

#include <nds.h>

#include "../time/timer.hpp"
#include "scene.hpp"

namespace timerds::ui {
using time::Timer;

class Controls : public Scene {
public:
    static constexpr u32 gap = 15;

    Controls();

    Button *getSelectedButton() override { return nullptr; }
};
}
