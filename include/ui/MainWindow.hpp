#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <ui/ui_App.hpp>
#include <utils/moveLog.hpp>
#include <utils/position.hpp>
#include <GameController.hpp>

class MainWindow : public QMainWindow {
  Q_OBJECT;
  Ui::MainWindow ui;
  BoardModel* boardModel = nullptr;
  GameController* controller = nullptr;

  void updateMoveIndicator() const;

public:
  explicit MainWindow(QWidget *parent = nullptr);

  void init() const;

  ~MainWindow() override = default;

private slots:
  void onRestartGameClicked() const;
  void onMoveMade(const MoveLog &log) const;
  void onModelBoardReset() const;
  void onPieceRemoved(Position from) const;
};

#endif
