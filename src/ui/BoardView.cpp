#include <ui/BoardView.hpp>

BoardView::BoardView(QFrame* parent)
  : QGraphicsView(parent), scene(new QGraphicsScene(this))
{
  setScene(this->scene);
}


void BoardView::init() {
  updateSizes();
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

  setupCoordinateLabels();
}


void BoardView::resizeEvent(QResizeEvent* event) {
  QGraphicsView::resizeEvent(event);

  updateSizes();
  setSceneRect(0, 0, this->boardSize, this->boardSize);

  for (size_t row = 0; row < BoardConstants::SQUARES_ROWS_COLS; ++row) {
    for (size_t col = 0; col < BoardConstants::SQUARES_ROWS_COLS; ++col) {
      this->board[row][col]->updatePosAndSize(this->squareSize);
    }
  }

  for (const auto& label : this->coordinateLabels) {
    label->updatePosition(this->squareSize);
  }
}


void BoardView::setupCoordinateLabels() {
  const auto setupLabels = [this](const BoardConstants::COORDINATES_TYPE type) {
    const size_t fixedCoord = type == BoardConstants::COORDINATES_TYPE::COLS
      ? BoardConstants::DEFAULT_ROW_FOR_COLS_COORDINATES
      : BoardConstants::DEFAULT_COL_FOR_ROWS_COORDINATES;

    for (size_t ind = 0; ind < BoardConstants::SQUARES_ROWS_COLS; ++ind) {
      const Position pos = type == BoardConstants::COORDINATES_TYPE::COLS
        ? Position{fixedCoord, ind}
        : Position{ind, fixedCoord};

      auto* label = new CoordinateLabel(pos, type);
      this->scene->addItem(label);
      label->updatePosition(this->squareSize); // required after added to scene!
      this->coordinateLabels.emplace_back(label);
    }
  };

  setupLabels(BoardConstants::COORDINATES_TYPE::ROWS);
  setupLabels(BoardConstants::COORDINATES_TYPE::COLS);
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

  for (const auto& label : this->coordinateLabels) {
    label->updateCharAfterTurningBoard();
  }
}


void BoardView::setupPiece(
  const Position pos,
  const PiecesConstants::PIECE_COLORS color,
  const PiecesConstants::PIECE_TYPES type
) const {
  this->board[pos.row][pos.col]->addIcon(color, type, this->squareSize);
}


void BoardView::cleanBoard() const {
  clearHighlights({.isSelect = true, .isCheck = true, .isLastMove = true});
  for (size_t row = 0; row < BoardConstants::SQUARES_ROWS_COLS; ++row) {
    for (size_t col = 0; col < BoardConstants::SQUARES_ROWS_COLS; ++col) {
      this->board[row][col]->clearIcon();
    }
  }
}


void BoardView::highlightSquare(const Position pos) const {
  this->board[pos.row][pos.col]->getRect()->highlightSelectSquare();
}


void BoardView::showPossibleMoves(const std::vector<Position>& moves) const {
  for (const auto&[row, col] : moves) {
    this->board[row][col]->showCircle();
  }
}


void BoardView::clearHighlights(const HighlightFlags flags) const {
  for (size_t row = 0; row < BoardConstants::SQUARES_ROWS_COLS; ++row) {
    for (size_t col = 0; col < BoardConstants::SQUARES_ROWS_COLS; ++col) {
      if (flags.isSelect) this->board[row][col]->getRect()->unhighlightSelectSquare();
      if (flags.isCheck) this->board[row][col]->getRect()->unhighlightCheckSquare();
      if (flags.isLastMove) this->board[row][col]->getRect()->unhighlightLastMove();
      this->board[row][col]->hideCircle();
    }
  }
}


void BoardView::removePiece(const Position from) const {
  this->board[from.row][from.col]->clearIcon();
}


void BoardView::onSquareClicked(const SquareItem* square) {
  emit squareClicked(square->getRealPos());
}


void BoardView::highlightCheckSquare(const Position pos) const {
  this->board[pos.row][pos.col]->getRect()->highlightCheckSquare();
}


void BoardView::highlightLastMoveSquares(
  const Position from,
  const Position to
) const {
  this->board[from.row][from.col]->getRect()->highlightLastMove();
  this->board[to.row][to.col]->getRect()->highlightLastMove();
}


void BoardView::applyMoveEffect(
  const Position from,
  const Position to,
  const PiecesConstants::PIECE_COLORS color,
  const PiecesConstants::PIECE_TYPES type
) const {
  removePiece(from);
  setupPiece(to, color, type);
}
