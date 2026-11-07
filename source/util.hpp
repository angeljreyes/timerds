#pragma once

#include <print>

#include <nds.h>

namespace timerds {
[[noreturn]] inline void fatalError(const char *message) {
    consoleDemoInit();
    std::println(stderr, "{}", message);
    while (true) {
       swiWaitForVBlank();
    }
}
}
