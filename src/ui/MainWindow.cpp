#include <ui/MainWindow.hpp>
#include <ui/PromotionDialog.hpp>
#include <GameState.hpp>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui() {
  this->ui.setupUi(this);
  this->controller = new GameController(this->ui.chessBoardView);
  tryUpdateDifficultyBtn(this->ui.easyBotBtn, StockfishConstants::EASY_DEPTH);
  connect(
    this->ui.restartGameBtn, &QPushButton::clicked,
    this, &MainWindow::onRestartGameClicked
  );
  connect(
    this->ui.easyBotBtn, &QPushButton::clicked,
    this, &MainWindow::onEasyBotBtnClicked
  );
  connect(
    this->ui.mediumBotBtn, &QPushButton::clicked,
    this, &MainWindow::onMediumBotBtnClicked
  );
  connect(
    this->ui.hardBotBtn, &QPushButton::clicked,
    this, &MainWindow::onHardBotBtnClicked
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
  this->ui.chessBoardView->init();
  this->controller->restartGame();
}


void MainWindow::updateMoveIndicator() const {
  if (GameState::instance().isGameActive()) {
    if (GameState::instance().isUserMove())
      this->ui.moveIndicator->setText(ConstantsUI::YOUR_MOVE);
    else this->ui.moveIndicator->setText(ConstantsUI::BOT_MOVE);
  } else {
    this->ui.moveIndicator->setText(
      ConstantsUI::ENDGAME_TEXTS[GameState::instance().getActiveColor()][
        GameState::instance().getGameStatus()]
    );
  }
}


void MainWindow::onRestartGameClicked() const {
  this->controller->restartGame();
  this->ui.chessBoardView->turningBoard();
  this->ui.tableView->cleanTable();
  GameState::instance().restart();
  updateMoveIndicator();
  this->controller->tryEngineMove();
}


void MainWindow::onMoveMade(const MoveLog& log) const {
  if (GameState::instance().getActiveColor() == PiecesConstants::PIECE_COLORS::WHITE)
    this->ui.tableView->addWhiteMove(log);
  else this->ui.tableView->addBlackMove(log);

  GameState::instance().moveMade();
  updateMoveIndicator();
  this->controller->tryEngineMove();
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


void MainWindow::tryUpdateDifficultyBtn(
  QPushButton* clicked,
  const size_t clickedDepth
) {
  if (clicked && this->selectedDifficultyBtn != clicked) {
    this->controller->updateEngineDepth(clickedDepth);

    if (this->selectedDifficultyBtn) {
      this->selectedDifficultyBtn->setStyleSheet(
        ConstantsUI::DEFAULT_DIFFICULTY_BTN_STYLESHEET
      );
    }

    clicked->setStyleSheet(ConstantsUI::SELECTED_DIFFICULTY_BTN_STYLESHEET);
    this->selectedDifficultyBtn = clicked;
  }
}


void MainWindow::onEasyBotBtnClicked() {
  tryUpdateDifficultyBtn(
    qobject_cast<QPushButton*>(sender()),
    StockfishConstants::EASY_DEPTH
  );
}


void MainWindow::onMediumBotBtnClicked() {
  tryUpdateDifficultyBtn(
    qobject_cast<QPushButton*>(sender()),
    StockfishConstants::MEDIUM_DEPTH
  );
}


void MainWindow::onHardBotBtnClicked() {
  tryUpdateDifficultyBtn(
    qobject_cast<QPushButton*>(sender()),
    StockfishConstants::HARD_DEPTH
  );
}
