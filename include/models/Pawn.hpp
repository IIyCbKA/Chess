#ifndef PAWN_HPP
#define PAWN_HPP

#include <models/Piece.hpp>
#include <utils/enPassant.hpp>
#include <utils/position.hpp>
#include <constants.hpp>

#include <optional>

class Pawn final : public Piece {
  bool tryAddDefaultMove(
    Position curPosition, int deltaRow, int deltaCol, std::vector<Position>& moves
  ) const;
  void getDefaultMoves(Position curPosition, std::vector<Position>& moves) const;
  void getAttackMoves(Position curPosition, std::vector<Position>& moves) const;

  [[nodiscard]] std::optional<EnPassant> tryGetEnPassantCapture(Position to) const;

public:
  Pawn(
    const BoardModelContext boardContext,
    const PiecesConstants::PIECE_COLORS color
  ) : Piece(boardContext, color, PAWN_TYPE) {}

  std::vector<Position> getPossibleMoves(Position curPosition) override;
  Position getCapturePosition(Position from, Position to) override;

  ~Pawn() override = default;
};

#endif
