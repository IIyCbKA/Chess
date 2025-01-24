#ifndef RECTITEM_HPP
#define RECTITEM_HPP

#include <QGraphicsRectItem>
#include <QObject>

class SquareItem;

class RectItem : public QObject, public QGraphicsRectItem {
  Q_OBJECT
  SquareItem* squareParent;

public:
  explicit RectItem(SquareItem* squareParent, QGraphicsItem* graphicsParent = nullptr);

  void selectSquare();
  void deselectSquare();

protected:
  void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif
