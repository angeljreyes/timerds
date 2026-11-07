#pragma once

#include "time/nds_timer_service.hpp"
#include "ui/ui.hpp"

namespace timerds {
class TimerDS {
private:
    ui::Ui &m_ui;
    time::NdsTimerService &m_ndsTimerService;

    TimerDS() = delete;

public:
    explicit TimerDS(ui::Ui &ui, time::NdsTimerService &ndsTimerService)
        : m_ui(ui), m_ndsTimerService(ndsTimerService) {}

    [[noreturn]] void run();
};
}
