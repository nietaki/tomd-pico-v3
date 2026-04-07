#include "constants.hpp"
#include "game_data.hpp"
#include "picosystem.hpp"
#include "utils.hpp"

using namespace picosystem;
using namespace tomd;

struct {
  uint8_t screen;
  uint8_t weight_selection;
  uint8_t backlight;
  uint32_t last_frame_time;
  uint32_t frame_duration;
} state;

void reset_state() {
  state.screen = SCREEN_MAIN;
  state.weight_selection = 0;
  state.backlight = 50;
}

void init() { reset_state(); }

void change_selection(int8_t amount) {
  state.weight_selection += amount;
  clamp(state.weight_selection, -2, 2);
}

void change_backlight(int8_t amount) {
  state.backlight += amount;
  clamp(state.backlight, 0, 100);
}

void change_screen() {
  // modulo SCREEN_COUNT
  state.screen = (state.screen + 1) % SCREEN_COUNT;
}

void update(uint32_t tick) {
  if (pressed(RIGHT)) {
    change_selection(1);
  }
  if (pressed(LEFT)) {
    change_selection(-1);
  }
  if (pressed(UP)) {
    change_backlight(BACKLIGHT_STEP);
  }
  if (pressed(DOWN)) {
    change_backlight(-BACKLIGHT_STEP);
  }
  if (pressed(Y)) {
    change_screen();
  }
  auto cur_time = time_us();
  state.frame_duration = cur_time - state.last_frame_time;
  state.last_frame_time = cur_time;
}

void draw_main(uint32_t tick) {
  pen(TEXT_COLOR);
  text(questions[0], 1, 1, SCREEN_WIDTH - 2);
}

void draw_stats(uint32_t tick) {
  pen(BOLD_TEXT_COLOR);
  text("STATS\n", 1, 1, SCREEN_WIDTH - 2);
  pen(TEXT_COLOR);
  text("battery :");
  text(str(battery()));

  text("tick :");
  text(str(tick));

  text("backlight :");
  text(str((uint32_t)state.backlight));

  text("frame time (us) :");
  text(str(state.frame_duration));
}

void draw(uint32_t tick) {
  pen(BACKGROUND_COLOR);
  backlight(state.backlight);
  clear();
  switch (state.screen) {
  case SCREEN_MAIN:
    draw_main(tick);
    break;
  case SCREEN_STATS:
    draw_stats(tick);
    break;
  }
}
