#ifndef PIECE_HPP
#define PIECE_HPP

#include <utils/BoardTypes.hpp>
#include <utils/position.hpp>
#include <constants.hpp>

class Piece {
protected:
  PiecesConstants::PIECE_COLORS color;
  PiecesConstants::PIECE_TYPES type;
  bool isMoved = false;

  static bool isWithinBounds(Position curPosition, int moveRow, int moveCol);

public:
  Piece(PiecesConstants::PIECE_COLORS color, PiecesConstants::PIECE_TYPES type);

  void move() { this->isMoved = true; }
  [[nodiscard]] PiecesConstants::PIECE_COLORS getColor() const { return this->color; }
  [[nodiscard]] PiecesConstants::PIECE_TYPES getType() const { return this->type; }
  [[nodiscard]] bool getIsMoved() const { return this->isMoved; }
  virtual Position getCapturePosition(const Position from, const Position to) { return to; }
  virtual std::vector<Position> getPossibleMoves(
    const ModelBoard& board, const AttackMap& attackMap, Position curPosition
  ) = 0;

  virtual ~Piece() = default;
};

#endif //PIECE_HPP
