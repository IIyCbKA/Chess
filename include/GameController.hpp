#ifndef GAMECONTROLLER_HPP
#define GAMECONTROLLER_HPP

#include <models/BoardModel.hpp>
#include <ui/BoardView.hpp>
#include <utils/moveLog.hpp>
#include <utils/position.hpp>
#include <StockfishEngine.hpp>

#include <QObject>

struct PerformMoveData {
  Position from;
  Position to;
  bool isTrackMove = false;
};

class GameController final : public QObject {
  Q_OBJECT;
  BoardModel* model;
  BoardView* view;
  StockfishEngine* stockfishEngine;
  std::optional<PiecesConstants::PIECE_TYPES> promotionPending;
  std::optional<PiecesConstants::PIECE_TYPES> enginePromotionSelection;

  void selectSquare(Position pos) const;
  void deselectSquare() const;
  void tryMovePiece(Position to);
  void performMovePiece(const PerformMoveData& data);
  void movePieceEmit(Position from, Position to);
  void clearCheckAndLastMove() const;
  void endGameCheck();
  void removePieceBeforeMove(Position from, Position to) const;
  [[nodiscard]] QString getFEN() const;

public:
  explicit GameController(BoardView* view, QObject* parent = nullptr);
  void restartGame() const;
  void tryEngineMove() const;
  void updateEngineDepth(size_t depth) const;
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
  void onStockfishMove(const QString& bestMove);
};

#endif //GAMECONTROLLER_HPP
