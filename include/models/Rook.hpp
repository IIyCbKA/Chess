#ifndef ROOK_HPP
#define ROOK_HPP

#include <models/Piece.hpp>
#include <utils/position.hpp>
#include <constants.hpp>

class Rook : public Piece {
public:
  explicit Rook(const PiecesConstants::PIECE_COLORS color) :
    Piece(color, PiecesConstants::ROOK) {}

  std::vector<Position> getPossibleMoves(
    const Board& board, Position curPosition
  ) override;

  ~Rook() override = default;
};

#endif
