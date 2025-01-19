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
    const array <
      array<unique_ptr<Square>, BoardConstants::SQUARES_ROWS_COLS>,
      BoardConstants::SQUARES_ROWS_COLS
    >& board, Position curPosition
  ) override;

  ~King() override = default;
};

#endif
