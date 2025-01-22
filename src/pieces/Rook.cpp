#include <components/Square.hpp>
#include <pieces/Rook.hpp>
#include <constants.hpp>

vector<Position> Rook::getPossibleMoves(
  const Board& board, const Position curPosition
) {
  vector<Position> moves;
  for (const auto [deltaRow, deltaCol] : PiecesConstants::ROOK_MOVES) {
    size_t tempRow = curPosition.row;
    size_t tempCol = curPosition.col;
    while (isWithinBounds({tempRow, tempCol}, deltaRow, deltaCol)) {
      tempRow += deltaRow;
      tempCol += deltaCol;
      if (const auto piece = board[tempRow][tempCol]->getPiece()) {
        if (piece->getColor() != this->color) moves.emplace_back(tempRow, tempCol);
        break;
      }

      moves.emplace_back(tempRow, tempCol);
      board[tempRow][tempCol]->showCircle();
    }
  }

  return moves;
}
