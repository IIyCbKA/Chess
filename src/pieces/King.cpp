#include <components/Square.hpp>
#include <pieces/King.hpp>
#include <constants.hpp>

vector<Position> King::getPossibleMoves(
  const Board& board, const Position curPosition
) {
  vector<Position> moves;
  for (const auto [deltaRow, deltaCol] : PiecesConstants::KING_MOVES) {
    if (isWithinBounds(curPosition, deltaRow, deltaCol)) {
      const size_t tempRow = curPosition.row + deltaRow;
      const size_t tempCol = curPosition.col + deltaCol;

      if (const auto piece = board[tempRow][tempCol]->getPiece()) {
        if (piece->getColor() != this->color) moves.emplace_back(tempRow, tempCol);
      } else {
        moves.emplace_back(tempRow, tempCol);
        board[tempRow][tempCol]->showCircle();
      }
    }
  }

  return moves;
}