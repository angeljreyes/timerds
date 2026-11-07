#pragma once

#include <array>
#include <functional>
#include <nds.h>
#include <optional>

#include "tab.hpp"

namespace timerds::ui {
class Tabs {
private:
    Tab m_currentTab;
    std::function<void(Tabs&, Tab)> m_onTabChange;

public:
    static constexpr u32 height = 21;
    static constexpr u32 width = SCREEN_WIDTH;
    static constexpr std::array<Tab, 2> tabs = { Tab::Timer, Tab::Stopwatch };
    static constexpr u32 tabWidth = width / tabs.size();
    static constexpr u32 startX = 0;
    static constexpr u32 startY = SCREEN_HEIGHT - 1 - height;

    Tabs(Tab initialTab) : m_currentTab(initialTab) {}

    void setTab(Tab newTab) {
        if (m_currentTab == newTab) {
            return;
        }

        Tab oldTab = m_currentTab;
        m_currentTab = newTab;

        if (m_onTabChange != nullptr) {
            m_onTabChange(*this, oldTab);
        }
    }

    Tab getTab() const {
        return m_currentTab;
    }

    std::optional<Tab> getTabTouched(touchPosition position) const {
        for (u32 i = 0; i < tabs.size(); i++) {
            u32 tabStartX = startX + (tabWidth * i);
            u32 tabEndX = tabStartX + tabWidth;
            if ((position.px >= tabStartX && position.px < tabEndX)
                && (position.py >= startY && position.py < startY + height)) {
                return tabs[i];
            }
        }
        return std::nullopt;
    }

    void setFromTouch(touchPosition position) {
        auto tab = getTabTouched(position);
        if (tab.has_value()) {
            setTab(tab.value());
        }
    }

    void setOnTabChange(std::function<void(Tabs&, Tab)> callback) { m_onTabChange = callback; }
};
}
