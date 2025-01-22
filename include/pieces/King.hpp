#ifndef KING_HPP
#define KING_HPP

#include <pieces/Piece.hpp>
#include <utils/position.hpp>
#include <constants.hpp>

class King : public Piece {
public:
  explicit King(PiecesConstants::PIECE_COLORS color) :
    Piece(color, PiecesConstants::KING) {}

  vector<Position> getPossibleMoves(
    const Board& board, Position curPosition
  ) override;

  ~King() override = default;
};

#endif
