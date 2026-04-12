#include "constants.hpp"
#include "game_data.hpp"
#include "game_state.hpp"
#include "picosystem.hpp"
#include "utils.hpp"

using namespace picosystem;
using namespace tomd;

struct {
  uint8_t screen;
  int8_t weight_selection;
  // game state
  uint16_t current_question_idx;
  uint16_t best_headword_idx;
  // generic
  uint8_t backlight;
  uint32_t last_frame_time;
  uint32_t frame_duration;
} state;

GameState game_state;

void reset_state() {
  state.screen = SCREEN_MAIN;
  state.weight_selection = 0;
  state.backlight = 50;
}

void update_from_game_state() {
  state.current_question_idx = get_best_question_idx(game_state);
  state.best_headword_idx = get_best_headword_idx(game_state);
}

void init() {
  reset_state();
  init(game_state);
  update_from_game_state();
}

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

void record_answer() {
  user_answered(game_state, state.current_question_idx, state.weight_selection);
  update_from_game_state();
  state.weight_selection = 0;
}

void update(uint32_t tick) {
  if (state.screen == SCREEN_MAIN) {
    if (pressed(RIGHT)) {
      change_selection(1);
    }
    if (pressed(LEFT)) {
      change_selection(-1);
    }

    if (pressed(A)) {
      record_answer();
    }
  }
  if (state.screen == SCREEN_STATS) {
    if (pressed(UP)) {
      change_backlight(BACKLIGHT_STEP);
    }
    if (pressed(DOWN)) {
      change_backlight(-BACKLIGHT_STEP);
    }
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
  text(questions[state.current_question_idx], 1, 1, SCREEN_WIDTH - 2);
  // text(str((int32_t)state.weight_selection));
  text(" ");
  text("best guess idx:");
  text(headwords[state.best_headword_idx]);
  text(" ");
  auto answer_text = get_answer_text(state.weight_selection);
  text(answer_text);
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
