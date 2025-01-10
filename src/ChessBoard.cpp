#include <Bishop.hpp>
#include <ChessBoard.hpp>
#include <constants.hpp>
#include <King.hpp>
#include <Knight.hpp>
#include <Pawn.hpp>
#include <Queen.hpp>
#include <ResourceManager.hpp>
#include <Rook.hpp>

ChessBoard::ChessBoard(QFrame *parent)
  : QGraphicsView(parent),
  scene(new QGraphicsScene(this)),
  board(
    BoardConstants::SQUARES_ROWS_COLS,
    std::vector<Square>(BoardConstants::SQUARES_ROWS_COLS)
  )
{
  setScene(this->scene);
}


void ChessBoard::init() {
  updateSizes();

  for(size_t row = 0; row < BoardConstants::SQUARES_ROWS_COLS; ++row) {
    for (size_t col = 0; col < BoardConstants::SQUARES_ROWS_COLS; ++col) {
      this->board[row][col].addRect(scene->addRect(
        col * this->squareSize,
        row * this->squareSize,
        this->squareSize,
        this->squareSize,
        Qt::NoPen,
        (row + col) % 2 == 0
          ? QBrush(BoardConstants::COLORS::BEIGE)
          : QBrush(BoardConstants::COLORS::BROWN)
      ), col, row);
    }
  }
}


void ChessBoard::resizeEvent(QResizeEvent *event) {
  QGraphicsView::resizeEvent(event);

  updateSizes();
  setSceneRect(0, 0, this->boardSize, this->boardSize);

  for (size_t row = 0; row < BoardConstants::SQUARES_ROWS_COLS; ++row) {
    for (size_t col = 0; col < BoardConstants::SQUARES_ROWS_COLS; ++col) {
      this->board[row][col].setRectByPos(this->squareSize);

      if (this->board[row][col].getPiece()) {
        this->board[row][col].pieceSvgIconUpdate(this->squareSize);
      }
    }
  }
}


Piece* ChessBoard::placePiece(Piece *piece, size_t row, size_t col) {
  if (!piece) return nullptr;

  this->board[row][col].addPiece(piece);

  piece->svgIconUpdate(row, col, this->squareSize);
  piece->getSvgIcon()->setParentItem(this->board[row][col].getRect());

  return piece;
}


void ChessBoard::setupPieces() {
  using namespace PiecesConstants;

  for (int col = 0; col < BoardConstants::SQUARES_ROWS_COLS; ++col) {
    placePiece(new Pawn(COLORS::WHITE), 6, col);
  }

  placePiece(new Rook  (COLORS::WHITE), 7, 0);
  placePiece(new Knight(COLORS::WHITE), 7, 1);
  placePiece(new Bishop(COLORS::WHITE), 7, 2);
  placePiece(new Queen (COLORS::WHITE), 7, 3);
  placePiece(new King  (COLORS::WHITE), 7, 4);
  placePiece(new Bishop(COLORS::WHITE), 7, 5);
  placePiece(new Knight(COLORS::WHITE), 7, 6);
  placePiece(new Rook  (COLORS::WHITE), 7, 7);

  for (int col = 0; col < BoardConstants::SQUARES_ROWS_COLS; ++col) {
    placePiece(new Pawn(COLORS::BLACK), 1, col);
  }

  placePiece(new Rook  (COLORS::BLACK), 0, 0);
  placePiece(new Knight(COLORS::BLACK), 0, 1);
  placePiece(new Bishop(COLORS::BLACK), 0, 2);
  placePiece(new Queen (COLORS::BLACK), 0, 3);
  placePiece(new King  (COLORS::BLACK), 0, 4);
  placePiece(new Bishop(COLORS::BLACK), 0, 5);
  placePiece(new Knight(COLORS::BLACK), 0, 6);
  placePiece(new Rook  (COLORS::BLACK), 0, 7);
}


void ChessBoard::turningBoard() {
   for(size_t row = 0; row < BoardConstants::SQUARES_ROWS_COLS; ++row) {
     for (size_t col = 0; col < BoardConstants::SQUARES_ROWS_COLS; ++col) {
       this->board[row][col].revertPos();
       this->board[row][col].setRectByPos(this->squareSize);

       if (this->board[row][col].getPiece()) {
         this->board[row][col].pieceSvgIconUpdate(this->squareSize);
       }
     }
  }
}


void ChessBoard::updateSizes() {
  this->boardSize = min(viewport()->width(), viewport()->height());
  this->squareSize = this->boardSize / static_cast<double>(BoardConstants::SQUARES_ROWS_COLS);
}
