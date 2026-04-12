#include "game_state.hpp"
#include "game_data.hpp"
#include <algorithm>
#include <cstdint>
#include <sys/types.h>

namespace tomd {

uint32_t current_question_no(const GameState &state) {
  return (uint32_t)state.history.size() + 1;
}

int8_t get_weight(uint16_t question_idx, uint16_t headword_idx) {
  return weights[headword_idx * QUESTION_COUNT + question_idx];
}

void init(GameState &state) {
  std::fill_n(state.headword_scores, HEADWORD_COUNT, 0);
  std::fill_n(state.question_potentials, QUESTION_COUNT, 0);
  std::fill_n(state.question_was_used, QUESTION_COUNT, false);
  state.history.clear();
  state.history.reserve(40);
}

// let's try max weight value / 2
const int16_t ANSWER_MAGNITUDE = 2;

int16_t get_headword_score_cutoff(const GameState &state) {
  int16_t ret = 0;

  // iterate over `history` and sum the absolute values of answers
  for (const auto &item : state.history) {
    ret += std::abs(item.answer) * ANSWER_MAGNITUDE;
  }

  return ret - 1;
}

void update_question_potential(GameState &state, uint16_t question_idx,
                               int16_t score_cutoff) {
  if (state.question_was_used[question_idx]) {
    state.question_potentials[question_idx] = 0;
    return;
  }

  uint16_t positive_potential = 0;
  uint16_t negative_potential = 0;

  for (uint16_t hw_id = 0; hw_id < HEADWORD_COUNT; hw_id++) {
    if (state.headword_scores[hw_id] >= score_cutoff) {
      int16_t weight = get_weight(question_idx, hw_id);
      if (weight > 0) {
        positive_potential += weight;
      } else {
        negative_potential -= weight;
      }
    }
  }

  state.question_potentials[question_idx] =
      std::min(positive_potential, negative_potential);
}

void user_answered(GameState &state, uint16_t question_idx, int8_t answer) {
  // update history
  state.question_was_used[question_idx] = true;
  state.history.push_back({.question_idx = question_idx, .answer = answer});

  // update headword scores
  for (uint32_t hw_idx = 0; hw_idx < HEADWORD_COUNT; hw_idx++) {
    state.headword_scores[hw_idx] += get_weight(question_idx, hw_idx) * answer;
  }

  // recalculate question potentials
  auto score_cutoff = get_headword_score_cutoff(state);
  for (uint16_t idx = 0; idx < QUESTION_COUNT; idx++) {
    update_question_potential(state, idx, score_cutoff);
  }
}

uint16_t get_best_question_idx(const GameState &state) {
  // if there's no answers yet
  if (state.history.empty()) {
    return QUESTION_COUNT - 4;
  }

  uint16_t best_potential = 0;
  uint16_t best_idx = 0;

  for (uint16_t idx = 0; idx < QUESTION_COUNT; idx++) {
    if (state.question_potentials[idx] > best_potential) {
      best_potential = state.question_potentials[idx];
      best_idx = idx;
    }
  }

  return best_idx;
}

uint16_t get_best_headword_idx(const GameState &state) {
  int16_t best_score = -1000;
  uint16_t best_headword_idx = 0;

  for (uint16_t hw_id = 0; hw_id < HEADWORD_COUNT; hw_id++) {
    if (state.headword_scores[hw_id] > best_score) {
      best_score = state.headword_scores[hw_id];
      best_headword_idx = hw_id;
    }
  }

  return best_headword_idx;
}

} // namespace tomd
