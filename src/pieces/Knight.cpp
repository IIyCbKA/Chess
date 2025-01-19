#include <components/Square.hpp>
#include <pieces/Knight.hpp>

vector<Position> Knight::getPossibleMoves(
  const array <
    array<unique_ptr<Square>, BoardConstants::SQUARES_ROWS_COLS>,
    BoardConstants::SQUARES_ROWS_COLS
  >& board, const Position curPosition
) {
  vector<Position> moves;
  const array<pair<int, int>, 8> knightMoves = {{
    {2, 1}, {-2, 1}, {-1, -2}, {-1, 2},
    {1, -2}, {1, 2}, {2, -1}, {-2, -1}
  }};

  for (auto [y, x] : knightMoves) {
    const size_t newY = curPosition.row + y;
    const size_t newX = curPosition.col + x;
    // Pattern
    if (newX <= 7 && newY <= 7) {
      moves.emplace_back(newY, newX);
      board[newY][newX]->showCircle();
    }
  }

  return moves;
}
