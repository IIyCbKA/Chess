#ifndef PAWN_HPP
#define PAWN_HPP

#include <pieces/Piece.hpp>
#include <utils/position.hpp>
#include <constants.hpp>

class Pawn : public Piece {
  static bool tryAddDefaultMove(
    const Board& board, Position curPosition,
    int deltaRow, int deltaCol, vector<Position>& moves
  );
  void getDefaultMoves(
    const Board& board, Position curPosition, vector<Position>& moves
  ) const;
  void getAttackMoves(
    const Board& board, Position curPosition, vector<Position>& moves
  ) const;

public:
  explicit Pawn(PiecesConstants::PIECE_COLORS color) :
    Piece(color, PiecesConstants::PAWN) {}

  vector<Position> getPossibleMoves(
    const Board& board, Position curPosition
  ) override;

  ~Pawn() override = default;
};

#endif
