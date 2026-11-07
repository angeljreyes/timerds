#pragma once

#include <string>
#include <vector>

#include "digit.hpp"

namespace timerds::ui {
class Display {
private:
    bool m_showDecimals = true;
    bool m_showHours = true;
    bool m_updatePending = true;

    void updatePositions();

public:
    std::vector<Digit> digits;

    Display();

    void createSprites();

    void setTime(std::string text);

    void showDecimals(bool show);

    void showHours(bool show);
};
}
