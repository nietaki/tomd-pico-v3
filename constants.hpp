#pragma once

#include "picosystem.hpp"

using namespace picosystem;

#include <cstdint>

namespace tomd {
// button aliases
#define BTN_UP (picosystem::UP)
#define BTN_DOWN (picosystem::DOWN)
#define BTN_LEFT (picosystem::LEFT)
#define BTN_RIGHT (picosystem::RIGHT)

// main buttons
#define BTN_CONFIRM (picosystem::A)
#define BTN_BACK (picosystem::B)

// extra buttons
#define BTN_SCREEN (picosystem::X)
#define BTN_DEBUG (picosystem::Y)

// screen properties
constexpr uint32_t SCREEN_SCALE = 2;
constexpr int32_t SCREEN_WIDTH = 240 / SCREEN_SCALE;
constexpr int32_t SCREEN_HEIGHT = 240 / SCREEN_SCALE;
constexpr int32_t CHAR_WIDTH = 8;

// screen (as in "section of the UI") info
constexpr uint8_t SCREEN_MAIN = 0;
constexpr uint8_t SCREEN_GAME = 1;
constexpr uint8_t SCREEN_STATS = 2;
constexpr uint8_t SCREEN_COUNT = 3;

extern const char *screen_names[SCREEN_COUNT];

// main menu

constexpr uint8_t MM_CONTINUE = 0;
constexpr uint8_t MM_NEW_GAME = 1;
constexpr uint8_t MM_SETTINGS = 2;
constexpr uint8_t MM_STATS = 3;
constexpr uint8_t MM_ITEM_COUNT = 4;

extern const char *mm_names[MM_ITEM_COUNT];

// configuration
constexpr int8_t BACKLIGHT_STEP = 5;

extern color_t BACKGROUND_COLOR;
extern color_t TEXT_COLOR;
} // namespace tomd
