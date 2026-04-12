#include "ui.hpp"
#include "constants.hpp"

using namespace tomd;

namespace ui {

void centered_text(const std::string_view &t, int32_t y) {
  int32_t w, h;
  measure(t, w, h);
  int32_t x = (SCREEN_WIDTH - w) / 2;
  text(t, x, y);
}

void draw_header(const std::string_view &t) {
  centered_text(t, 1);
  hline(0, 10, SCREEN_WIDTH);
  cursor(1, 15);
  return;
}
} // namespace ui
