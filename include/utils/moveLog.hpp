#ifndef MOVELOG_HPP
#define MOVELOG_HPP

#include <utils/position.hpp>

struct MoveLog {
  MoveLog(const Position initFrom, const Position initTo) :
    from(initFrom), to(initTo), isCastling(false), isKingSide(false) {}

  Position from;
  Position to;
  bool isCastling;
  bool isKingSide;
};

#endif //MOVELOG_HPP
