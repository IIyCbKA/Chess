#ifndef KING_HPP
#define KING_HPP

#include <models/Piece.hpp>
#include <utils/position.hpp>
#include <constants.hpp>

class King final : public Piece {
  static bool isValidCastleSquare(
    const ModelBoard& board,
    const AttackMap& attackMap,
    Position pos
  );

  void getDefaultMoves(
    const ModelBoard& board, Position curPosition, std::vector<Position>& moves
  ) const;
  void canKingSideCastling(
    const ModelBoard& board, const AttackMap& attackMap,
    Position pos, std::vector<Position>& moves
  ) const;
  void canQueenSideCastling(
    const ModelBoard& board, const AttackMap& attackMap,
    Position pos, std::vector<Position>& moves
  ) const;
  [[nodiscard]] bool isValidRook(const ModelBoard& board, Position pos) const;
  [[nodiscard]] bool isCanCastling(
    const ModelBoard& board, const AttackMap& attackMap,
    Position pos, const std::vector<size_t>& checkedCols, size_t rookCol
  ) const;

public:
  explicit King(const PiecesConstants::PIECE_COLORS color) :
    Piece(color, PiecesConstants::KING) {}

  std::vector<Position> getPossibleMoves(
    const ModelBoard& board, const AttackMap& attackMap, Position curPosition
  ) override;

  ~King() override = default;
};

#endif
