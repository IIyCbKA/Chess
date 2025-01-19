#include <components/RectItem.hpp>
#include <components/Square.hpp>
#include <constants.hpp>

#include <QBrush>

RectItem::RectItem(Square* squareParent, QGraphicsItem* graphicsParent)
  : QGraphicsRectItem(graphicsParent), squareParent(squareParent)
{
  setAcceptHoverEvents(true);
  setAcceptedMouseButtons(Qt::LeftButton);
}


void RectItem::mousePressEvent(QGraphicsSceneMouseEvent* event) {
  this->squareParent->squareClick(this->squareParent);
  QGraphicsRectItem::mousePressEvent(event);
}


void RectItem::selectSquare() {
  this->setBrush(QBrush(Colors::DEFAULT_YELLOW));
}


void RectItem::deselectSquare() {
  this->setBrush(this->squareParent->getBrush());
}
