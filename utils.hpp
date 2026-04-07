#pragma once

#include "picosystem.hpp"

namespace tomd {
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
} // namespace tomd
