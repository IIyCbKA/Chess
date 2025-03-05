#ifndef RECTITEM_HPP
#define RECTITEM_HPP

#include <QGraphicsRectItem>
#include <QObject>

class SquareItem;

class RectItem final : public QObject, public QGraphicsRectItem {
  Q_OBJECT
  SquareItem* squareParent;
  bool isHighlightedSelect = false;
  bool isHighlightedCheck = false;
  bool isHighlightedLastMove = false;

public:
  explicit RectItem(SquareItem* squareParent, QGraphicsItem* graphicsParent = nullptr);

  void highlightSelectSquare();
  void highlightCheckSquare();
  void highlightLastMove();
  void unhighlightCheckSquare();
  void unhighlightSelectSquare();
  void unhighlightLastMove();

protected:
  void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif
