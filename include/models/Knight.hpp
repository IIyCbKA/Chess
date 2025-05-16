#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include <models/Piece.hpp>
#include <utils/position.hpp>
#include <constants.hpp>

class Knight final : public Piece {
public:
  Knight(
    const BoardModelContext boardContext,
    const PiecesConstants::PIECE_COLORS color
  ) : Piece(boardContext, color, KNIGHT_TYPE) {}

  std::vector<Position> getPossibleMoves(Position curPosition) override;

  ~Knight() override = default;
};

#endif
