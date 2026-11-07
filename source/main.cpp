#include <nds.h>
#include <filesystem.h>
#include <nf_lib.h>
#include <maxmod9.h>

#include "time/nds_timer_service.hpp"
#include "timer_ds.hpp"
#include "ui/tabs.hpp"

using namespace timerds;


int main(int argc, char **argv) {
    NF_Set2D(0, 0);
    NF_Set2D(1, 0);

    if (!nitroFSInit(nullptr))
    {
        fatalError("NitroFS init error");
    }

    NF_SetRootFolder("NITROFS");

    NF_Set2D(0, 0);
    NF_Set2D(1, 0);

    NF_InitTiledBgBuffers();
    NF_InitTiledBgSys(0);
    NF_InitTiledBgSys(1);

    NF_InitSpriteBuffers();
    NF_InitSpriteSys(0);
    NF_InitSpriteSys(1);

    NF_LoadTiledBg("bg/background", "bg", 256, 256);
    NF_LoadTiledBg("bg/tabs_timer", "tabs_timer", 256, 256);
    NF_LoadTiledBg("bg/tabs_stopwatch", "tabs_stopwatch", 256, 256);

    gfx::timerFont.loadGfx();
    gfx::timerFont.loadPal();

    gfx::button.loadGfx();
    gfx::button.loadPal();
    gfx::buttonSelection.loadGfx();
    gfx::buttonSelection.loadPal();
    gfx::buttonPressed.loadGfx();
    gfx::buttonPressed.loadPal();

    // They are all the same color so we might as well only load
    // and use one palette.
    gfx::iconOne.loadPal();
    gfx::iconOne.loadGfx();
    gfx::iconTwo.loadGfx();
    gfx::iconThree.loadGfx();
    gfx::iconFour.loadGfx();
    gfx::iconFive.loadGfx();
    gfx::iconSix.loadGfx();
    gfx::iconSeven.loadGfx();
    gfx::iconEight.loadGfx();
    gfx::iconNine.loadGfx();
    gfx::iconZero.loadGfx();
    gfx::iconPlayPause.loadGfx();
    gfx::iconBack.loadGfx();
    gfx::iconReset.loadGfx();

    NF_CreateTiledBg(0, 3, "bg");
    NF_CreateTiledBg(1, 3, "bg");
    NF_CreateTiledBg(1, 2, "tabs_timer");

    NF_VramSpritePal(0, gfx::timerFont.id, ui::Digit::palMainId);
    NF_VramSpritePal(1, gfx::button.id, ui::Button::buttonPalSubId);
    NF_VramSpritePal(1, gfx::buttonSelection.id, ui::Button::buttonSelectionPalSubId);
    NF_VramSpritePal(1, gfx::buttonPressed.id, ui::Button::buttonPressedPalSubId);
    NF_VramSpritePal(1, gfx::iconOne.id, ui::Button::iconPalSubId);

    auto ndsTimerService = time::NdsTimerService::create();
    auto timer = time::Timer::create(time::TimerMode::TIMER, ndsTimerService);
    auto stopwatch = time::Timer::create(time::TimerMode::STOPWATCH, ndsTimerService);
    auto audioService = sfx::AudioService::init();
    ui::Ui ui(*timer, *stopwatch, ui::Tabs(ui::Tab::Timer), ui::Keypad(*timer), ui::Controls(), ui::Display(), audioService);

    TimerDS app(ui, ndsTimerService);

    app.run();
}
