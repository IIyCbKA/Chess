#include <MainWindow.hpp>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui() {
  this->ui.setupUi(this);
  connect(
    this->ui.restartGameBtn, &QPushButton::clicked,
    this, &MainWindow::onRestartGameClicked
  );
}


void MainWindow::init() const {
  this->ui.chessBoardView->init();
  this->ui.chessBoardView->setupPieces();
}


void MainWindow::onRestartGameClicked() {
  this->gameState.restart();
  this->ui.chessBoardView->turningBoard();
}
