#include <models/King.hpp>
#include <constants.hpp>

bool King::isValidCastleSquare(
  const ModelBoard& board,
  const AttackMap& attackMap,
  const Position pos
) {
  return
    !board[pos.row][pos.col] &&
    !attackMap[pos.row][pos.col];
}


bool King::isValidRook(const ModelBoard& board, const Position pos) const {
  return
    board[pos.row][pos.col]
    && board[pos.row][pos.col]->getColor() == this->color
    && board[pos.row][pos.col]->getType() == PiecesConstants::PIECE_TYPES::ROOK
    && !board[pos.row][pos.col]->getIsMoved();
}


void King::getDefaultMoves(
  const ModelBoard& board,
  const Position curPosition,
  std::vector<Position>& moves
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


bool King::isCanCastling(
  const ModelBoard& board,
  const AttackMap& attackMap,
  const Position pos,
  const std::vector<size_t>& checkedCols,
  const size_t rookCol
) const {
  if (this->isMoved) return false;

  for (const size_t checkedCol : checkedCols) {
    const Position checkPos{pos.row, checkedCol};
    if (!isValidCastleSquare(board, attackMap, checkPos)) return false;
  }

  const Position rookPos{pos.row, rookCol};
  return isValidRook(board, rookPos);
}


void King::canKingSideCastling(
  const ModelBoard& board,
  const AttackMap& attackMap,
  Position pos,
  std::vector<Position> &moves
) const {
  if (isCanCastling(
    board, attackMap, pos, BoardConstants::KINGSIDE_CASTLING_CHECKED_COLS,
    BoardConstants::DEFAULT_KINGSIDE_ROOK_COL
  )) {
    moves.emplace_back(pos.row, BoardConstants::KINGSIDE_CASTLING_NEW_KING_COL);
  }
}


void King::canQueenSideCastling(
  const ModelBoard& board,
  const AttackMap& attackMap,
  Position pos,
  std::vector<Position>& moves
) const {
  if (isCanCastling(
    board, attackMap, pos, BoardConstants::QUEENSIDE_CASTLING_CHECKED_COLS,
    BoardConstants::DEFAULT_QUEENSIDE_ROOK_COL
  )) {
    moves.emplace_back(pos.row, BoardConstants::QUEENSIDE_CASTLING_NEW_KING_COL);
  }
}


std::vector<Position> King::getPossibleMoves(
  const ModelBoard& board, const AttackMap& attackMap, const Position curPosition
) {
  std::vector<Position> moves;
  getDefaultMoves(board, curPosition, moves);
  canKingSideCastling(board, attackMap, curPosition, moves);
  canQueenSideCastling(board, attackMap, curPosition, moves);

  return moves;
}