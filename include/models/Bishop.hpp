#ifndef BISHOP_HPP
#define BISHOP_HPP

#include <models/Piece.hpp>
#include <utils/position.hpp>
#include <constants.hpp>

class Bishop final : public Piece {
public:
  explicit Bishop(const PiecesConstants::PIECE_COLORS color) :
    Piece(color, PiecesConstants::BISHOP) {}

  std::vector<Position> getPossibleMoves(
    const Board& board, const AttackMap& attackMap, Position curPosition
  ) override;

  ~Bishop() override = default;
};

#endif
