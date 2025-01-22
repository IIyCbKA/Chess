#ifndef BISHOP_HPP
#define BISHOP_HPP

#include <pieces/Piece.hpp>
#include <utils/position.hpp>
#include <constants.hpp>

class Bishop : public Piece {
public:
  explicit Bishop(PiecesConstants::PIECE_COLORS color) :
    Piece(color, PiecesConstants::BISHOP) {}

  vector<Position> getPossibleMoves(
    const Board& board, Position curPosition
  ) override;

  ~Bishop() override = default;
};

#endif
