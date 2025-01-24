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
      if (const auto piece = this->boardModel->getPiece({row, col})) {
        this->board[row][col]->addIcon(
          piece->getColor(),
          piece->getType(),
          this->squareSize
        );
      }
    }
  }
}


void BoardView::cleanBoard() {
  deselectSquare();
  for (size_t row = 0; row < BoardConstants::SQUARES_ROWS_COLS; ++row) {
    for (size_t col = 0; col < BoardConstants::SQUARES_ROWS_COLS; ++col) {
      this->board[row][col]->clearIcon();
    }
  }
}


void BoardView::boardReset() {
  cleanBoard();
  setupPieces();
}


void BoardView::selectSquare(SquareItem* square) {
  deselectSquare();
  this->selectedSquare = square;
  this->selectedCanMove = this->boardModel->getPossibleMoves(square->getRealPos());
  this->selectedSquare->getRect()->selectSquare();

  for (const auto [row, col] : this->selectedCanMove) {
    this->board[row][col]->showCircle();
  }
}


void BoardView::deselectSquare() {
  if (this->selectedSquare) {
    this->selectedSquare->getRect()->deselectSquare();
    this->selectedSquare = nullptr;
    for (const auto [row, col] : this->selectedCanMove) {
      this->board[row][col]->hideCircle();
    }
  }
}


void BoardView::performMove(const SquareItem *toSquare) {
  const Position from = this->selectedSquare->getRealPos();
  const Position to = toSquare->getRealPos();
  this->boardModel->movePiece(from, to);
  emit moveMade(from, to);
}


void BoardView::removePiece(const Position from) const {
  this->board[from.row][from.col]->clearIcon();
}


void BoardView::movePiece(const Position from, const Position to) const {
  this->board[from.row][from.col]->clearIcon();
  if (const auto piece = this->boardModel->getPiece(to)) {
    this->board[to.row][to.col]->addIcon(
      piece->getColor(),
      piece->getType(),
      this->squareSize
    );
  }
}


bool BoardView::isSelectedCanMoveTo(const Position to) const {
  return std::ranges::any_of(
    this->selectedCanMove,
    [to](const auto& pos) { return pos.row == to.row && pos.col == to.col; }
  );
}


void BoardView::onSquareClicked(SquareItem* square) {
  if (this->selectedSquare && this->selectedSquare == square) {
    deselectSquare();
    return;
  }

  if (
    const auto pieceInSquare = this->boardModel->getPiece(square->getRealPos());
    pieceInSquare &&
    pieceInSquare->getColor() == GameState::instance().getActiveColor()
  ) {
    selectSquare(square);
  } else if (this->selectedSquare) {
    if (isSelectedCanMoveTo(square->getRealPos())) performMove(square);
    deselectSquare();
  }
}
