#include <format>

#include "timer.hpp"
#include "nds_timer_service.hpp"

using namespace std::chrono_literals;

namespace timerds::time {
std::shared_ptr<Timer> Timer::create(TimerMode mode, NdsTimerService &service) {
    auto timer = std::make_shared<Timer>(mode);
    service.addCallback([timer]() {
        if (timer->getState() == TimerState::RUNNING) {
            timer->m_duration += timer->m_mode == TimerMode::TIMER ? -100ms : 100ms;
            if (timer->m_duration <= 0ms) {
                timer->setDone();
            }
            timer->update();
        }
    });
    return timer;
}

std::string Timer::inputToString() {
    if (m_mode == TimerMode::STOPWATCH) {
        return "00:00:00";
    }
    auto seconds = m_input % 100;
    auto minutes = (m_input / 100) % 100;
    auto hours = (m_input / 10000) % 100;
    return std::format("{:02}:{:02}:{:02}", hours, minutes, seconds);
}

std::chrono::milliseconds Timer::inputToDuration() {
    if (m_mode == TimerMode::STOPWATCH) {
        return 0ms;
    }
    auto result = std::chrono::seconds(m_input % 100);
    result += std::chrono::minutes((m_input / 100) % 100);
    result += std::chrono::hours((m_input / 10000) % 100);
    return std::min(result, maxDuration);
}

void Timer::addInput(u8 input) {
    if (m_input > 99999) {
        return;
    }

    if (m_input == 0 && input == 0) {
        return;
    }

    m_input = (m_input * 10) + input;
    update();
}

void Timer::removeInput() {
    if (m_input > 0) {
        m_input /= 10;
    }
    update();
}

void Timer::start() {
    if (m_state != TimerState::STOPPED && m_state != TimerState::DONE) {
        return;
    }

    m_duration = inputToDuration();
    changeState(TimerState::RUNNING);
    update();
}

void Timer::pauseToggle() {
    switch (m_state) {
        case TimerState::RUNNING:
            changeState(TimerState::PAUSED);
            break;

        case TimerState::PAUSED:
            changeState(TimerState::RUNNING);
            break;

        default:
            break;
    }
}

void Timer::reset() {
    if (m_state == TimerState::STOPPED) {
        return;
    }

    changeState(TimerState::STOPPED);
    update();
}

void Timer::setDone() {
    m_duration = 0ms;
    changeState(TimerState::DONE);
    update();
}

void Timer::update() {
    switch (m_state) {
        case TimerState::DONE:
        case TimerState::PAUSED:
        case TimerState::RUNNING:
            m_displayTime = std::format("{:%T}{}", m_duration, m_duration.count());
            break;

        case TimerState::STOPPED:
            m_displayTime = inputToString();
            break;
    }
    if (m_onUpdate != nullptr) {
        m_onUpdate(*this);
    }
}
}
