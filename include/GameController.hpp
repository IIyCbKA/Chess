#ifndef GAMECONTROLLER_HPP
#define GAMECONTROLLER_HPP

#include <models/BoardModel.hpp>
#include <ui/BoardView.hpp>
#include <utils/moveLog.hpp>
#include <utils/position.hpp>

#include <QObject>

struct PerformMoveData {
  Position from;
  Position to;
  bool emitLog = false;
};

class GameController : public QObject {
  Q_OBJECT;
  BoardModel* model;
  BoardView* view;
  std::optional<PiecesConstants::PIECE_TYPES> promotionPending;

  void selectSquare(Position pos) const;
  void deselectSquare() const;
  void tryMovePiece(Position to);
  void performMovePiece(const PerformMoveData& data);
  void movePieceEmit(Position from, Position to);
  void forceMovePiece(Position from, Position to);
  void clearCheck() const;
  void endGameCheck();

public:
  explicit GameController(BoardModel* model, BoardView* view, QObject* parent = nullptr);
  void changePawnType(
    Position pos,
    PiecesConstants::PIECE_TYPES newType,
    PiecesConstants::PIECE_COLORS color
  );
  ~GameController() override = default;

signals:
  void moveMade(MoveLog log);
  void pawnPromotion(Position pos, PiecesConstants::PIECE_COLORS color);
  void endGame();

private slots:
  void onSquareClicked(Position pos);
  void onCastlingMoveRook(Position from, Position to);
  void onPawnPromotion(Position pos, PiecesConstants::PIECE_COLORS color);
  void onCheck(Position pos, PiecesConstants::PIECE_COLORS color) const;
};

#endif //GAMECONTROLLER_HPP
