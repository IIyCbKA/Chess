#include <models/Knight.hpp>
#include <constants.hpp>

std::vector<Position> Knight::getPossibleMoves(const Position curPosition) {
  std::vector<Position> moves;
  for (const auto [deltaRow, deltaCol] : PiecesConstants::KNIGHT_MOVES) {
    if (isWithinBounds(curPosition, deltaRow, deltaCol)) {
      const size_t tempRow = curPosition.row + deltaRow;
      const size_t tempCol = curPosition.col + deltaCol;

      if (const auto piece = this->boardContext.getPieceAt({tempRow, tempCol})) {
        if (piece->getColor() != this->color) moves.emplace_back(tempRow, tempCol);
      } else {
        moves.emplace_back(tempRow, tempCol);
      }
    }
  }

  return moves;
}
