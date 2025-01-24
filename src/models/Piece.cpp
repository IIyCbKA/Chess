#include <models/Piece.hpp>
#include <utils/utils.hpp>

Piece::Piece(
  const PiecesConstants::PIECE_COLORS color,
  const PiecesConstants::PIECE_TYPES type
) {
  this->color = color;
  this->type = type;
}


bool Piece::isWithinBounds(
  const Position curPosition,
  const int moveRow,
  const int moveCol
) {
  const int newRow = static_cast<int>(curPosition.row) + moveRow;
  const int newCol = static_cast<int>(curPosition.col) + moveCol;

  return
    inRange(newRow, 0, BoardConstants::SQUARES_ROWS_COLS) &&
    inRange(newCol, 0, BoardConstants::SQUARES_ROWS_COLS);
}
