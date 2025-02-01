#ifndef GAMECONTROLLER_HPP
#define GAMECONTROLLER_HPP

#include <models/BoardModel.hpp>
#include <ui/BoardView.hpp>
#include <utils/position.hpp>

#include <QObject>

class GameController : public QObject {
  Q_OBJECT;
  BoardModel* model;
  BoardView* view;

  void selectSquare(Position pos) const;
  void deselectSquare() const;
  void tryMovePiece(Position to);

public:
  explicit GameController(BoardModel* model, BoardView* view, QObject* parent = nullptr);
  ~GameController() override = default;

signals:
  void moveMade(Position from, Position to);

private slots:
  void onSquareClicked(Position pos);
};

#endif //GAMECONTROLLER_HPP
