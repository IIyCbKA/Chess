#ifndef BOARDMODELCONTEXT_HPP
#define BOARDMODELCONTEXT_HPP

#include <utils/position.hpp>

class BoardModel;
class Piece;

class BoardModelContext {
  const BoardModel& model;

public:
  explicit BoardModelContext(const BoardModel& model) : model(model) {}

  [[nodiscard]] bool isOccupied(Position pos) const;
  [[nodiscard]] bool isUnderAttack(Position pos) const;
  [[nodiscard]] const Piece* getPieceAt(Position pos) const;
};

#endif //BOARDMODELCONTEXT_HPP
