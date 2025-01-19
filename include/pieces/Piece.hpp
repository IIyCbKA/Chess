#ifndef PIECE_HPP
#define PIECE_HPP

#include <utils/position.hpp>
#include <constants.hpp>

#include <vector>
#include <QGraphicsSvgItem>
#include <QPointer>

using namespace std;

class Square;

class Piece {
protected:
  QPointer<QGraphicsSvgItem> svgIcon = nullptr;
  PiecesConstants::PIECE_COLORS color;

public:
  Piece(PiecesConstants::PIECE_COLORS color, PiecesConstants::PIECE_TYPES piece);

  [[nodiscard]] QGraphicsSvgItem* getSvgIcon() const { return this->svgIcon; }
  [[nodiscard]] PiecesConstants::PIECE_COLORS getColor() const { return this->color; }
  void svgIconUpdate(Position curPosition, double squareSize);

  virtual vector<Position> getPossibleMoves(
    const array <
      array<unique_ptr<Square>, BoardConstants::SQUARES_ROWS_COLS>,
      BoardConstants::SQUARES_ROWS_COLS
    >& board, Position curPosition
  ) = 0;

  virtual ~Piece() = default;
};

#endif
