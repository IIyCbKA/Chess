#ifndef PAWN_HPP
#define PAWN_HPP

#include <pieces/Piece.hpp>
#include <utils/position.hpp>
#include <constants.hpp>

class Pawn : public Piece {
public:
  explicit Pawn(PiecesConstants::PIECE_COLORS color) :
    Piece(color, PiecesConstants::PAWN) {}

  vector<Position> getPossibleMoves(
    const array <
      array<unique_ptr<Square>, BoardConstants::SQUARES_ROWS_COLS>,
      BoardConstants::SQUARES_ROWS_COLS
    >& board, Position curPosition
  ) override;

  ~Pawn() override = default;
};

#endif
