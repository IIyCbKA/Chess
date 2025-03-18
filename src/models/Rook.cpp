#include <models/Rook.hpp>
#include <constants.hpp>

std::vector<Position> Rook::getPossibleMoves(const Position curPosition) {
  std::vector<Position> moves;
  for (const auto [deltaRow, deltaCol] : PiecesConstants::ROOK_MOVES) {
    size_t tempRow = curPosition.row;
    size_t tempCol = curPosition.col;
    while (isWithinBounds({tempRow, tempCol}, deltaRow, deltaCol)) {
      tempRow += deltaRow;
      tempCol += deltaCol;
      if (const auto piece = this->boardContext.getPieceAt({tempRow, tempCol})) {
        if (piece->getColor() != this->color) moves.emplace_back(tempRow, tempCol);
        break;
      }

      moves.emplace_back(tempRow, tempCol);
    }
  }

  return moves;
}
