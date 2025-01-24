#include <models/Queen.hpp>
#include <constants.hpp>

std::vector<Position> Queen::getPossibleMoves(
  const Board& board, const Position curPosition
) {
  std::vector<Position> moves;
  for (const auto [deltaRow, deltaCol] : PiecesConstants::QUEEN_MOVES) {
    size_t tempRow = curPosition.row;
    size_t tempCol = curPosition.col;
    while (isWithinBounds({tempRow, tempCol}, deltaRow, deltaCol)) {
      tempRow += deltaRow;
      tempCol += deltaCol;
      if (const auto piece = board[tempRow][tempCol].get()) {
        if (piece->getColor() != this->color) moves.emplace_back(tempRow, tempCol);
        break;
      }

      moves.emplace_back(tempRow, tempCol);
    }
  }

  return moves;
}