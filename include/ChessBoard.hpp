#ifndef CHESSBOARD_HPP
#define CHESSBOARD_HPP

#include <Square.hpp>

#include <QGraphicsView>
#include <vector>

using namespace std;

class ChessBoard : public QGraphicsView {
  QGraphicsScene *scene;
  vector<vector<Square>> board;
  double boardSize = 0;
  double squareSize = 0;

  void resizeEvent(QResizeEvent *event) override;

public:
  explicit ChessBoard(QFrame *parent = nullptr);

  void init();
  void turningBoard();
  void setupPieces();
  void updateSizes();
  Piece* placePiece(Piece* piece, size_t row, size_t col);

  ~ChessBoard() override = default;
};

#endif
