#include <components/ChessBoard.hpp>
#include <components/RectItem.hpp>
#include <pieces/Bishop.hpp>
#include <pieces/King.hpp>
#include <pieces/Knight.hpp>
#include <pieces/Pawn.hpp>
#include <pieces/Queen.hpp>
#include <pieces/Rook.hpp>
#include <constants.hpp>
#include <GameState.hpp>
#include <ResourceManager.hpp>

ChessBoard::ChessBoard(QFrame *parent)
  : QGraphicsView(parent), scene(new QGraphicsScene(this))
{
  setScene(this->scene);
}


void ChessBoard::init() {
  updateSizes();
  for(size_t row = 0; row < BoardConstants::SQUARES_ROWS_COLS; ++row) {
    for (size_t col = 0; col < BoardConstants::SQUARES_ROWS_COLS; ++col) {
      this->board[row][col] = make_unique<Square>(Position{row, col}, this->squareSize);
      this->scene->addItem(this->board[row][col]->getRect());

      connect(
        this->board[row][col].get(), &Square::squareClick,
        this, &ChessBoard::clickOnSquare
      );
    }
  }
}


void ChessBoard::resizeEvent(QResizeEvent *event) {
  QGraphicsView::resizeEvent(event);

  updateSizes();
  setSceneRect(0, 0, this->boardSize, this->boardSize);

  for (size_t row = 0; row < BoardConstants::SQUARES_ROWS_COLS; ++row) {
    for (size_t col = 0; col < BoardConstants::SQUARES_ROWS_COLS; ++col) {
      this->board[row][col]->setRectByPos(this->squareSize);
      this->board[row][col]->setCircleByPos(this->squareSize);

      if (this->board[row][col]->getPiece()) {
        this->board[row][col]->pieceSvgIconUpdate(this->squareSize);
      }
    }
  }
}


void ChessBoard::placePiece(unique_ptr<Piece> piece, const Position to) {
  if (!piece) return;

  this->board[to.row][to.col]->addPiece(std::move(piece));
  this->board[to.row][to.col]->getPiece()->getSvgIcon()->setParentItem(
    this->board[to.row][to.col]->getRect()
  );
  this->board[to.row][to.col]->pieceSvgIconUpdate(this->squareSize);
}


void ChessBoard::setupPieces() {
  using namespace PiecesConstants;

  for (size_t col = 0; col < BoardConstants::SQUARES_ROWS_COLS; ++col) {
    placePiece(make_unique<Pawn> (Pawn(PIECE_COLORS::WHITE)), {6, col});
  }

  placePiece(make_unique<Rook>   (Rook(PIECE_COLORS::WHITE)), {7, 0});
  placePiece(make_unique<Knight> (Knight(PIECE_COLORS::WHITE)), {7, 1});
  placePiece(make_unique<Bishop> (Bishop(PIECE_COLORS::WHITE)), {7, 2});
  placePiece(make_unique<Queen>  (Queen(PIECE_COLORS::WHITE)), {7, 3});
  placePiece(make_unique<King>   (King(PIECE_COLORS::WHITE)), {7, 4});
  placePiece(make_unique<Bishop> (Bishop(PIECE_COLORS::WHITE)), {7, 5});
  placePiece(make_unique<Knight> (Knight(PIECE_COLORS::WHITE)), {7, 6});
  placePiece(make_unique<Rook>   (Rook(PIECE_COLORS::WHITE)), {7, 7});

  for (size_t col = 0; col < BoardConstants::SQUARES_ROWS_COLS; ++col) {
    placePiece(make_unique<Pawn> (Pawn(PIECE_COLORS::BLACK)), {1, col});
  }

  placePiece(make_unique<Rook>   (Rook(PIECE_COLORS::BLACK)), {0, 0});
  placePiece(make_unique<Knight> (Knight(PIECE_COLORS::BLACK)), {0, 1});
  placePiece(make_unique<Bishop> (Bishop(PIECE_COLORS::BLACK)), {0, 2});
  placePiece(make_unique<Queen>  (Queen(PIECE_COLORS::BLACK)), {0, 3});
  placePiece(make_unique<King>   (King(PIECE_COLORS::BLACK)), {0, 4});
  placePiece(make_unique<Bishop> (Bishop(PIECE_COLORS::BLACK)), {0, 5});
  placePiece(make_unique<Knight> (Knight(PIECE_COLORS::BLACK)), {0, 6});
  placePiece(make_unique<Rook>   (Rook(PIECE_COLORS::BLACK)), {0, 7});
}


void ChessBoard::turningBoard() {
   for(size_t row = 0; row < BoardConstants::SQUARES_ROWS_COLS; ++row) {
     for (size_t col = 0; col < BoardConstants::SQUARES_ROWS_COLS; ++col) {
       this->board[row][col]->revertPos();
       this->board[row][col]->setRectByPos(this->squareSize);
       this->board[row][col]->setCircleByPos(this->squareSize);

       if (this->board[row][col]->getPiece()) {
         this->board[row][col]->pieceSvgIconUpdate(this->squareSize);
       }
     }
  }
}


void ChessBoard::updateSizes() {
  this->boardSize = min(viewport()->width(), viewport()->height());
  this->squareSize = this->boardSize / static_cast<double>(BoardConstants::SQUARES_ROWS_COLS);
}


void ChessBoard::deselectSquare() {
  this->selectedSquare->getRect()->deselectSquare();
  this->selectedSquare = nullptr;
  for (const auto [row, col] : this->selectedCanMove) {
    board[row][col]->hideCircle();
  }
}


// primitive mechanics
void ChessBoard::clickOnSquare(Square *square) {
  if (this->selectedSquare && this->selectedSquare == square) {
    deselectSquare();
    return;
  }

  if (
    square->getPiece() &&
    square->getPiece()->getColor() == GameState::instance().getActiveColor()
  ) {
    if (this->selectedSquare) deselectSquare();

    this->selectedSquare = square;
    this->selectedCanMove = this->selectedSquare->getPiece()->getPossibleMoves(
      board, this->selectedSquare->getRealPos()
    );
    this->selectedSquare->getRect()->selectSquare();
  } else if (this->selectedSquare) {
    movePiece(square);
    deselectSquare();
  }
}


void ChessBoard::deletePiece(const Position from) {
  if (this->board[from.row][from.col]->getPiece()) {
    this->board[from.row][from.col]->clearPiece();
  }
}


void ChessBoard::movePiece(Square *toSquare) {
  const Position from = this->selectedSquare->getRealPos();
  const Position to = toSquare->getRealPos();
  deletePiece(to);

  this->board[to.row][to.col]->addPiece(
    std::move(this->selectedSquare->releasePiece())
  );
  this->board[to.row][to.col]->getPiece()->getSvgIcon()->setParentItem(
    this->board[to.row][to.col]->getRect()
  );
  this->board[to.row][to.col]->pieceSvgIconUpdate(this->squareSize);
  emit moveMade(from, to);
}


void ChessBoard::cleanBoard() {
  for (size_t row = 0; row < BoardConstants::SQUARES_ROWS_COLS; ++row) {
    for (size_t col = 0; col < BoardConstants::SQUARES_ROWS_COLS; ++col) {
      deletePiece({row, col});
    }
  }
}
