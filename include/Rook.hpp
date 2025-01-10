#ifndef ROOK_HPP
#define ROOK_HPP

#include <constants.hpp>
#include <Piece.hpp>

class Rook : public Piece {
public:
  explicit Rook(PiecesConstants::COLORS color) :
    Piece(color, PiecesConstants::ROOK) {};

  ~Rook() override = default;
};

#endif
