#ifndef ROOK_HPP
#define ROOK_HPP

#include <pieces/Piece.hpp>
#include <utils/position.hpp>
#include <constants.hpp>

class Rook : public Piece {
public:
  explicit Rook(PiecesConstants::PIECE_COLORS color) :
    Piece(color, PiecesConstants::ROOK) {}

  vector<Position> getPossibleMoves(
    const array <
      array<unique_ptr<Square>, BoardConstants::SQUARES_ROWS_COLS>,
      BoardConstants::SQUARES_ROWS_COLS
    >& board, Position curPosition
  ) override;

  ~Rook() override = default;
};

#endif
