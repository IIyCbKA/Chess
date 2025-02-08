#ifndef BOARDMODEL_HPP
#define BOARDMODEL_HPP

#include <models/Piece.hpp>
#include <constants.hpp>

#include <array>
#include <memory>
#include <optional>
#include <QObject>

class BoardModel : public QObject {
  Q_OBJECT;
  std::array<
    std::array<std::unique_ptr<Piece>, BoardConstants::SQUARES_ROWS_COLS>,
    BoardConstants::SQUARES_ROWS_COLS
  > board;
  std::optional<Position> selectedPosition;
  std::vector<Position> selectedCanMove;

  static void clearEnPassant();
  static std::unique_ptr<Piece> createPiece(
    PiecesConstants::PIECE_TYPES type,
    PiecesConstants::PIECE_COLORS color
  );

  void setupPieces();
  void cleanBoard();
  void getPossibleMoves(Position from);
  void removePiece(Position from);
  void tryCastling(Position to);
  void tryPawnPromotion(Position pos);
  [[nodiscard]] bool isCastling(Position to) const;
  [[nodiscard]] bool isPawnPromotion(Position pos) const;

public:
  BoardModel() = default;
  void boardReset();
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

  ~BoardModel() override = default;

signals:
  void onBoardReset();
  void onPieceRemoved(Position from);
  void onMoveRook(Position rookFrom, Position rookTo);
  void onPawnPromotion(Position pos, PiecesConstants::PIECE_COLORS color);
};

#endif //BOARDMODEL_HPP
