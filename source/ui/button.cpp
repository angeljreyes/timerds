#include <nf_lib.h>

#include "button.hpp"
#include "../gfx/sprite_gfx.hpp"

namespace timerds::ui {
Button::Button(u32 x, u32 y, const gfx::SpriteGfx *iconGfx)
    : m_iconId(iconGfx == nullptr ?  0 : gfx::getNewGfxVramSubSlot()), m_x(x), m_y(y), m_iconGfx(iconGfx) {}

void Button::createSprite() const {
    NF_VramSpriteGfx(1, gfx::button.id, getButtonId(), true);
    NF_CreateSprite(1, getButtonId(), getButtonId(), buttonPalSubId, getX(), getY());
    NF_SpriteLayer(1, getButtonId(), 3);

    if (m_iconGfx != nullptr) {
        const u32 iconX = getX() + (width / 2) - (m_iconGfx->width / 2);
        const u32 iconY = getY() + (height / 2) - (m_iconGfx->height / 2);
        NF_VramSpriteGfx(1, m_iconGfx->id, getIconId(), true);
        NF_CreateSprite(1, getIconId(), getIconId(), iconPalSubId, iconX, iconY);
        NF_SpriteLayer(1, getIconId(), 1);
    }
}

void Button::showSprite(bool show) const {
    NF_ShowSprite(1, getButtonId(), show);
    if (m_iconGfx != nullptr) {
        NF_ShowSprite(1, getIconId(), show);
    }
}

bool Button::isTouching(touchPosition position) const {
    return
        (position.px >= getX() && position.px < getEndX())
        && (position.py >= getY() && position.py < getEndY());
}

void Button::setHeld(bool isHeld) {
    // NF_SpriteFrame(1, getButtonId(), isHeld ? 2 : 0);
}
}
