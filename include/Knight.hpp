#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include <constants.hpp>
#include <Piece.hpp>

class Knight : public Piece {
public:
  explicit Knight(PiecesConstants::COLORS color) :
    Piece(color, PiecesConstants::KNIGHT) {};

  ~Knight() override = default;
};

#endif
