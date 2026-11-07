#pragma once

#include <nds.h>
#include <maxmod9.h>
#include <optional>

#include "nitrofs/soundbank_info.h"
#include "../util.hpp"

namespace timerds::sfx {
class AudioService {
private:
    static inline bool isConsumed = false;
    std::optional<u32> m_timerSoundHandle = std::nullopt;

    AudioService() = default;

public:
    [[nodiscard]] static AudioService init() {
        if (isConsumed) {
            fatalError("Audio service obtained more than once");
        }

        isConsumed = true;
        mmInitDefault("maxmod/soundbank.bin");
        mmLoadEffect(SFX_ALARM_CLOCK);
        return {};
    }

    AudioService(AudioService &audioService) = delete;

    AudioService operator=(AudioService &audioService) = delete;

    void playTimerSound() {
        m_timerSoundHandle = mmEffect(SFX_ALARM_CLOCK);
    }

    void stopTimerSound() {
        if (m_timerSoundHandle.has_value()) {
            mmEffectCancel(m_timerSoundHandle.value());
        }
    }
};
}
