#ifndef ROOK_HPP
#define ROOK_HPP

#include <models/Piece.hpp>
#include <utils/position.hpp>
#include <constants.hpp>

class Rook final : public Piece {
public:
  Rook(
    const BoardModelContext boardContext,
    const PiecesConstants::PIECE_COLORS color
  ) : Piece(boardContext, color, PiecesConstants::ROOK) {}

  std::vector<Position> getPossibleMoves(Position curPosition) override;

  ~Rook() override = default;
};

#endif
