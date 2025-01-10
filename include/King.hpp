#ifndef KING_HPP
#define KING_HPP

#include <constants.hpp>
#include <Piece.hpp>

class King : public Piece {
public:
  explicit King(PiecesConstants::COLORS color) :
    Piece(color, PiecesConstants::KING) {};

  ~King() override = default;
};

#endif
