#include <nf_lib.h>

#include "display.hpp"

namespace timerds::ui {
Display::Display() {
    digits.reserve(10);

    for (u32 i = 0; i < digits.capacity(); i++) {
        digits.emplace_back(0, 0);
    }
}

void Display::createSprites() {
    for (const auto &digit : digits) {
        digit.createSprite();
    }

    NF_SpriteFrame(0, digits[2].getId(), 10); // First colon
    NF_SpriteFrame(0, digits[5].getId(), 10); // Second colon
    NF_SpriteFrame(0, digits[8].getId(), 11); // Period

    showDecimals(false);
    showHours(true);
    setTime("00:00:00.0");
}

void Display::setTime(std::string text) {
    if (m_updatePending) {
        updatePositions();
    }

    for (u32 i = 0; i < digits.size(); i++) {
        if (i == 2 || i == 5 || i == 8) {
            continue;
        }
        char digit = i < text.size() ? text[i] : '0';
        if (digit >= '0' && digit <= '9') {
            digits[i].setNumber(digit - '0');
        }
    }
}

void Display::showDecimals(bool show) {
    if (show != m_showDecimals) {
        m_showDecimals = show;
        m_updatePending = true;
    }
}

void Display::showHours(bool show) {
    if (show != m_showHours) {
        m_showHours = show;
        m_updatePending = true;
    }
}

void Display::updatePositions() {
    m_updatePending = false;

    constexpr u32 gap = 28;
    u32 x = 10;
    constexpr u32 y = (SCREEN_HEIGHT / 2) - 20;

    if (!m_showDecimals) {
        x += 20;
    }

    if (!m_showHours) {
        x -= 40;
    }

    for (u32 i = 0; i < digits.capacity(); i++) {
        digits[i].move(x, y);
        if (i % 3 == 2) {
            x += gap / 2;
        } else {
            x += gap;
        }
    }

    NF_ShowSprite(0, digits[0].getId(), m_showHours);
    NF_ShowSprite(0, digits[1].getId(), m_showHours);
    NF_ShowSprite(0, digits[2].getId(), m_showHours);

    NF_ShowSprite(0, digits[digits.size() - 2].getId(), m_showDecimals);
    NF_ShowSprite(0, digits[digits.size() - 1].getId(), m_showDecimals);
}
}
