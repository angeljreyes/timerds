#include "keypad.hpp"

namespace timerds::ui {
Keypad::Keypad(Timer &timer) : m_timer(timer)  {
    // Just centering the buttons for a width of 3.
    constexpr u32 startX = (SCREEN_WIDTH / 2) - (Button::width / 2) - gap - Button::width;
    u32 x = startX;
    u32 y = 10;

    buttons.reserve(12);

    for (u32 i = 0; i < buttons.capacity(); i++) {
        const gfx::SpriteGfx *iconGfx;

        switch (i) {
            case 0: iconGfx = &gfx::iconOne; break;
            case 1: iconGfx = &gfx::iconTwo; break;
            case 2: iconGfx = &gfx::iconThree; break;
            case 3: iconGfx = &gfx::iconFour; break;
            case 4: iconGfx = &gfx::iconFive; break;
            case 5: iconGfx = &gfx::iconSix; break;
            case 6: iconGfx = &gfx::iconSeven; break;
            case 7: iconGfx = &gfx::iconEight; break;
            case 8: iconGfx = &gfx::iconNine; break;
            case 9: iconGfx = &gfx::iconPlayPause; break;
            case 10: iconGfx = &gfx::iconZero; break;
            case 11: iconGfx = &gfx::iconBack; break;
            default: iconGfx = nullptr; break;
        }

        buttons.emplace_back(x, y, iconGfx);

        if (i < 9) {
            buttons[i].setOnPress([&timer, i](auto button){ timer.addInput(i + 1); });
        }

        if (i % 3 == 2) {
            x = startX;
            y += Button::height + gap;
        } else {
            x += Button::width + gap;
        }
    }

    buttons[9].setOnPress([&timer](auto button){ timer.start(); });
    buttons[10].setOnPress([&timer](auto button){ timer.addInput(0); });
    buttons[11].setOnPress([&timer](auto button){ timer.removeInput(); });
}

void Keypad::handleSelection(u32 keys) {
    if (keys & KEY_UP && selectedButtonIndex >= 3) {
        selectedButtonIndex -= 3;
    } else if (keys & KEY_DOWN && selectedButtonIndex < (buttons.size() - 3)) {
        selectedButtonIndex += 3;
    } else if (keys & KEY_LEFT && selectedButtonIndex > 0) {
        selectedButtonIndex -= 1;
    } else if (keys & KEY_RIGHT && selectedButtonIndex < (buttons.size() - 1)) {
        selectedButtonIndex += 1;
    }
}
}
