#include <pieces/Pawn.hpp>

vector<Position> Pawn::getPossibleMoves(
  const array <
    array<unique_ptr<Square>, BoardConstants::SQUARES_ROWS_COLS>,
    BoardConstants::SQUARES_ROWS_COLS
  >& board, const Position curPosition
) {
  return {};
}