#ifndef QUEEN_HPP
#define QUEEN_HPP

#include <constants.hpp>
#include <Piece.hpp>

class Queen : public Piece {
public:
  explicit Queen(PiecesConstants::COLORS color) :
    Piece(color, PiecesConstants::QUEEN) {};

  ~Queen() override = default;
};

#endif
