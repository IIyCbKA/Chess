#include <components/MainWindow.hpp>
#include <constants.hpp>
#include <GameState.hpp>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui() {
  this->ui.setupUi(this);
  connect(
    this->ui.restartGameBtn, &QPushButton::clicked,
    this, &MainWindow::onRestartGameClicked
  );
  connect(
    this->ui.chessBoardView, &ChessBoard::moveMade,
    this, &MainWindow::onMoveMade
  );
}


void MainWindow::init() const {
  this->ui.chessBoardView->init();
  this->ui.chessBoardView->setupPieces();
}


void MainWindow::onRestartGameClicked() {
  this->ui.chessBoardView->cleanBoard();
  this->ui.chessBoardView->setupPieces();
  this->ui.chessBoardView->turningBoard();
  this->ui.tableView->cleanTable();
  GameState::instance().restart();
  updateMoveIndicator();
}


void MainWindow::onMoveMade(Position from, Position to) {
  if (GameState::instance().getActiveColor() == PiecesConstants::PIECE_COLORS::WHITE)
    ui.tableView->addWhiteMove(from, to);
  else ui.tableView->addBlackMove(from, to);

  GameState::instance().moveMade();
  updateMoveIndicator();
}


void MainWindow::updateMoveIndicator() {
  if (GameState::instance().getActiveColor() == GameState::instance().getUserColor())
    this->ui.moveIndicator->setText(ConstantsUI::YOUR_MOVE);
  else this->ui.moveIndicator->setText(ConstantsUI::BOT_MOVE);
}
