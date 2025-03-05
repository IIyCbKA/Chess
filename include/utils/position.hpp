#ifndef POSITION_HPP
#define POSITION_HPP

#include <cstddef>

struct Position {
  Position() : row(0), col(0) {}
  Position(const size_t initRow, const size_t initCol) : row(initRow), col(initCol) {}

  size_t row;
  size_t col;

  bool operator==(const Position& other) const {
    return this->row == other.row && this->col == other.col;
  }
};

#endif //POSITION_HPP
