#include <ui/RectItem.hpp>
#include <ui/SquareItem.hpp>
#include <constants.hpp>

#include <QBrush>

RectItem::RectItem(SquareItem* squareParent, QGraphicsItem* graphicsParent)
  : QGraphicsRectItem(graphicsParent), squareParent(squareParent)
{
  setAcceptHoverEvents(true);
  setAcceptedMouseButtons(Qt::LeftButton);
}


void RectItem::mousePressEvent(QGraphicsSceneMouseEvent* event) {
  this->squareParent->squareClick(this->squareParent);
  QGraphicsRectItem::mousePressEvent(event);
}


void RectItem::highlightSelectSquare() {
  this->isHighlightedSelect = true;
  this->setBrush(QBrush(Colors::YELLOW));
}


void RectItem::highlightCheckSquare() {
  this->isHighlightedCheck = true;
  this->setBrush(QBrush(Colors::PASTEL_RED));
}


void RectItem::unhighlightSelectSquare() {
  if (this->isHighlightedSelect) {
    this->isHighlightedSelect = false;
    if (this->isHighlightedCheck) this->setBrush(QBrush(Colors::PASTEL_RED));
    else this->setBrush(this->squareParent->getBrush());
  }
}


void RectItem::unhighlightCheckSquare() {
  if (this->isHighlightedCheck) {
    this->isHighlightedCheck = false;
    this->setBrush(this->squareParent->getBrush());
  }
}
