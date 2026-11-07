#pragma once

#include <chrono>
#include <functional>

#include <nds.h>
#include <string>

#include "nds_timer_service.hpp"
#include "timer_mode.hpp"
#include "timer_state.hpp"

namespace timerds::time {
using namespace std::chrono_literals;

class Timer {
private:
    static constexpr auto maxDuration = 99h + 59min + 59s;

    const TimerMode m_mode;
    std::chrono::milliseconds m_duration{};
    u32 m_input = 0;
    TimerState m_state = TimerState::STOPPED;
    std::string m_displayTime = "00:00:00";
    std::function<void(Timer&)> m_onStateChange;
    std::function<void(Timer&)> m_onUpdate;


    // Timer(Timer &_) = delete;

    // Timer operator=(Timer &_) = delete;

    Timer(Timer &&timer) = default;

    std::string inputToString();

    std::chrono::milliseconds inputToDuration();

    void changeState(TimerState newState) {
        m_state = newState;
        if (m_onStateChange != nullptr) {
            m_onStateChange(*this);
        }
    }

    void setDisplayTime(std::string value) {
    }

public:
    static std::shared_ptr<Timer> create(TimerMode mode, NdsTimerService &service);

    Timer(TimerMode mode) : m_mode(mode) {}

    void addInput(u8 input);

    void removeInput();

    TimerState getState() const { return m_state; }

    void start();

    void pauseToggle();

    void reset();

    void setDone();

    void setOnStateChange(std::function<void(Timer&)> callback) { m_onStateChange = callback; }

    void setOnUpdate(std::function<void(Timer&)> callback) { m_onUpdate = callback; }

    std::string getDisplayTime() { return m_displayTime; }

    void update();
};
}
