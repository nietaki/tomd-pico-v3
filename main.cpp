#include "constants.hpp"
#include "game_data.hpp"
#include "game_state.hpp"
#include "picosystem.hpp"
#include "ui.hpp"
#include "utils.hpp"

using namespace picosystem;
using namespace tomd;
using namespace std::literals;

struct {
  uint8_t screen;
  int8_t weight_selection;
  int8_t main_menu_selection;
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
  state.main_menu_selection = 1;
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

void change_weight_selection(int8_t amount) {
  state.weight_selection += amount;
  clamp(state.weight_selection, -2, 2);
}

void change_main_menu_selection(int8_t amount) {
  state.main_menu_selection += amount;
  clamp(state.main_menu_selection, 0, MM_ITEM_COUNT - 1);
  if (state.main_menu_selection == MM_CONTINUE &&
      current_question_no(game_state) == 1) {
    state.main_menu_selection = MM_NEW_GAME;
  }
}

void change_backlight(int8_t amount) {
  state.backlight += amount;
  clamp(state.backlight, 0, 100);
}

void change_screen() { state.screen = (state.screen + 1) % SCREEN_COUNT; }

void record_answer() {
  user_answered(game_state, state.current_question_idx, state.weight_selection);
  update_from_game_state();
  state.weight_selection = 0;
}

void update(uint32_t tick) {
  if (state.screen == SCREEN_GAME) {
    if (pressed(BTN_RIGHT)) {
      change_weight_selection(1);
    }
    if (pressed(BTN_LEFT)) {
      change_weight_selection(-1);
    }

    if (pressed(BTN_CONFIRM)) {
      record_answer();
    }
  }
  if (state.screen == SCREEN_STATS) {
    if (pressed(BTN_UP)) {
      change_backlight(BACKLIGHT_STEP);
    }
    if (pressed(BTN_DOWN)) {
      change_backlight(-BACKLIGHT_STEP);
    }
  }

  if (state.screen == SCREEN_MAIN) {
    if (pressed(BTN_UP)) {
      change_main_menu_selection(-1);
    }
    if (pressed(BTN_DOWN)) {
      change_main_menu_selection(1);
    }
  }
  if (pressed(BTN_SCREEN)) {
    change_screen();
  }
  auto cur_time = time_us();
  state.frame_duration = cur_time - state.last_frame_time;
  state.last_frame_time = cur_time;
}

void draw_main(uint32_t tick) {
  for (uint8_t i = 0; i < MM_ITEM_COUNT; i++) {
    if (i == MM_CONTINUE && current_question_no(game_state) == 1) {
      // skip the continue if there's no game to continue
      continue;
    }
    ui::draw_menu_item(mm_names[i], state.main_menu_selection == i);
  }
}

void draw_game(uint32_t tick) {
  auto question_text = "q"s + str(current_question_no(game_state)) + ":  " +
                       questions[state.current_question_idx];
  text(question_text, SCREEN_WIDTH - 2);
  // text(str((int32_t)state.weight_selection));
  text(" ");
  text("current best guess:");
  text(headwords[state.best_headword_idx]);
  text(" ");
  auto answer_text = get_answer_text(state.weight_selection);
  constexpr int32_t bottom_y = SCREEN_HEIGHT - 9;
  text("<", 1, bottom_y);
  ui::centered_text(answer_text, bottom_y);
  text(">", SCREEN_WIDTH - CHAR_WIDTH, bottom_y);
}

void draw_stats(uint32_t tick) {
  text("battery : "s + str(battery()));
  text("tick : "s + str(tick));
  text("backlight : "s + str((uint32_t)state.backlight));
  text("frame time (us) : "s + str(state.frame_duration));
}

void draw(uint32_t tick) {
  backlight(state.backlight);
  pen(BACKGROUND_COLOR);
  clear();
  pen(TEXT_COLOR);
  ui::draw_header(screen_names[state.screen]);
  switch (state.screen) {
  case SCREEN_MAIN:
    draw_main(tick);
    break;
  case SCREEN_GAME:
    draw_game(tick);
    break;
  case SCREEN_STATS:
    draw_stats(tick);
    break;
  }
}
