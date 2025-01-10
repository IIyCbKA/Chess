#ifndef PAWN_HPP
#define PAWN_HPP

#include <constants.hpp>
#include <Piece.hpp>

class Pawn : public Piece {
public:
  explicit Pawn(PiecesConstants::COLORS color) :
    Piece(color, PiecesConstants::PAWN) {};

  ~Pawn() override = default;
};

#endif
