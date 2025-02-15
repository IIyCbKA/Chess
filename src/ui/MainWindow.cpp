#include <ui/MainWindow.hpp>
#include <ui/PromotionDialog.hpp>
#include <GameState.hpp>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui() {
  this->ui.setupUi(this);
  this->boardModel = new BoardModel();
  this->controller = new GameController(this->boardModel, this->ui.chessBoardView);
  connect(
    this->ui.restartGameBtn, &QPushButton::clicked,
    this, &MainWindow::onRestartGameClicked
  );
  connect(
    this->boardModel, &BoardModel::onBoardReset,
    this, &MainWindow::onModelBoardReset
  );
  connect(
    this->boardModel, &BoardModel::onPieceRemoved,
    this, &MainWindow::onPieceRemoved
  );
  connect(
    this->controller, &GameController::moveMade,
    this, &MainWindow::onMoveMade
  );
  connect(
    this->controller, &GameController::pawnPromotion,
    this, &MainWindow::onPawnPromotion
  );
  connect(
    this->controller, &GameController::endGame,
    this, &MainWindow::onEndGame
  );
}


void MainWindow::init() const {
  this->ui.chessBoardView->init(this->boardModel);
  this->boardModel->boardReset();
}


void MainWindow::updateMoveIndicator() const {
  PiecesConstants::PIECE_COLORS activeColor = GameState::instance().getActiveColor();
  if (GameState::instance().getGameStatus() == GameStateConstants::CHECKMATE) {
    if (activeColor == PiecesConstants::PIECE_COLORS::WHITE)
      this->ui.moveIndicator->setText(ConstantsUI::BLACK_CHECKMATED);
    else this->ui.moveIndicator->setText(ConstantsUI::WHITE_CHECKMATED);
  } else if (GameState::instance().getGameStatus() == GameStateConstants::STALEMATE) {
    if (activeColor == PiecesConstants::PIECE_COLORS::WHITE)
      this->ui.moveIndicator->setText(ConstantsUI::BLACK_STALEMATED);
    else this->ui.moveIndicator->setText(ConstantsUI::WHITE_STALEMATED);
  } else {
    if (activeColor == GameState::instance().getUserColor())
      this->ui.moveIndicator->setText(ConstantsUI::YOUR_MOVE);
    else this->ui.moveIndicator->setText(ConstantsUI::BOT_MOVE);
  }
}


void MainWindow::onRestartGameClicked() const {
  this->boardModel->boardReset();
  this->ui.chessBoardView->turningBoard();
  this->ui.tableView->cleanTable();
  GameState::instance().restart();
  updateMoveIndicator();
}


void MainWindow::onMoveMade(const MoveLog &log) const {
  if (GameState::instance().getActiveColor() == PiecesConstants::PIECE_COLORS::WHITE)
    this->ui.tableView->addWhiteMove(log);
  else this->ui.tableView->addBlackMove(log);

  GameState::instance().moveMade();
  updateMoveIndicator();
}


void MainWindow::onModelBoardReset() const {
  this->ui.chessBoardView->boardReset();
}


void MainWindow::onPieceRemoved(const Position from) const {
  this->ui.chessBoardView->removePiece(from);
}


void MainWindow::onPawnPromotion(
  const Position pos,
  const PiecesConstants::PIECE_COLORS color
) {
  auto dialog = PromotionDialog(color, this);
  PiecesConstants::PIECE_TYPES chosenType = PiecesConstants::PIECE_TYPES::QUEEN;

  if (dialog.exec() == QDialog::Accepted) chosenType = dialog.getSelectedType();
  this->controller->changePawnType(pos, chosenType, color);
}


void MainWindow::onEndGame() const {
  updateMoveIndicator();
}