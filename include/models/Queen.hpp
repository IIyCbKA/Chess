#ifndef QUEEN_HPP
#define QUEEN_HPP

#include <models/Piece.hpp>
#include <utils/position.hpp>
#include <constants.hpp>

class Queen : public Piece {
public:
  explicit Queen(const PiecesConstants::PIECE_COLORS color) :
    Piece(color, PiecesConstants::QUEEN) {}

  std::vector<Position> getPossibleMoves(
    const Board& board, Position curPosition
  ) override;

  ~Queen() override = default;
};

#endif
