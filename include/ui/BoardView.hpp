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
  SquareItem* selectedSquare = nullptr;
  std::vector<Position> selectedCanMove;

  void resizeEvent(QResizeEvent *event) override;
  void setupPieces() const;
  void cleanBoard();

public:
  explicit BoardView(QFrame* parent = nullptr);

  void init(BoardModel* model);
  void turningBoard() const;
  void updateSizes();
  void boardReset();
  void selectSquare(SquareItem* square);
  void deselectSquare();
  void performMove(const SquareItem *toSquare);
  void removePiece(Position from) const;
  void movePiece(Position from, Position to) const;

  [[nodiscard]] bool isSelectedCanMoveTo(Position to) const;

signals:
  void moveMade(Position from, Position to);

private slots:
  void onSquareClicked(SquareItem* square);
};

#endif //BOARDVIEW_HPP
