#ifndef PIECE_HPP
#define PIECE_HPP

#include <utils/position.hpp>
#include <constants.hpp>

#include <vector>
#include <QGraphicsSvgItem>
#include <QPointer>

class Square;

using namespace std;
using Board = array <
  array<unique_ptr<Square>, BoardConstants::SQUARES_ROWS_COLS>,
  BoardConstants::SQUARES_ROWS_COLS
>;

class Piece {
protected:
  QPointer<QGraphicsSvgItem> svgIcon = nullptr;
  PiecesConstants::PIECE_COLORS color;
  bool isMoved = false;

public:
  Piece(PiecesConstants::PIECE_COLORS color, PiecesConstants::PIECE_TYPES piece);

  [[nodiscard]] QGraphicsSvgItem* getSvgIcon() const { return this->svgIcon; }
  [[nodiscard]] PiecesConstants::PIECE_COLORS getColor() const { return this->color; }
  void svgIconUpdate(Position curPosition, double squareSize);

  void move() { this->isMoved = true; }
  static bool isWithinBounds(Position curPosition, int moveRow, int moveCol);
  virtual vector<Position> getPossibleMoves(
    const Board& board, Position curPosition
  ) = 0;

  virtual ~Piece() = default;
};

#endif
