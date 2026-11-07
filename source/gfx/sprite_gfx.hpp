#pragma once

#include <nds.h>
#include <nf_lib.h>

namespace timerds::gfx {

inline u32 getNewGfxRamSlot() {
    static u32 current = 0;
    return current++;
}

inline u32 getNewPalRamSlot() {
    static u32 current = 0;
    return current++;
}

inline u32 getNewGfxVramMainSlot() {
    static u32 current = 0;
    return current++;
}

inline u32 getNewPalVramMainSlot() {
    static u32 current = 0;
    return current++;
}

inline u32 getNewGfxVramSubSlot() {
    static u32 current = 0;
    return current++;
}

inline u32 getNewPalVramSubSlot() {
    static u32 current = 0;
    return current++;
}

inline u32 getNewSpriteId() {
    static u32 current = 0;
    return current++;
}

class SpriteGfx {
public:
    const char *file;
    const u32 id;
    const u32 width;
    const u32 height;
    const u32 palette;

    void loadGfx() const { NF_LoadSpriteGfx(file, id, width, height); }
    void loadPal() const { NF_LoadSpritePal(file, palette); }
};

inline const SpriteGfx button = {
    .file = "spr/button",
    .id = getNewGfxRamSlot(),
    .width = 64,
    .height = 32,
    .palette = getNewPalRamSlot()
};

inline const SpriteGfx buttonSelection = {
    .file = "spr/button_selection",
    .id = getNewGfxRamSlot(),
    .width = 64,
    .height = 32,
    .palette = getNewPalRamSlot()
};

inline const SpriteGfx buttonPressed = {
    .file = "spr/button_pressed",
    .id = getNewGfxRamSlot(),
    .width = 64,
    .height = 32,
    .palette = getNewPalRamSlot()
};

inline const SpriteGfx timerFont = {
    .file = "spr/timer_font",
    .id = getNewGfxRamSlot(),
    .width = 32,
    .height = 64,
    .palette = getNewPalRamSlot()
};

inline const SpriteGfx iconZero = {
    .file = "spr/icons/zero",
    .id = getNewGfxRamSlot(),
    .width = 16,
    .height = 32,
    .palette = getNewPalRamSlot()
};

inline const SpriteGfx iconOne = {
    .file = "spr/icons/one",
    .id = getNewGfxRamSlot(),
    .width = 16,
    .height = 32,
    .palette = getNewPalRamSlot()
};

inline const SpriteGfx iconTwo = {
    .file = "spr/icons/two",
    .id = getNewGfxRamSlot(),
    .width = 16,
    .height = 32,
    .palette = getNewPalRamSlot()
};

inline const SpriteGfx iconThree = {
    .file = "spr/icons/three",
    .id = getNewGfxRamSlot(),
    .width = 16,
    .height = 32,
    .palette = getNewPalRamSlot()
};

inline const SpriteGfx iconFour = {
    .file = "spr/icons/four",
    .id = getNewGfxRamSlot(),
    .width = 16,
    .height = 32,
    .palette = getNewPalRamSlot()
};

inline const SpriteGfx iconFive = {
    .file = "spr/icons/five",
    .id = getNewGfxRamSlot(),
    .width = 16,
    .height = 32,
    .palette = getNewPalRamSlot()
};

inline const SpriteGfx iconSix = {
    .file = "spr/icons/six",
    .id = getNewGfxRamSlot(),
    .width = 16,
    .height = 32,
    .palette = getNewPalRamSlot()
};

inline const SpriteGfx iconSeven = {
    .file = "spr/icons/seven",
    .id = getNewGfxRamSlot(),
    .width = 16,
    .height = 32,
    .palette = getNewPalRamSlot()
};

inline const SpriteGfx iconEight = {
    .file = "spr/icons/eight",
    .id = getNewGfxRamSlot(),
    .width = 16,
    .height = 32,
    .palette = getNewPalRamSlot()
};

inline const SpriteGfx iconNine = {
    .file = "spr/icons/nine",
    .id = getNewGfxRamSlot(),
    .width = 16,
    .height = 32,
    .palette = getNewPalRamSlot()
};

inline const SpriteGfx iconPlayPause = {
    .file = "spr/icons/play_pause",
    .id = getNewGfxRamSlot(),
    .width = 32,
    .height = 32,
    .palette = getNewPalRamSlot()
};

inline const SpriteGfx iconReset = {
    .file = "spr/icons/reset",
    .id = getNewGfxRamSlot(),
    .width = 32,
    .height = 32,
    .palette = getNewPalRamSlot()
};

inline const SpriteGfx iconBack = {
    .file = "spr/icons/back",
    .id = getNewGfxRamSlot(),
    .width = 32,
    .height = 32,
    .palette = getNewPalRamSlot()
};
}
