#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <utils/position.hpp>
#include <ui_App.hpp>

class MainWindow : public QMainWindow {
  Q_OBJECT;
  Ui::MainWindow ui;

public:
  explicit MainWindow(QWidget *parent = nullptr);

  void init() const;
  void updateMoveIndicator();

  ~MainWindow() override = default;

private slots:
  void onRestartGameClicked();
  void onMoveMade(Position from, Position to);
};

#endif
