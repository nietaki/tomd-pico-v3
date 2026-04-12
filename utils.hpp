#pragma once

#include <cstdint>

namespace tomd {

extern const char *answer_texts[5];

void clamp(uint32_t &value, int32_t min, int32_t max);
void clamp(int32_t &value, int32_t min, int32_t max);
void clamp(uint8_t &value, int8_t min, int8_t max);
void clamp(int8_t &value, int8_t min, int8_t max);

const char *get_answer_text(int8_t answer);
} // namespace tomd
