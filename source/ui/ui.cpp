#include "ui.hpp"
#include "button.hpp"
#include "scene_type.hpp"
#include "tabs.hpp"

namespace timerds::ui {
using time::TimerState;
Ui::Ui(Timer &timer, Timer &stopwatch, Tabs tabs, Keypad keypad, Controls controls, Display display, sfx::AudioService &audioService)
    : m_keypad(keypad), m_tabs(tabs), m_controls(controls), m_display(display), m_timer(timer), m_stopwatch(stopwatch), m_audioService(audioService) {
    m_keypad.createSprites();
    m_controls.createSprites();
    m_display.createSprites();

    NF_VramSpriteGfx(1, gfx::buttonSelection.id, m_buttonSelectionId, false);
    NF_CreateSprite(1, m_buttonSelectionId, m_buttonSelectionId, Button::buttonSelectionPalSubId, 0, 0);
    NF_SpriteLayer(1, m_buttonSelectionId, 1);
    NF_ShowSprite(1, m_buttonSelectionId, false);

    NF_VramSpriteGfx(1, gfx::buttonPressed.id, m_buttonPressedId, false);
    NF_CreateSprite(1, m_buttonPressedId, m_buttonPressedId, Button::buttonPressedPalSubId, 0, 0);
    NF_SpriteLayer(1, m_buttonPressedId, 2);
    NF_ShowSprite(1, m_buttonPressedId, false);

    m_controls.buttons[0].setOnPress([this](Button &button){
        Timer &timer = getCurrentTimer();
        switch (timer.getState()) {
            case time::TimerState::RUNNING:
            case time::TimerState::PAUSED:
                timer.pauseToggle();
                break;

            case time::TimerState::DONE:
            case time::TimerState::STOPPED:
                timer.start();
                break;

            default:
                break;
        }
    });
    m_controls.buttons[1].setOnPress([this](auto button){ getCurrentTimer().reset(); });
    
    m_tabs.setOnTabChange([this](Tabs &tabs, Tab oldTab) {
        switch (tabs.getTab()) {
            case Tab::Timer:
                NF_CreateTiledBg(1, 2, "tabs_timer");
                updateScene();
                updateDisplay();
                break;

            case Tab::Stopwatch:
                NF_CreateTiledBg(1, 2, "tabs_stopwatch");
                setScene(SceneType::CONTROLS);
                updateScene();
                updateDisplay();
                break;
        }
    });

    m_timer.setOnStateChange([this](Timer &timer) {
        if (timer.getState() != TimerState::DONE) {
            m_audioService.stopTimerSound();
        } else {
            m_audioService.playTimerSound();
        }
        updateScene();
        updateDisplay(Tab::Timer);
    });

    m_stopwatch.setOnStateChange([this](Timer &stopwatch) {
        updateScene();
        updateDisplay(Tab::Stopwatch);
    });

    m_timer.setOnUpdate([this](Timer &timer) {
        updateDisplay(Tab::Timer);
    });

    m_stopwatch.setOnUpdate([this](Timer &timer) {
        updateDisplay(Tab::Stopwatch);
    });

    showSelection(true);
    setScene(SceneType::KEYPAD);
}

void Ui::handleKeys() {
    scanKeys();
    auto down = keysDown();
    auto held = keysHeld();
    auto up = keysUp();
    touchPosition position = { 0 };
    touchRead(&position);

    if (down & KEY_TOUCH) {
        showSelection(false);
        Scene &scene = getCurrentScene();
        m_tabs.setFromTouch(position);
        for (auto &button : scene.buttons) {
            if (button.isTouching(position)) {
                m_heldButton = &button;
                setHeldButton(*m_heldButton);
                break;
            }
        }
    } else if (m_heldButton != nullptr) {
        if (held & KEY_TOUCH) {
            if (m_heldButton->isTouching(position)) {
                setHeldButton(*m_heldButton);
            } else {
                unsetHeldButton();
            }
        } else if (up & KEY_TOUCH) {
            unsetHeldButton();
            if (m_previousTouchPosition.has_value() && m_heldButton->isTouching(m_previousTouchPosition.value())) {
                m_heldButton->press();
            }
            m_heldButton = nullptr;
        }
    } else {
        if (down & KEY_L) {
            m_tabs.setTab(Tab::Timer);
            return;
        } else if (down & KEY_R) {
            m_tabs.setTab(Tab::Stopwatch);
            return;
        }
        switch (m_currentSceneType) {
            case SceneType::KEYPAD:

                if (down & (KEY_UP | KEY_LEFT | KEY_DOWN | KEY_RIGHT)) {
                    if (m_showSelection) {
                        m_keypad.handleSelection(down);
                    } else {
                        showSelection(true);
                    }
                    updateSelection();
                }

                if (down & KEY_A) {
                    if (m_showSelection) {
                        setHeldButton(*m_keypad.getSelectedButton());
                        m_keypad.getSelectedButton()->press();
                    } else {
                        showSelection(true);
                    }
                } else if (up & KEY_A) {
                    unsetHeldButton();
                } else if (down & KEY_B) {
                    m_timer.removeInput();
                } else if (down & KEY_X) {
                    m_timer.start();
                }

                break;

            case SceneType::CONTROLS:
                if (down & KEY_A) {
                    m_controls.buttons[0].press();
                } else if (down & KEY_B) {
                    m_controls.buttons[1].press();
                }

                break;
        }
    }

    if (held & KEY_TOUCH) {
        m_previousTouchPosition = position;
    } else if (up & KEY_TOUCH) {
        m_previousTouchPosition.reset();
    }
}

void Ui::showSelection(bool show) {
    m_showSelection = show;
    if (getCurrentScene().getSelectedButton() != nullptr) {
        NF_ShowSprite(1, m_buttonSelectionId, show);
    }
}

void Ui::updateSelection() {
    Button *button = getCurrentScene().getSelectedButton();
    if (button == nullptr) {
        NF_ShowSprite(1, m_buttonSelectionId, false);
    } else {
        NF_ShowSprite(1, m_buttonSelectionId, m_showSelection);
        NF_MoveSprite(1, m_buttonSelectionId, button->getX(), button->getY());
    }
}

void Ui::setHeldButton(Button &button) {
    NF_ShowSprite(1, m_buttonPressedId, true);
    NF_MoveSprite(1, m_buttonPressedId, button.getX(), button.getY());
}

void Ui::unsetHeldButton() {
    NF_ShowSprite(1, m_buttonPressedId, false);
}

void Ui::setScene(SceneType scene) {
    if (scene == SceneType::KEYPAD && m_tabs.getTab() == Tab::Stopwatch) {
        return;
    }
    Scene &previous = getCurrentScene();
    m_currentSceneType = scene;
    Scene &current = getCurrentScene();
    previous.showSprites(false);
    current.showSprites(true);
    unsetHeldButton();
    m_heldButton = nullptr;
    updateSelection();
}

void Ui::updateScene() {
    switch (getCurrentTimer().getState()) {
        case TimerState::STOPPED:
            setScene(SceneType::KEYPAD);
            NF_SpriteFrame(1, m_controls.buttons[0].getIconId(), 0);
            break;

        case TimerState::RUNNING:
            setScene(SceneType::CONTROLS);
            NF_SpriteFrame(1, m_controls.buttons[0].getIconId(), 1);
            break;
            
        case TimerState::PAUSED:
            NF_SpriteFrame(1, m_controls.buttons[0].getIconId(), 0);
            break;

        case TimerState::DONE:
            NF_SpriteFrame(1, m_controls.buttons[0].getIconId(), 0);
            break;
    }
}

void Ui::updateDisplay() {
    if (m_tabs.getTab() == Tab::Timer) {
        switch (getCurrentTimer().getState()) {
            case TimerState::STOPPED:
                m_display.showHours(true);
                m_display.showDecimals(false);
                break;

            case TimerState::RUNNING:
            case TimerState::PAUSED:
            case TimerState::DONE: {
                auto time = getCurrentTimer().getDisplayTime();
                m_display.showHours(time[0] != '0' || time[1] != '0');
                m_display.showDecimals(true);
                break;
            }
        }
    } else {
        m_display.showDecimals(true);
        switch (getCurrentTimer().getState()) {
            case TimerState::STOPPED:
            case TimerState::DONE:
                m_display.showHours(false);
                break;

            case TimerState::RUNNING:
            case TimerState::PAUSED: {
                auto time = getCurrentTimer().getDisplayTime();
                m_display.showHours(time[0] != '0' || time[1] != '0');
                break;
            }
        }
    }
}

void Ui::updateDisplay(Tab tab) {
    if (m_tabs.getTab() == tab) {
        updateDisplay();
    }
}

Scene &Ui::getCurrentScene() {
    switch (m_currentSceneType) {
        case SceneType::KEYPAD:
            return m_keypad;

        case SceneType::CONTROLS:
            return m_controls;
    }
}

void Ui::updateTimer() {
    m_display.setTime(getCurrentTimer().getDisplayTime());
}
}
