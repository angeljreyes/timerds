#pragma once

#include <functional>
#include <nds.h>

#include "../gfx/sprite_gfx.hpp"

namespace timerds::ui {
class Button {
private:
    const u32 m_buttonId = gfx::getNewGfxVramSubSlot();
    const u32 m_iconId;
    const u32 m_x;
    const u32 m_y;
    const gfx::SpriteGfx *m_iconGfx;

    std::function<void(Button&)> m_onPress = nullptr;

public:
    static constexpr u32 width = 64;
    static constexpr u32 height = 32;
    static inline u32 buttonPalSubId = gfx::getNewPalVramSubSlot();
    static inline u32 buttonSelectionPalSubId = gfx::getNewPalVramSubSlot();
    static inline u32 buttonPressedPalSubId = gfx::getNewPalVramSubSlot();
    static inline u32 iconPalSubId = gfx::getNewPalVramSubSlot();

    Button(u32 x, u32 y, const gfx::SpriteGfx *iconGfx);

    bool isTouching(touchPosition position) const;

    void handleKeys(bool down, bool held, bool up, touchPosition touch);

    void createSprite() const;

    void showSprite(bool show) const;
    
    void setOnPress(std::function<void(Button&)> callback) {
        m_onPress = callback;
    }

    void press() {
        if (m_onPress != nullptr) {
            m_onPress(*this);
        }
    }

    void setHeld(bool isHeld);

    u32 getButtonId() const { return m_buttonId; }

    u32 getIconId() const { return m_iconId; }

    u32 getX() const { return m_x; }

    u32 getY() const { return m_y; }

    u32 getEndX() const { return m_x + width; }

    u32 getEndY() const { return m_y + height; }
};
}
