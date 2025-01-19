#ifndef RECTITEM_HPP
#define RECTITEM_HPP

#include <QGraphicsRectItem>
#include <QObject>

class Square;

class RectItem : public QObject, public QGraphicsRectItem {
  Q_OBJECT
  Square* squareParent;

public:
  explicit RectItem(Square* squareParent, QGraphicsItem* graphicsParent = nullptr);

  void selectSquare();
  void deselectSquare();

protected:
  void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif
