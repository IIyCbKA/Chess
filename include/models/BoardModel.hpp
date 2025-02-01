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

  void setupPieces();
  void cleanBoard();
  static void clearEnPassant();

public:
  BoardModel() = default;
  void boardReset();
  void removePiece(Position from);
  void movePiece(Position to);
  void deselectSquare();
  void selectSquare(Position to);
  void getPossibleMoves(Position from);

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
};

#endif //BOARDMODEL_HPP
