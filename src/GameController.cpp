#include <GameController.hpp>

GameController::GameController(BoardModel* model, BoardView* view, QObject* parent)
  : QObject(parent), model(model), view(view)
{
  connect(
    view, &BoardView::squareClicked,
    this, &GameController::onSquareClicked
  );
  connect(
    this->model, &BoardModel::onMoveRook,
    this, &GameController::onCastlingMoveRook
  );
}


void GameController::selectSquare(const Position pos) const {
  if (this->model->hasSelectedPiece()) deselectSquare();

  this->model->selectSquare(pos);
  this->view->highlightSquare(pos);
  this->view->showPossibleMoves(this->model->getSelectedCanMove());
}


void GameController::deselectSquare() const {
  this->model->deselectSquare();
  this->view->clearHighlights();
}


void GameController::tryMovePiece(const Position to) {
  if (this->model->isSelectedCanMoveTo(to)) {
    const Position from = this->model->getSelectedPosition();
    this->model->movePiece(from, to);
    this->view->movePiece(from, to);
    movePieceEmit(from, to);
  }
}


void GameController::movePieceEmit(const Position from, const Position to) {
  MoveLog log(from, to);
  if (
    const auto piece = this->model->getPiece(to);
    piece->getType() == PiecesConstants::PIECE_TYPES::KING
    && std::abs(static_cast<int>(to.col) - static_cast<int>(from.col)) == 2
  ) {
    log.isCastling = true;
    log.isKingSide = to.col > from.col;
  }

  emit moveMade(log);
}


void GameController::onSquareClicked(const Position pos) {
  if (this->model->isSamePosition(pos)) {
    deselectSquare();
    return;
  }

  if (this->model->trySelectSquare(pos)) {
    selectSquare(pos);
  } else if (this->model->hasSelectedPiece()) {
    tryMovePiece(pos);
    deselectSquare();
  }
}


void GameController::forceMovePiece(const Position from, const Position to) const {
  this->model->movePiece(from, to);
  this->view->movePiece(from, to);
}


void GameController::onCastlingMoveRook(const Position from, const Position to) const {
  forceMovePiece(from, to);
}
