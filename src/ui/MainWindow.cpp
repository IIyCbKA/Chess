#include <ui/MainWindow.hpp>
#include <ui/PromotionDialog.hpp>
#include <GameState.hpp>

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent), ui(std::make_unique<Ui::MainWindow>())
{
  this->ui->setupUi(this);
  this->controller = new GameController(this->ui->chessBoardView);
  tryUpdateDifficultyBtn(this->ui->easyBotBtn, StockfishConstants::EASY_DEPTH);
  connect(
    this->ui->restartGameBtn, &QPushButton::clicked,
    this, &MainWindow::onRestartGameClicked
  );
  connect(
    this->ui->easyBotBtn, &QPushButton::clicked,
    this, [this]() -> void {
      tryUpdateDifficultyBtn(this->ui->easyBotBtn, StockfishConstants::EASY_DEPTH);
    }
  );
  connect(
    this->ui->mediumBotBtn, &QPushButton::clicked,
    this, [this]() -> void {
      tryUpdateDifficultyBtn(this->ui->mediumBotBtn, StockfishConstants::MEDIUM_DEPTH);
    }
  );
  connect(
    this->ui->hardBotBtn, &QPushButton::clicked,
    this, [this]() -> void {
      tryUpdateDifficultyBtn(this->ui->hardBotBtn, StockfishConstants::HARD_DEPTH);
    }
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
  this->ui->chessBoardView->init();
  this->controller->restartGame();
}


void MainWindow::updateMoveIndicator() const {
  if (gameState.isGameActive()) {
    if (gameState.isUserMove())
      this->ui->moveIndicator->setText(ConstantsUI::YOUR_MOVE);
    else this->ui->moveIndicator->setText(ConstantsUI::BOT_MOVE);
  } else {
    this->ui->moveIndicator->setText(
      ConstantsUI::ENDGAME_TEXTS[gameState.getActiveColor()][
        gameState.getGameStatus()]
    );
  }
}


void MainWindow::onRestartGameClicked() const {
  this->controller->restartGame();
  this->ui->chessBoardView->turningBoard();
  this->ui->tableView->cleanTable();
  gameState.restart();
  updateMoveIndicator();
  this->controller->tryEngineMove();
}


void MainWindow::onMoveMade(const MoveLog& log) const {
  if (gameState.getActiveColor() == WHITE_COLOR)
    this->ui->tableView->addWhiteMove(log);
  else this->ui->tableView->addBlackMove(log);

  gameState.moveMade();
  updateMoveIndicator();
  this->controller->tryEngineMove();
}


void MainWindow::onPawnPromotion(
  const Position pos,
  const PiecesConstants::PIECE_COLORS color
) {
  auto dialog = PromotionDialog(color, this);
  PiecesConstants::PIECE_TYPES chosenType = QUEEN_TYPE;

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
