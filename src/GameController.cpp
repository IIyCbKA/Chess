#include <utils/highlightFlags.hpp>
#include <utils/utils.hpp>
#include <GameController.hpp>
#include <GameState.hpp>

GameController::GameController(BoardView* view, QObject* parent)
  : QObject(parent), view(view)
{
  this->model = new BoardModel();
  this->stockfishEngine = new StockfishEngine(this);
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
  connect(
    this->stockfishEngine, &StockfishEngine::bestMoveReady,
    this, &GameController::onStockfishMove
  );
}


void GameController::restartGame() const {
  this->model->cleanBoard();
  this->view->cleanBoard();
  for (const auto& [pos, color, type] : BoardConstants::STANDARD_SETUP) {
    this->model->setupPiece(pos, color, type);
    this->view->setupPiece(pos, color, type);
  }
}


void GameController::removePieceBeforeMove(
  const Position from,
  const Position to
) const {
  const Position removePos = this->model->getCapturePos(from, to);
  this->model->removePiece(removePos);
  this->view->removePiece(removePos);
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
  clearCheckAndLastMove();
  removePieceBeforeMove(data.from, data.to);
  this->model->movePiece(data.from, data.to);
  this->view->applyMoveEffect(
    data.from,
    data.to,
    this->model->getPiece(data.to)->getColor(),
    this->model->getPiece(data.to)->getType()
  );

  if (data.isTrackMove) {
    this->view->highlightLastMoveSquares(data.from, data.to);
    movePieceEmit(data.from, data.to);
  }

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
    performMovePiece({.from = from, .to = to, .isTrackMove = true});
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
    log.promotionType = *this->promotionPending;
    this->promotionPending.reset();
  }

  emit moveMade(log);
}


void GameController::onSquareClicked(const Position pos) {
  if (
    !GameState::instance().isGameActive()
    || !GameState::instance().isUserMove()
    || this->model->isSamePosition(pos)
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


void GameController::onCastlingMoveRook(const Position from, const Position to) {
  performMovePiece({.from = from, .to = to, .isTrackMove = false});
}


void GameController::onPawnPromotion(
  const Position pos,
  const PiecesConstants::PIECE_COLORS color
) {
  if (GameState::instance().isUserMove()) {
    emit pawnPromotion(pos, color);
  } else {
    changePawnType(pos, *this->enginePromotionSelection, color);
    this->enginePromotionSelection.reset();
  }
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


void GameController::clearCheckAndLastMove() const {
  if (GameState::instance().getCheckColor().has_value()) {
    this->view->clearHighlights({.isCheck = true, .isLastMove = true});
    GameState::instance().clearCheck();
  } else {
    this->view->clearHighlights({.isLastMove = true});
  }
}


void GameController::tryEngineMove() const {
  if (!GameState::instance().isUserMove()) {
    const QString fen = getFEN();
    this->stockfishEngine->setPosition(fen);
    this->stockfishEngine->calculateBestMove();
  }
}


QString GameController::getFEN() const {
  const std::string boardInFEN = this->model->getBoardForFEN();
  const char activeColorInFEN = ConstantsFEN::colorInFEN[
    GameState::instance().getActiveColor()];
  const std::string castling = this->model->getCastlingForFEN();
  const std::string enPassant = GameState::instance().getStringEnPassant();
  const size_t halfMoveClock = this->model->getHalfMoveClock();
  const size_t fullMoveNumber = GameState::instance().getFullMoveNumber();

  return QString(ConstantsFEN::FEN_DEFAULT_MASK)
    .arg(QString::fromStdString(boardInFEN))
    .arg(QChar(activeColorInFEN))
    .arg(QString::fromStdString(castling))
    .arg(QString::fromStdString(enPassant))
    .arg(halfMoveClock)
    .arg(fullMoveNumber);
}


void GameController::onStockfishMove(const QString& bestMove) {
  const std::string str = bestMove.toStdString();
  const Position from = {
    BoardConstants::CHAR_NUM_TO_NUM[str[StockfishConstants::BESTMOVE_FROM_ROW_IND]],
    BoardConstants::CHAR_TO_NUM_COL[str[StockfishConstants::BESTMOVE_FROM_COL_IND]]
  };

  const Position to = {
    BoardConstants::CHAR_NUM_TO_NUM[str[StockfishConstants::BESTMOVE_TO_ROW_IND]],
    BoardConstants::CHAR_TO_NUM_COL[str[StockfishConstants::BESTMOVE_TO_COL_IND]]
  };

  if (str.size() == StockfishConstants::BESTMOVE_SIZE_WITH_PROMOTION) {
    const char upperChar =
      static_cast<char>(std::toupper(str[StockfishConstants::BESTMOVE_PROMOTION_IND]));
    this->enginePromotionSelection = upperCharToPieceType(upperChar);
  }

  performMovePiece({.from = from, .to = to, .isTrackMove = true});
}


void GameController::updateEngineDepth(const size_t depth) const {
  this->stockfishEngine->updateDepth(depth);
}
