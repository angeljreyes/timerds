#pragma once

#include <vector>

#include "button.hpp"

namespace timerds::ui {
class Scene {
protected:
    u32 selectedButtonIndex = 0;

public:
    std::vector<Button> buttons;

    virtual void createSprites() const {
        for (const auto &button : buttons) {
            button.createSprite();
        }
        showSprites(false);
    }

    virtual void showSprites(bool show) const {
        for (const auto &button : buttons) {
            button.showSprite(show);
        }
    }

    virtual Button *getSelectedButton() {
        return &buttons[selectedButtonIndex];
    }
};
}
