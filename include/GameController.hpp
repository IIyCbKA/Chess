#ifndef GAMECONTROLLER_HPP
#define GAMECONTROLLER_HPP

#include <models/BoardModel.hpp>
#include <ui/BoardView.hpp>
#include <utils/moveLog.hpp>
#include <utils/position.hpp>

#include <QObject>

class GameController : public QObject {
  Q_OBJECT;
  BoardModel* model;
  BoardView* view;

  void selectSquare(Position pos) const;
  void deselectSquare() const;
  void tryMovePiece(Position to);
  void movePieceEmit(Position from, Position to);
  void forceMovePiece(Position from, Position to) const;

public:
  explicit GameController(BoardModel* model, BoardView* view, QObject* parent = nullptr);
  ~GameController() override = default;

signals:
  void moveMade(MoveLog log);

private slots:
  void onSquareClicked(Position pos);
  void onCastlingMoveRook(Position from, Position to) const;
};

#endif //GAMECONTROLLER_HPP
