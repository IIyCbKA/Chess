#ifndef QUEEN_HPP
#define QUEEN_HPP

#include <models/Piece.hpp>
#include <utils/position.hpp>
#include <constants.hpp>

class Queen final : public Piece {
public:
  Queen(
    const BoardModelContext boardContext,
    const PiecesConstants::PIECE_COLORS color
  ) : Piece(boardContext, color, PiecesConstants::QUEEN) {}

  std::vector<Position> getPossibleMoves(Position curPosition) override;

  ~Queen() override = default;
};

#endif
