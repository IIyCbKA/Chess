#ifndef BOARDVIEW_HPP
#define BOARDVIEW_HPP

#include <models/BoardModel.hpp>
#include <ui/SquareItem.hpp>
#include <constants.hpp>

#include <array>
#include <QGraphicsView>

class BoardView : public QGraphicsView {
  Q_OBJECT;
  QGraphicsScene* scene = nullptr;
  BoardModel* boardModel = nullptr;
  std::array<
    std::array<SquareItem*, BoardConstants::SQUARES_ROWS_COLS>,
    BoardConstants::SQUARES_ROWS_COLS
  > board{};
  double boardSize = 0;
  double squareSize = 0;

  void resizeEvent(QResizeEvent *event) override;
  void setupPieces() const;
  void cleanBoard() const;

public:
  explicit BoardView(QFrame* parent = nullptr);

  void init(BoardModel* model);
  void turningBoard() const;
  void updateSizes();
  void boardReset() const;
  void highlightSquare(Position pos) const;
  void showPossibleMoves(const std::vector<Position>& moves) const;
  void clearHighlights() const;
  void removePiece(Position from) const;
  void movePiece(Position from, Position to) const;

signals:
  void squareClicked(Position pos);

private slots:
  void onSquareClicked(const SquareItem* square);
};

#endif //BOARDVIEW_HPP
