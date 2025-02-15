#ifndef RECTITEM_HPP
#define RECTITEM_HPP

#include <QGraphicsRectItem>
#include <QObject>

class SquareItem;

class RectItem : public QObject, public QGraphicsRectItem {
  Q_OBJECT
  SquareItem* squareParent;
  bool isHighlightedSelect = false;
  bool isHighlightedCheck = false;

public:
  explicit RectItem(SquareItem* squareParent, QGraphicsItem* graphicsParent = nullptr);

  void highlightSelectSquare();
  void highlightCheckSquare();
  void unhighlightCheckSquare();
  void unhighlightSelectSquare();

protected:
  void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif
