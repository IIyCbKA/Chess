#ifndef MOVELOG_HPP
#define MOVELOG_HPP

#include <utils/position.hpp>

#include <constants.hpp>
#include <optional>

struct MoveLog {
  MoveLog(const Position initFrom, const Position initTo) :
    from(initFrom), to(initTo), isCastling(false), isKingSide(false), promotionType(std::nullopt) {}

  Position from;
  Position to;
  bool isCastling;
  bool isKingSide;
  std::optional<PiecesConstants::PIECE_TYPES> promotionType;
};

#endif //MOVELOG_HPP
