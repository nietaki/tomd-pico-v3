#include "ui.hpp"
#include "constants.hpp"

using namespace tomd;

namespace ui {

int32_t cur_menu_item_idx = 0;

void centered_text(const std::string_view &t, int32_t y) {
  int32_t w, h;
  measure(t, w, h);
  int32_t x = (SCREEN_WIDTH - w) / 2;
  text(t, x, y);
}

void draw_header(const std::string_view &t) {
  centered_text(t, 1);
  hline(0, 10, SCREEN_WIDTH);
  cursor(1, CONTENT_MIN_Y);
  cur_menu_item_idx = 0;
  return;
}

void draw_menu_item(const std::string_view &t, bool selected) {
  color_t fg = TEXT_COLOR;
  color_t bg = BACKGROUND_COLOR;
  if (selected) {
    std::swap(fg, bg);
  }
  pen(bg);
  int32_t y = CONTENT_MIN_Y + cur_menu_item_idx * MENU_ITEM_HEIGHT;
  frect(0, y, SCREEN_WIDTH, MENU_ITEM_HEIGHT);
  pen(fg);
  text(t, 3, y + 2);
  pen(TEXT_COLOR);
  cur_menu_item_idx++;
}
} // namespace ui
