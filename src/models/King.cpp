#include <models/King.hpp>
#include <constants.hpp>

bool King::isValidCastleSquare(const Position pos) const {
  return
    !this->boardContext.isOccupied(pos) &&
    !this->boardContext.isUnderAttack(pos);
}


bool King::isValidRook(const Position pos) const {
  const auto piece = this->boardContext.getPieceAt(pos);

  return
    piece != nullptr
    && piece->getColor() == this->color
    && piece->getType() == PiecesConstants::PIECE_TYPES::ROOK
    && !piece->getIsMoved();
}


void King::getDefaultMoves(
  const Position curPosition,
  std::vector<Position>& moves
) const {
  for (const auto [deltaRow, deltaCol] : PiecesConstants::KING_MOVES) {
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
}


bool King::isCanCastling(
  const Position pos,
  const std::vector<size_t>& checkedCols,
  const size_t rookCol
) const {
  if (this->isMoved) return false;

  for (const size_t checkedCol : checkedCols) {
    const Position checkPos{pos.row, checkedCol};
    if (!isValidCastleSquare(checkPos)) return false;
  }

  const Position rookPos{pos.row, rookCol};
  return isValidRook(rookPos);
}


void King::canKingSideCastling(Position pos, std::vector<Position>& moves) const {
  if (isCanCastling(
    pos, BoardConstants::KINGSIDE_CASTLING_CHECKED_COLS,
    BoardConstants::DEFAULT_KINGSIDE_ROOK_COL
  )) {
    moves.emplace_back(pos.row, BoardConstants::KINGSIDE_CASTLING_NEW_KING_COL);
  }
}


void King::canQueenSideCastling(Position pos, std::vector<Position>& moves) const {
  if (isCanCastling(
    pos, BoardConstants::QUEENSIDE_CASTLING_CHECKED_COLS,
    BoardConstants::DEFAULT_QUEENSIDE_ROOK_COL
  )) {
    moves.emplace_back(pos.row, BoardConstants::QUEENSIDE_CASTLING_NEW_KING_COL);
  }
}


std::vector<Position> King::getPossibleMoves(const Position curPosition) {
  std::vector<Position> moves;
  getDefaultMoves(curPosition, moves);
  canKingSideCastling(curPosition, moves);
  canQueenSideCastling(curPosition, moves);

  return moves;
}