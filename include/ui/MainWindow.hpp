#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <ui/ui_App.hpp>
#include <utils/position.hpp>

class MainWindow : public QMainWindow {
  Q_OBJECT;
  Ui::MainWindow ui;
  BoardModel* boardModel = nullptr;

  void updateMoveIndicator() const;

public:
  explicit MainWindow(QWidget *parent = nullptr);

  void init() const;

  ~MainWindow() override = default;

private slots:
  void onRestartGameClicked() const;
  void onMoveMade(Position from, Position to) const;
  void onModelBoardReset() const;
  void onPieceMoved(Position from, Position to) const;
  void onPieceRemoved(Position from) const;
};

#endif
