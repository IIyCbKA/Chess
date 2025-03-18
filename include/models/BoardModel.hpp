#ifndef BOARDMODEL_HPP
#define BOARDMODEL_HPP

#include <models/Piece.hpp>
#include <utils/BoardTypes.hpp>
#include <utils/position.hpp>
#include <constants.hpp>

#include <array>
#include <bitset>
#include <memory>
#include <optional>

class BoardModel {
  ModelBoard board;
  std::optional<Position> selectedPosition;
  std::vector<Position> selectedCanMove;
  AttackMap attackMap;
  size_t halfMoveClock = 0;

  void updateHalfMoveClock(Position from, Position to);
  bool checkPossibleMove(Position from, Position to);
  [[nodiscard]] std::vector<Position> getPossibleMoves(Position pos) const;
  [[nodiscard]] bool isNotMovedPiece(Position pos) const;
  [[nodiscard]] bool isPosUnderAttack(
    Position checkPos,
    PiecesConstants::PIECE_COLORS opponentColor
  ) const;
  [[nodiscard]] std::unique_ptr<Piece> createPiece(
    PiecesConstants::PIECE_TYPES type,
    PiecesConstants::PIECE_COLORS color
  ) const;

public:
  BoardModel() = default;
  void cleanBoard();
  void setupPiece(
    Position pos,
    PiecesConstants::PIECE_COLORS color,
    PiecesConstants::PIECE_TYPES type
  );
  void removePiece(Position pos);
  void movePiece(Position from, Position to, bool isTrackMove);
  void updateAttackMap();
  void deselectSquare();
  void selectSquare(Position to);
  void changePawnType(
    Position pos,
    PiecesConstants::PIECE_TYPES newType,
    PiecesConstants::PIECE_COLORS color
  );

  [[nodiscard]] Position getSelectedPosition() const;
  [[nodiscard]] Piece* getPiece(Position piecePosition) const;
  [[nodiscard]] std::vector<Position> getSelectedCanMove() const;
  [[nodiscard]] bool isSelectedCanMoveTo(Position to) const;
  [[nodiscard]] bool trySelectSquare(Position to) const;
  [[nodiscard]] bool hasSelectedPiece() const;
  [[nodiscard]] bool isSamePosition(Position pos) const;
  [[nodiscard]] bool isPlayerHavePossibleMove();
  [[nodiscard]] std::string getBoardForFEN() const;
  [[nodiscard]] std::string getCastlingForFEN() const;
  [[nodiscard]] size_t getHalfMoveClock() const;
  [[nodiscard]] Position getCapturePos(Position from, Position to) const;
  [[nodiscard]] bool isCastling(Position from, Position to) const;
  [[nodiscard]] bool isPawnPromotion(Position pos) const;
  [[nodiscard]] bool isUnderAttack(Position pos) const;
  [[nodiscard]] Position getKingPosByColor(PiecesConstants::PIECE_COLORS color) const;

  ~BoardModel() = default;
};

#endif //BOARDMODEL_HPP
