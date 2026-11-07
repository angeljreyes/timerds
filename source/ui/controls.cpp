#include "controls.hpp"

namespace timerds::ui {
Controls::Controls() {
    constexpr u32 x = (SCREEN_WIDTH / 2) - (Button::width / 2);
    constexpr u32 y = 40;

    buttons.reserve(2);

    buttons.emplace_back(x, y, &gfx::iconPlayPause);
    buttons.emplace_back(x, y + Button::height + gap, &gfx::iconReset);
}
}
