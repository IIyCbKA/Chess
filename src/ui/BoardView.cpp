#include <ui/BoardView.hpp>
#include <GameState.hpp>

BoardView::BoardView(QFrame *parent)
  : QGraphicsView(parent), scene(new QGraphicsScene(this))
{
  setScene(this->scene);
}


void BoardView::init(BoardModel* model) {
  updateSizes();
  this->boardModel = model;
  for(size_t row = 0; row < BoardConstants::SQUARES_ROWS_COLS; ++row) {
    for (size_t col = 0; col < BoardConstants::SQUARES_ROWS_COLS; ++col) {
      this->board[row][col] = new SquareItem({row, col}, this->squareSize);
      this->scene->addItem(this->board[row][col]->getRect());

      connect(
        this->board[row][col], &SquareItem::squareClick,
        this, &BoardView::onSquareClicked
      );
    }
  }
}


void BoardView::resizeEvent(QResizeEvent *event) {
  QGraphicsView::resizeEvent(event);

  updateSizes();
  setSceneRect(0, 0, this->boardSize, this->boardSize);

  for (size_t row = 0; row < BoardConstants::SQUARES_ROWS_COLS; ++row) {
    for (size_t col = 0; col < BoardConstants::SQUARES_ROWS_COLS; ++col) {
      this->board[row][col]->updatePosAndSize(this->squareSize);
    }
  }
}


void BoardView::updateSizes() {
  this->boardSize = std::min(viewport()->width(), viewport()->height());
  this->squareSize = this->boardSize / static_cast<double>(BoardConstants::SQUARES_ROWS_COLS);
}


void BoardView::turningBoard() const {
  for (size_t row = 0; row < BoardConstants::SQUARES_ROWS_COLS; ++row) {
    for (size_t col = 0; col < BoardConstants::SQUARES_ROWS_COLS; ++col) {
      this->board[row][col]->revertPos(this->squareSize);
    }
  }
}


void BoardView::setupPieces() const {
  for (size_t row = 0; row < BoardConstants::SQUARES_ROWS_COLS; ++row) {
    for (size_t col = 0; col < BoardConstants::SQUARES_ROWS_COLS; ++col) {
      setupPieceByPos({row, col});
    }
  }
}


void BoardView::setupPieceByPos(const Position pos) const {
  if (const auto piece = this->boardModel->getPiece(pos)) {
    this->board[pos.row][pos.col]->addIcon(
      piece->getColor(),
      piece->getType(),
      this->squareSize
    );
  }
}


void BoardView::cleanBoard() const {
  clearHighlights();
  for (size_t row = 0; row < BoardConstants::SQUARES_ROWS_COLS; ++row) {
    for (size_t col = 0; col < BoardConstants::SQUARES_ROWS_COLS; ++col) {
      this->board[row][col]->clearIcon();
    }
  }
}


void BoardView::boardReset() const {
  cleanBoard();
  setupPieces();
}


void BoardView::highlightSquare(const Position pos) const {
  this->board[pos.row][pos.col]->getRect()->selectSquare();
}


void BoardView::showPossibleMoves(const std::vector<Position>& moves) const {
  for (const auto&[row, col] : moves) {
    this->board[row][col]->showCircle();
  }
}


void BoardView::clearHighlights() const {
  for (size_t row = 0; row < BoardConstants::SQUARES_ROWS_COLS; ++row) {
    for (size_t col = 0; col < BoardConstants::SQUARES_ROWS_COLS; ++col) {
      this->board[row][col]->getRect()->deselectSquare();
      this->board[row][col]->hideCircle();
    }
  }
}


void BoardView::removePiece(const Position from) const {
  this->board[from.row][from.col]->clearIcon();
}


void BoardView::movePiece(const Position from, const Position to) const {
  removePiece(from);
  setupPieceByPos(to);
}


void BoardView::onSquareClicked(const SquareItem* square) {
  emit squareClicked(square->getRealPos());
}
