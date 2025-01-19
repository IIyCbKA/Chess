#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include <pieces/Piece.hpp>
#include <utils/position.hpp>
#include <constants.hpp>

class Knight : public Piece {
public:
  explicit Knight(PiecesConstants::PIECE_COLORS color) :
    Piece(color, PiecesConstants::KNIGHT) {}

  vector<Position> getPossibleMoves(
    const array <
      array<unique_ptr<Square>, BoardConstants::SQUARES_ROWS_COLS>,
      BoardConstants::SQUARES_ROWS_COLS
    >& board, Position curPosition
  ) override;

  ~Knight() override = default;
};

#endif
