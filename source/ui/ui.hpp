#pragma once

#include <optional>

#include "display.hpp"
#include "keypad.hpp"
#include "controls.hpp"
#include "scene_type.hpp"
#include "../sfx/audio_service.hpp"
#include "tab.hpp"
#include "tabs.hpp"

namespace timerds::ui {
class Ui {
private:
    Tabs m_tabs;
    Keypad m_keypad;
    Controls m_controls;
    Display m_display;
    Timer &m_timer;
    Timer &m_stopwatch;
    sfx::AudioService &m_audioService;

    Button *m_heldButton = nullptr;
    bool m_showSelection;
    u32 m_buttonSelectionId = gfx::getNewGfxVramSubSlot();
    u32 m_buttonPressedId = gfx::getNewGfxVramSubSlot();
    std::optional<touchPosition> m_previousTouchPosition;
    SceneType m_currentSceneType = SceneType::KEYPAD;

public:
    Ui(Timer &timer, Timer &stopwatch, Tabs tabs, Keypad keypad, Controls controls, Display display, sfx::AudioService &audioService);

    void showSelection(bool show);

    void updateSelection();

    void setHeldButton(Button &button);

    void unsetHeldButton();

    void handleKeys();

    void setScene(SceneType scene);

    void updateScene();

    void updateDisplay();

    void updateDisplay(Tab tab);

    Scene& getCurrentScene();

    Timer &getCurrentTimer() {
        switch (m_tabs.getTab()) {
            case Tab::Timer:
                return m_timer;

            case Tab::Stopwatch:
                return m_stopwatch;
        }
    }

    void updateTimer();
};
}
