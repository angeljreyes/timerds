#pragma once

#include "../util.hpp"
#include <functional>
#include <vector>

namespace timerds::time {
class NdsTimerService {
private:
    static inline volatile bool updateTimerFlag = false;
    static inline bool isConsumed = false;

    std::vector<std::function<void()>> m_callbacks{};

    NdsTimerService() = default;

    NdsTimerService(NdsTimerService &_) = delete;

    NdsTimerService operator=(NdsTimerService &_) = delete;

public:
    [[nodiscard]] static NdsTimerService create() {
        if (isConsumed) {
            fatalError("Timer service is already initialized");
        }

        isConsumed = true;
        timerStart(0, ClockDivider_256, timerFreqToTicks_256(10), []() { updateTimerFlag = true; });
        return {};
    }

    void addCallback(std::function<void()> callback) { m_callbacks.push_back(callback); }

    bool update() {
        if (!updateTimerFlag) {
            return false;
        }
        updateTimerFlag = false;
        for (auto callback : m_callbacks) {
            if (callback != nullptr) {
                callback();
            }
        }
        return true;
    }
};
}
