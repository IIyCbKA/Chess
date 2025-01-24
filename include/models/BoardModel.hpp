#ifndef BOARDMODEL_HPP
#define BOARDMODEL_HPP

#include <models/Piece.hpp>
#include <constants.hpp>

#include <array>
#include <memory>
#include <QObject>

class BoardModel : public QObject {
  Q_OBJECT

  std::array<
    std::array<std::unique_ptr<Piece>, BoardConstants::SQUARES_ROWS_COLS>,
    BoardConstants::SQUARES_ROWS_COLS
  > board;

  void setupPieces();
  void cleanBoard();

public:
  BoardModel() = default;
  void boardReset();
  void removePiece(Position from);
  void movePiece(Position from, Position to);

  [[nodiscard]] Piece* getPiece(Position piecePosition) const;
  [[nodiscard]] std::vector<Position> getPossibleMoves(Position from) const;

  ~BoardModel() override = default;

signals:
  void onBoardReset();
  void onPieceMoved(Position from, Position to);
  void onPieceRemoved(Position from);
};

#endif //BOARDMODEL_HPP
