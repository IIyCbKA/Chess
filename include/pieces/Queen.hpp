#ifndef QUEEN_HPP
#define QUEEN_HPP

#include <pieces/Piece.hpp>
#include <utils/position.hpp>
#include <constants.hpp>

class Queen : public Piece {
public:
  explicit Queen(PiecesConstants::PIECE_COLORS color) :
    Piece(color, PiecesConstants::QUEEN) {}

  vector<Position> getPossibleMoves(
    const Board& board, Position curPosition
  ) override;

  ~Queen() override = default;
};

#endif
