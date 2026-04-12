#pragma once

#include "game_data.hpp"
// #include "picosystem.hpp"
#include <cstdint>
#include <vector>

namespace tomd {
// enum answer_t { NO = -2, UNLIKELY = -1, IRRELEVANT = 0, LIKELY = 1, YES = 2
// };

struct HistoryItem {
  uint16_t question_idx;
  int8_t answer;
};

struct GameState {
  // sources of truth
  // this should go into main
  // uint16_t current_question_idx;
  int16_t headword_scores[HEADWORD_COUNT];
  std::vector<HistoryItem> history;
  bool question_was_used[QUESTION_COUNT];
  // derived
  // not needed
  // uint16_t headword_ranks[HEADWORD_COUNT];
  uint16_t question_potentials[QUESTION_COUNT];
};

int8_t get_weight(uint16_t question_idx, uint16_t headword_idx);

void init(GameState &state);

// updates the sources of truth and derived state
void user_answered(GameState &state, uint16_t question_idx, int8_t answer);

// TODO generate cutoff values based on a game simulation (or an answer
// analysis)
int16_t get_headword_score_cutoff(const GameState &state);
uint16_t get_best_question_idx(const GameState &state);

uint16_t get_best_headword_idx(const GameState &state);

uint32_t current_question_no(const GameState &state);

} // namespace tomd
