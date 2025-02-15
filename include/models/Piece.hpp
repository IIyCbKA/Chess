#ifndef PIECE_HPP
#define PIECE_HPP

#include <utils/position.hpp>
#include <constants.hpp>

#include <bitset>

class Piece;

using Board = std::array<
  std::array<std::unique_ptr<Piece>, BoardConstants::SQUARES_ROWS_COLS>,
  BoardConstants::SQUARES_ROWS_COLS
>;

using AttackMap = std::array<
  std::bitset<BoardConstants::SQUARES_ROWS_COLS>,
  BoardConstants::SQUARES_ROWS_COLS
>;

class Piece {
protected:
  PiecesConstants::PIECE_COLORS color;
  PiecesConstants::PIECE_TYPES type;
  bool isMoved = false;

public:
  Piece(PiecesConstants::PIECE_COLORS color, PiecesConstants::PIECE_TYPES type);

  void move() { this->isMoved = true; }
  static bool isWithinBounds(Position curPosition, int moveRow, int moveCol);
  [[nodiscard]] PiecesConstants::PIECE_COLORS getColor() const { return this->color; }
  [[nodiscard]] PiecesConstants::PIECE_TYPES getType() const { return this->type; }
  [[nodiscard]] bool getIsMoved() const { return this->isMoved; }
  virtual Position getCapturePosition(const Position from, const Position to) { return to; }
  virtual std::vector<Position> getPossibleMoves(
    const Board& board, const AttackMap& attackMap, Position curPosition
  ) = 0;

  virtual ~Piece() = default;
};

#endif //PIECE_HPP
