#include <GameController.hpp>

GameController::GameController(BoardModel* model, BoardView* view, QObject* parent)
  : QObject(parent), model(model), view(view)
{
  connect(
    view, &BoardView::squareClicked,
    this, &GameController::onSquareClicked
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
    this->model->movePiece(to);
    this->view->movePiece(from, to);
    emit moveMade(from, to);
  }
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
