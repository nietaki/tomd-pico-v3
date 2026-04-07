#include "game_data.hpp"

namespace tomd {
// QUESTION_COUNT = 5
const char *questions[QUESTION_COUNT] = {
    "Is it a person?", "Is it alive?", "Is it an object?",
    "Is it bigger than a breadbox?", "Is it something you can eat?"};

// QUESTION_COUNT = 1
const char *headwords[HEADWORD_COUNT] = {"frog"};

const int8_t weights[QUESTION_COUNT * HEADWORD_COUNT] = {-2, -1, 0, 1, 2};
} // namespace tomd
