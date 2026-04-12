#pragma once

#include "picosystem.hpp"

using namespace picosystem;

#include <cstdint>

namespace tomd {
constexpr uint32_t SCREEN_SCALE = 2;
constexpr int32_t SCREEN_WIDTH = 240 / SCREEN_SCALE;
constexpr int32_t SCREEN_HEIGHT = 240 / SCREEN_SCALE;

constexpr uint8_t SCREEN_MAIN = 0;
constexpr uint8_t SCREEN_STATS = 1;
constexpr uint8_t SCREEN_COUNT = 2;

constexpr int8_t BACKLIGHT_STEP = 5;

color_t BACKGROUND_COLOR = rgb(0, 0, 0);
color_t TEXT_COLOR = rgb(14, 14, 13);
color_t BOLD_TEXT_COLOR = rgb(15, 15, 14);
color_t INACTIVE_COLOR = rgb(6, 5, 5);
} // namespace tomd
