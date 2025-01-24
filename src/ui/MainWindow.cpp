#include <ui/MainWindow.hpp>
#include <constants.hpp>
#include <GameState.hpp>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui() {
  this->ui.setupUi(this);
  this->boardModel = new BoardModel();
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
    this->boardModel, &BoardModel::onPieceMoved,
    this, &MainWindow::onPieceMoved
  );
  connect(
    this->ui.chessBoardView, &BoardView::moveMade,
    this, &MainWindow::onMoveMade
  );
}


void MainWindow::init() const {
  this->ui.chessBoardView->init(this->boardModel);
  this->boardModel->boardReset();
}


void MainWindow::updateMoveIndicator() const {
  if (GameState::instance().getActiveColor() == GameState::instance().getUserColor())
    this->ui.moveIndicator->setText(ConstantsUI::YOUR_MOVE);
  else this->ui.moveIndicator->setText(ConstantsUI::BOT_MOVE);
}


void MainWindow::onRestartGameClicked() const {
  this->boardModel->boardReset();
  this->ui.chessBoardView->turningBoard();
  this->ui.tableView->cleanTable();
  GameState::instance().restart();
  updateMoveIndicator();
}


void MainWindow::onMoveMade(const Position from, const Position to) const {
  if (GameState::instance().getActiveColor() == PiecesConstants::PIECE_COLORS::WHITE)
    this->ui.tableView->addWhiteMove(from, to);
  else this->ui.tableView->addBlackMove(from, to);

  GameState::instance().moveMade();
  updateMoveIndicator();
}


void MainWindow::onModelBoardReset() const {
  this->ui.chessBoardView->boardReset();
}


void MainWindow::onPieceMoved(const Position from, const Position to) const {
  this->ui.chessBoardView->movePiece(from, to);
}


void MainWindow::onPieceRemoved(const Position from) const {
  this->ui.chessBoardView->removePiece(from);
}
