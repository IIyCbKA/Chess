#ifndef BISHOP_HPP
#define BISHOP_HPP

#include <constants.hpp>
#include <Piece.hpp>

class Bishop : public Piece {
public:
  explicit Bishop(PiecesConstants::COLORS color) :
    Piece(color, PiecesConstants::BISHOP) {};

  ~Bishop() override = default;
};

#endif
