#include <utils/highlightFlags.hpp>
#include <GameController.hpp>
#include <GameState.hpp>

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
  connect(
    this->model, &BoardModel::onPawnPromotion,
    this, &GameController::onPawnPromotion
  );
  connect(
    this->model, &BoardModel::onCheck,
    this, &GameController::onCheck
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
  this->view->clearHighlights({.isSelect = true});
}


void GameController::performMovePiece(const PerformMoveData& data) {
  clearCheck();
  this->model->movePiece(data.from, data.to);
  this->view->movePiece(data.from, data.to);
  if (data.emitLog) movePieceEmit(data.from, data.to);
  endGameCheck();
}


void GameController::endGameCheck() {
  if (!this->model->isPlayerHavePossibleMove()) {
    const std::optional<PiecesConstants::PIECE_COLORS> checkColor =
      GameState::instance().getCheckColor();

    if (checkColor.has_value())
      GameState::instance().setGameStatus(GameStateConstants::GAME_STATUS::CHECKMATE);
    else GameState::instance().setGameStatus(GameStateConstants::GAME_STATUS::STALEMATE);

    emit endGame();
  }
}


void GameController::tryMovePiece(const Position to) {
  if (this->model->isSelectedCanMoveTo(to)) {
    const Position from = this->model->getSelectedPosition();
    performMovePiece({.from = from, .to = to, .emitLog = true});
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

  if (this->promotionPending.has_value()) {
    log.promotionType = this->promotionPending.value();
    this->promotionPending.reset();
  }

  emit moveMade(log);
}


void GameController::onSquareClicked(const Position pos) {
  if (
    GameState::instance().getGameStatus() != GameStateConstants::ACTIVE ||
    this->model->isSamePosition(pos)
  ) {
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


void GameController::forceMovePiece(const Position from, const Position to) {
  performMovePiece({.from = from, .to = to, .emitLog = false});
}


void GameController::onCastlingMoveRook(const Position from, const Position to) {
  forceMovePiece(from, to);
}


void GameController::onPawnPromotion(
  const Position pos,
  const PiecesConstants::PIECE_COLORS color
) {
  emit pawnPromotion(pos, color);
}


void GameController::changePawnType(
  const Position pos,
  const PiecesConstants::PIECE_TYPES newType,
  const PiecesConstants::PIECE_COLORS color
) {
  this->model->changePawnType(pos, newType, color);
  this->promotionPending = newType;
}


void GameController::onCheck(
  const Position pos,
  const PiecesConstants::PIECE_COLORS color
) const {
  this->view->highlightCheckSquare(pos);
  GameState::instance().setCheck(color);
}


void GameController::clearCheck() const {
  if (GameState::instance().getCheckColor().has_value()) {
    this->view->clearHighlights({.isCheck = true});
    GameState::instance().clearCheck();
  }
}
