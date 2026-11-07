#pragma once

#include <nds.h>

#include "../gfx/sprite_gfx.hpp"

namespace timerds::ui {
class Digit {
private:
    const u32 m_id;
    u32 m_x;
    u32 m_y;

public:
    static inline u32 palMainId = gfx::getNewPalVramMainSlot();

    Digit(u32 x, u32 y);

    void createSprite() const;

    void showSprite(bool show) const;

    void setNumber(u32 number) const;
    
    u32 getId() const { return m_id; }

    u32 getX() const { return m_x; }

    u32 getY() const { return m_y; }

    void move(u32 x, u32 y);

    void moveBy(u32 x, u32 y) {
        move(getX() + x, getY() + y);
    }
};
}
