#ifndef KING_HPP
#define KING_HPP

#include <models/Piece.hpp>
#include <utils/position.hpp>
#include <constants.hpp>

class King : public Piece {
  void getDefaultMoves(
    const Board& board, Position curPosition, std::vector<Position>& moves
  ) const;
  void canKingSideCastling(
    const Board& board, Position curPosition, std::vector<Position>& moves
  ) const;
  void canQueenSideCastling(
    const Board& board, Position curPosition, std::vector<Position>& moves
  ) const;
  [[nodiscard]] bool isValidRook(const Board& board, Position pos) const;

public:
  explicit King(const PiecesConstants::PIECE_COLORS color) :
    Piece(color, PiecesConstants::KING) {}

  std::vector<Position> getPossibleMoves(
    const Board& board, Position curPosition
  ) override;

  ~King() override = default;
};

#endif
