#ifndef BOARDVIEW_HPP
#define BOARDVIEW_HPP

#include <ui/CoordinateLabel.hpp>
#include <ui/SquareItem.hpp>
#include <utils/BoardTypes.hpp>
#include <utils/highlightFlags.hpp>
#include <constants.hpp>

#include <array>
#include <QGraphicsView>

class BoardView final : public QGraphicsView {
  Q_OBJECT;
  QGraphicsScene* scene = nullptr;
  ViewBoard board{};
  std::vector<CoordinateLabel*> coordinateLabels;
  double boardSize = 0;
  double squareSize = 0;

  void updateSizes();
  void resizeEvent(QResizeEvent* event) override;

public:
  explicit BoardView(QFrame* parent = nullptr);

  void init();
  void cleanBoard() const;
  void setupCoordinateLabels();
  void turningBoard() const;
  void highlightSquare(Position pos) const;
  void showPossibleMoves(const std::vector<Position>& moves) const;
  void clearHighlights(HighlightFlags flags) const;
  void removePiece(Position from) const;
  void highlightCheckSquare(Position pos) const;
  void highlightLastMoveSquares(Position from, Position to) const;
  void setupPiece(
    Position pos,
    PiecesConstants::PIECE_COLORS color,
    PiecesConstants::PIECE_TYPES type
  ) const;
  void applyMoveEffect(
    Position from,
    Position to,
    PiecesConstants::PIECE_COLORS color,
    PiecesConstants::PIECE_TYPES type
  ) const;
  void replacePiece(
    Position pos,
    PiecesConstants::PIECE_COLORS color,
    PiecesConstants::PIECE_TYPES newType
  ) const;

signals:
  void squareClicked(Position pos);

private slots:
  void onSquareClicked(const SquareItem* square);
};

#endif //BOARDVIEW_HPP
