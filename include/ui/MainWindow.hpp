#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <ui/ui_App.hpp>
#include <utils/moveLog.hpp>
#include <utils/position.hpp>
#include <constants.hpp>
#include <GameController.hpp>

#include <memory>

class MainWindow final : public QMainWindow {
  Q_OBJECT;
  std::unique_ptr<Ui::MainWindow> ui;
  GameController* controller = nullptr;
  QPushButton* selectedDifficultyBtn = nullptr;

  void updateMoveIndicator() const;
  void tryUpdateDifficultyBtn(QPushButton* clicked, size_t clickedDepth);

public:
  explicit MainWindow(QWidget* parent = nullptr);
  void init() const;
  ~MainWindow() override = default;

private slots:
  void onRestartGameClicked() const;
  void onMoveMade(const MoveLog& log) const;
  void onPawnPromotion(Position pos, PiecesConstants::PIECE_COLORS color);
  void onEndGame() const;
};

#endif
