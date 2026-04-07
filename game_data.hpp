#pragma once

// #include "picosystem.hpp"
#include <cstdint>

// using namespace picosystem;

namespace tomd {

const uint32_t QUESTION_COUNT = 153;
const uint32_t HEADWORD_COUNT = 8599;

extern const char *questions[QUESTION_COUNT];

extern const char *headwords[HEADWORD_COUNT];

// rows are the headwords, columns are the questions
extern const int8_t weights[QUESTION_COUNT * HEADWORD_COUNT];

} // namespace tomd
