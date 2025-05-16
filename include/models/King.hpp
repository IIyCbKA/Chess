#ifndef KING_HPP
#define KING_HPP

#include <models/Piece.hpp>
#include <utils/position.hpp>
#include <constants.hpp>

class King final : public Piece {
  void getDefaultMoves(Position curPosition, std::vector<Position>& moves) const;
  void canKingSideCastling(Position pos, std::vector<Position>& moves) const;
  void canQueenSideCastling(Position pos, std::vector<Position>& moves) const;
  [[nodiscard]] bool isValidCastleSquare(Position pos) const;
  [[nodiscard]] bool isValidRook(Position pos) const;
  [[nodiscard]] bool isCanCastling(
    Position pos,
    const std::vector<size_t>& checkedCols,
    size_t rookCol
  ) const;

public:
  King(
    const BoardModelContext boardContext,
    const PiecesConstants::PIECE_COLORS color
  ) : Piece(boardContext, color, KING_TYPE) {}

  std::vector<Position> getPossibleMoves(Position curPosition) override;

  ~King() override = default;
};

#endif
