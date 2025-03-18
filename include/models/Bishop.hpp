#ifndef BISHOP_HPP
#define BISHOP_HPP

#include <models/Piece.hpp>
#include <utils/position.hpp>
#include <constants.hpp>

class Bishop final : public Piece {
public:
  Bishop(
    const BoardModelContext boardContext,
    const PiecesConstants::PIECE_COLORS color
  ) : Piece(boardContext, color, PiecesConstants::BISHOP) {}

  std::vector<Position> getPossibleMoves(Position curPosition) override;

  ~Bishop() override = default;
};

#endif
