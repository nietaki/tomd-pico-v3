#pragma once

#include "picosystem.hpp"

using namespace picosystem;

#include <cstdint>

namespace tomd {
constexpr uint32_t SCREEN_SCALE = 2;
constexpr int32_t SCREEN_WIDTH = 240 / SCREEN_SCALE;
constexpr int32_t SCREEN_HEIGHT = 240 / SCREEN_SCALE;
constexpr int32_t CHAR_WIDTH = 8;

constexpr uint8_t SCREEN_MAIN = 0;
constexpr uint8_t SCREEN_STATS = 1;
constexpr uint8_t SCREEN_COUNT = 2;

extern const char *screen_names[SCREEN_COUNT];

constexpr int8_t BACKLIGHT_STEP = 5;

extern color_t BACKGROUND_COLOR;
extern color_t TEXT_COLOR;

// color_t BOLD_TEXT_COLOR = rgb(15, 15, 14);
} // namespace tomd
