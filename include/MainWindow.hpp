#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <GameState.hpp>
#include <ui_App.hpp>

class MainWindow : public QMainWindow {
  Q_OBJECT;
  Ui::MainWindow ui;
  GameState gameState;

public:
  explicit MainWindow(QWidget *parent = nullptr);

  void init() const;

  ~MainWindow() override = default;

private slots:
  void onRestartGameClicked();
};

#endif
