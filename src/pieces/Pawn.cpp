#include <components/Square.hpp>
#include <pieces/Pawn.hpp>
#include <constants.hpp>

bool Pawn::tryAddDefaultMove(
  const Board& board, const Position curPosition,
  const int deltaRow, const int deltaCol, vector<Position> &moves
) {
  if (isWithinBounds(curPosition, deltaRow, deltaCol)) {
    const size_t tempRow = curPosition.row + deltaRow;
    const size_t tempCol = curPosition.col + deltaCol;

    if (!board[tempRow][tempCol]->getPiece()) {
      moves.emplace_back(tempRow, tempCol);
      board[tempRow][tempCol]->showCircle();
      return true;
    }
  }

  return false;
}


void Pawn::getDefaultMoves(
  const Board& board, const Position curPosition, vector<Position>& moves
) const {
  auto [deltaRow, deltaCol] = PiecesConstants::PAWN_DEFAULT_MOVE[this->color];
  if (
    tryAddDefaultMove(board, curPosition, deltaRow, deltaCol, moves)
    && !this->isMoved
  ) {
    const size_t tempRow = curPosition.row + deltaRow;
    const size_t tempCol = curPosition.col + deltaCol;
    tryAddDefaultMove(board, {tempRow, tempCol}, deltaRow, deltaCol, moves);
  }
}


void Pawn::getAttackMoves(
  const Board& board, const Position curPosition, vector<Position> &moves
) const {
  for (
    const auto [deltaRow, deltaCol] :
    PiecesConstants::PAWN_ATTACK_MOVES[this->color]
  ) {
    if (isWithinBounds(curPosition, deltaRow, deltaCol)) {
      size_t tempRow = curPosition.row + deltaRow;
      size_t tempCol = curPosition.col + deltaCol;

      if (const auto piece = board[tempRow][tempCol]->getPiece()) {
        if (piece->getColor() != this->color) moves.emplace_back(tempRow, tempCol);
      }
    }
  }
}


vector<Position> Pawn::getPossibleMoves(
  const Board& board, const Position curPosition
) {
  vector<Position> moves;
  getDefaultMoves(board, curPosition, moves);
  getAttackMoves(board, curPosition, moves);

  return moves;
}
