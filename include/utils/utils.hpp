#ifndef UTILS_HPP
#define UTILS_HPP

#include <cstddef>

inline char getChar(const size_t num) {
  return static_cast<char>('a' + num);
}

inline bool inRange(const int value, const int min, const int max) {
  return value >= min && value < max;
}

#endif //UTILS_HPP
