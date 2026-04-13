#pragma once

#include "picosystem.hpp"

namespace ui {

constexpr int32_t MENU_ITEM_HEIGHT = 11;
constexpr int32_t CONTENT_MIN_Y = 15;

void draw_header(const std::string_view &t);
void centered_text(const std::string_view &t, int32_t y);
void draw_menu_item(const std::string_view &t, bool selected);
} // namespace ui
