#include <filesystem.h>

#include "timer_ds.hpp"

using namespace timerds;

void TimerDS::run() {

    // consoleInit(nullptr, 3, BgType_Text4bpp, BgSize_T_256x256, 31, 0, true, true);
    // consoleDemoInit();

    while (true) {
        m_ndsTimerService.update();
        m_ui.handleKeys();
        m_ui.updateTimer();

        NF_SpriteOamSet(0);
        NF_SpriteOamSet(1);

        swiWaitForVBlank();

        oamUpdate(&oamMain);
        oamUpdate(&oamSub);
    }

    exit(0);
}
