#ifndef BOARDMODEL_HPP
#define BOARDMODEL_HPP

#include <models/Piece.hpp>
#include <utils/position.hpp>
#include <constants.hpp>

#include <array>
#include <bitset>
#include <memory>
#include <optional>
#include <QObject>

class BoardModel final : public QObject {
  Q_OBJECT;
  std::array<
    std::array<std::unique_ptr<Piece>, BoardConstants::SQUARES_ROWS_COLS>,
    BoardConstants::SQUARES_ROWS_COLS
  > board;
  std::optional<Position> selectedPosition;
  std::vector<Position> selectedCanMove;
  std::array<
    std::bitset<BoardConstants::SQUARES_ROWS_COLS>,
    BoardConstants::SQUARES_ROWS_COLS
  > attackMap;
  size_t halfMoveClock = 0;

  static std::unique_ptr<Piece> createPiece(
    PiecesConstants::PIECE_TYPES type,
    PiecesConstants::PIECE_COLORS color
  );

  void updateHalfMoveClock(Position from, Position to);
  void tryCastling(Position from, Position to);
  void tryPawnPromotion(Position pos);
  void searchCheck();
  void updateAttackMap(PiecesConstants::PIECE_COLORS color);
  bool checkPossibleMove(Position from, Position to);
  [[nodiscard]] bool isCastling(Position from, Position to) const;
  [[nodiscard]] bool isPawnPromotion(Position pos) const;
  [[nodiscard]] bool isPosUnderAttack(Position checkPos, PiecesConstants::PIECE_COLORS opponentColor) const;
  [[nodiscard]] Position getKingPosByColor(PiecesConstants::PIECE_COLORS color) const;
  [[nodiscard]] std::vector<Position> getPossibleMoves(Position pos) const;
  [[nodiscard]] bool isNotMovedPiece(Position pos) const;

public:
  BoardModel() = default;
  void cleanBoard();
  void setupPiece(
    Position pos,
    PiecesConstants::PIECE_COLORS color,
    PiecesConstants::PIECE_TYPES type
  );
  void removePiece(Position pos);
  void movePiece(Position from, Position to);
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

  ~BoardModel() override = default;

signals:
  void onMoveRook(Position rookFrom, Position rookTo);
  void onPawnPromotion(Position pos, PiecesConstants::PIECE_COLORS color);
  void onCheck(Position pos, PiecesConstants::PIECE_COLORS color);
};

#endif //BOARDMODEL_HPP
