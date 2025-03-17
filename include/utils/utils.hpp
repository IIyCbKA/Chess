#ifndef UTILS_HPP
#define UTILS_HPP

#include <utils/position.hpp>
#include <constants.hpp>

#include <cstddef>

inline char getChar(const size_t num) {
  return static_cast<char>('a' + num);
}

inline bool inRange(const int value, const int min, const int max) {
  return value >= min && value < max;
}

inline PiecesConstants::PIECE_TYPES upperCharToPieceType(const char ch) {
  switch (ch) {
    case PiecesConstants::QUEEN_CHAR:
      return PiecesConstants::PIECE_TYPES::QUEEN;
    case PiecesConstants::ROOK_CHAR:
      return PiecesConstants::PIECE_TYPES::ROOK;
    case PiecesConstants::KNIGHT_CHAR:
      return PiecesConstants::PIECE_TYPES::KNIGHT;
    case PiecesConstants::BISHOP_CHAR:
      return PiecesConstants::PIECE_TYPES::BISHOP;
    case PiecesConstants::KING_CHAR:
      return PiecesConstants::PIECE_TYPES::KING;
    case PiecesConstants::PAWN_CHAR:
      return PiecesConstants::PIECE_TYPES::PAWN;
    default:
      return PiecesConstants::PIECE_TYPES::QUEEN;
  }
}

inline QString pieceTypeToHistoryStr(const PiecesConstants::PIECE_TYPES type) {
  switch (type) {
    case PiecesConstants::PIECE_TYPES::QUEEN:
      return ConstantsUI::HISTORY_PROMOTION_TO_QUEEN;
    case PiecesConstants::PIECE_TYPES::ROOK:
      return ConstantsUI::HISTORY_PROMOTION_TO_ROOK;
    case PiecesConstants::PIECE_TYPES::KNIGHT:
      return ConstantsUI::HISTORY_PROMOTION_TO_KNIGHT;
    case PiecesConstants::PIECE_TYPES::BISHOP:
      return ConstantsUI::HISTORY_PROMOTION_TO_BISHOP;
    default:
      return ConstantsUI::HISTORY_PROMOTION_TO_QUEEN;
  }
}

inline std::pair<Position, Position> getCastlingRookMove(
  const Position kingFrom,
  const Position kingTo
) {
  Position rookFrom, rookTo;
  rookFrom.row = kingTo.row;
  rookTo.row = kingTo.row;

  if (kingTo.col > kingFrom.col) {
    rookFrom.col = BoardConstants::DEFAULT_KINGSIDE_ROOK_COL;
    rookTo.col = BoardConstants::KINGSIDE_CASTLING_NEW_ROOK_COL;
  } else {
    rookFrom.col = BoardConstants::DEFAULT_QUEENSIDE_ROOK_COL;
    rookTo.col = BoardConstants::QUEENSIDE_CASTLING_NEW_ROOK_COL;
  }

  return std::make_pair(rookFrom, rookTo);
}

inline QColor getHighlightSelectedColor(const QColor baseColor) {
  if (baseColor == Colors::BEIGE) return Colors::HIGHLIGHTED_SELECTED_BEIGE;
  return Colors::HIGHLIGHTED_SELECTED_BROWN;
}

inline QColor getHighlightLastMoveColor(const QColor baseColor) {
  if (baseColor == Colors::BEIGE) return Colors::HIGHLIGHTED_LAST_MOVE_BEIGE;
  return Colors::HIGHLIGHTED_LAST_MOVE_BROWN;
}

inline QColor getDefaultSquareColor(const Position position) {
  if ((position.row + position.col) % 2 == 0) return Colors::BEIGE;
  return Colors::BROWN;
}

inline QColor getRevertSquareColor(const Position position) {
  if ((position.row + position.col) % 2 == 0) return Colors::BROWN;
  return Colors::BEIGE;
}

#endif //UTILS_HPP
