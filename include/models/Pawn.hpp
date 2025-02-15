#ifndef PAWN_HPP
#define PAWN_HPP

#include <models/Piece.hpp>
#include <utils/enPassant.hpp>
#include <utils/position.hpp>
#include <constants.hpp>

#include <optional>

class Pawn : public Piece {
  static bool tryAddDefaultMove(
    const Board& board, Position curPosition,
    int deltaRow, int deltaCol, std::vector<Position>& moves
  );
  void getDefaultMoves(
    const Board& board, Position curPosition, std::vector<Position>& moves
  ) const;
  void getAttackMoves(
    const Board& board, Position curPosition, std::vector<Position>& moves
  ) const;

  [[nodiscard]] std::optional<EnPassant> tryGetEnPassantCapture(Position to) const;

public:
  explicit Pawn(const PiecesConstants::PIECE_COLORS color) :
    Piece(color, PiecesConstants::PAWN) {}

  std::vector<Position> getPossibleMoves(
    const Board& board, const AttackMap& attackMap, Position curPosition
  ) override;
  Position getCapturePosition(Position from, Position to) override;

  ~Pawn() override = default;
};

#endif
