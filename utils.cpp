#include "utils.hpp"
#include <cstdint>

namespace tomd {

const char *answer_texts[5] = {"no", "unlikely", "irrelevant / IDK", "likely",
                               "yes"};

void clamp(uint32_t &value, int32_t min, int32_t max) {
  if (value < min)
    value = min;
  if (value > max)
    value = max;
}

void clamp(int32_t &value, int32_t min, int32_t max) {
  if (value < min)
    value = min;
  if (value > max)
    value = max;
}

void clamp(uint8_t &value, int8_t min, int8_t max) {
  if (value < min)
    value = min;
  if (value > max)
    value = max;
}

void clamp(int8_t &value, int8_t min, int8_t max) {
  if (value < min)
    value = min;
  if (value > max)
    value = max;
}

const char *get_answer_text(int8_t answer) {
  if (answer < -2 || answer > 2) {
    return "invalid answer";
  }
  return answer_texts[answer + 2];
}
} // namespace tomd
