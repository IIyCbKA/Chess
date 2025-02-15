#include <models/King.hpp>
#include <constants.hpp>

bool King::isValidCastleSquare(
  const Board &board,
  const AttackMap &attackMap,
  const Position pos
) {
  return
    !board[pos.row][pos.col] &&
    !attackMap[pos.row][pos.col];
}


bool King::isValidRook(const Board &board, const Position pos) const {
  return
    board[pos.row][pos.col]
    && board[pos.row][pos.col]->getColor() == this->color
    && board[pos.row][pos.col]->getType() == PiecesConstants::PIECE_TYPES::ROOK
    && !board[pos.row][pos.col]->getIsMoved();
}


void King::getDefaultMoves(
  const Board &board,
  const Position curPosition,
  std::vector<Position> &moves
) const {
  for (const auto [deltaRow, deltaCol] : PiecesConstants::KING_MOVES) {
    if (isWithinBounds(curPosition, deltaRow, deltaCol)) {
      const size_t tempRow = curPosition.row + deltaRow;
      const size_t tempCol = curPosition.col + deltaCol;

      if (const auto piece = board[tempRow][tempCol].get()) {
        if (piece->getColor() != this->color) moves.emplace_back(tempRow, tempCol);
      } else {
        moves.emplace_back(tempRow, tempCol);
      }
    }
  }
}


void King::canKingSideCastling(
  const Board &board,
  const AttackMap& attackMap,
  Position pos,
  std::vector<Position> &moves
) const {
  if (
    !this->isMoved
    && isValidCastleSquare(board, attackMap, {pos.row, pos.col + BoardConstants::CASTLING_FIRST_OFFSET})
    && isValidCastleSquare(board, attackMap, {pos.row, pos.col + BoardConstants::CASTLING_SECOND_OFFSET})
    && isValidRook(board, {pos.row, pos.col + BoardConstants::KINGSIDE_CASTLING_ROOK_OFFSET})
  ) moves.emplace_back(pos.row, pos.col + BoardConstants::CASTLING_SECOND_OFFSET);
}


void King::canQueenSideCastling(
  const Board &board,
  const AttackMap& attackMap,
  Position pos,
  std::vector<Position> &moves
) const {
  if (
    !this->isMoved
    && isValidCastleSquare(board, attackMap, {pos.row, pos.col - BoardConstants::CASTLING_FIRST_OFFSET})
    && isValidCastleSquare(board, attackMap, {pos.row, pos.col - BoardConstants::CASTLING_SECOND_OFFSET})
    && isValidCastleSquare(board, attackMap, {pos.row, pos.col - BoardConstants::CASTLING_THIRD_OFFSET})
    && isValidRook(board, {pos.row, pos.col - BoardConstants::QUEENSIDE_CASTLING_ROOK_OFFSET})
  ) moves.emplace_back(pos.row, pos.col - BoardConstants::CASTLING_SECOND_OFFSET);
}


std::vector<Position> King::getPossibleMoves(
  const Board& board, const AttackMap& attackMap, const Position curPosition
) {
  std::vector<Position> moves;
  getDefaultMoves(board, curPosition, moves);
  canKingSideCastling(board, attackMap, curPosition, moves);
  canQueenSideCastling(board, attackMap, curPosition, moves);

  return moves;
}