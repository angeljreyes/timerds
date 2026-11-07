#include <nf_lib.h>

#include "digit.hpp"
#include "../gfx/sprite_gfx.hpp"

namespace timerds::ui {
Digit::Digit(u32 x, u32 y) : m_id(gfx::getNewGfxVramMainSlot()), m_x(x), m_y(y) {}

void Digit::createSprite() const {
    NF_VramSpriteGfx(0, gfx::timerFont.id, getId(), true);
    NF_CreateSprite(0, getId(), getId(), palMainId, getX(), getY());
}

void Digit::showSprite(bool show) const {
    NF_ShowSprite(0, getId(), show);
}

void Digit::setNumber(u32 number) const {
    NF_SpriteFrame(0, getId(), number);
}

void Digit::move(u32 x, u32 y) {
    m_x = x;
    m_y = y;
    NF_MoveSprite(0, getId(), m_x, m_y);
}
}
