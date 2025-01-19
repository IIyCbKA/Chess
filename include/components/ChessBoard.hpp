#ifndef CHESSBOARD_HPP
#define CHESSBOARD_HPP

#include <components/Square.hpp>
#include <utils/position.hpp>

#include <array>
#include <QGraphicsView>

using namespace std;

class ChessBoard : public QGraphicsView {
  Q_OBJECT;
  QGraphicsScene *scene;
  array <
    array<unique_ptr<Square>, BoardConstants::SQUARES_ROWS_COLS>,
    BoardConstants::SQUARES_ROWS_COLS
  > board;
  double boardSize = 0;
  double squareSize = 0;
  Square* selectedSquare = nullptr;
  vector<Position> selectedCanMove;

  void resizeEvent(QResizeEvent *event) override;

public:
  explicit ChessBoard(QFrame *parent = nullptr);

  void init();
  void turningBoard();
  void setupPieces();
  void updateSizes();
  void deselectSquare();
  void movePiece(Square *toSquare);
  void deletePiece(Position from);
  void cleanBoard();
  void placePiece(unique_ptr<Piece> piece, Position to);

  ~ChessBoard() override = default;

signals:
  void moveMade(Position from, Position to);

private slots:
  void clickOnSquare(Square* square);
};

#endif
