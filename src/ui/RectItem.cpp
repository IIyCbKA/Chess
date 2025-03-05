#include <ui/RectItem.hpp>
#include <ui/SquareItem.hpp>
#include <utils/utils.hpp>
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
  this->setBrush(getHighlightSelectedColor(this->squareParent->getBrush().color()));
}


void RectItem::highlightCheckSquare() {
  this->isHighlightedCheck = true;
  this->setBrush(QBrush(Colors::PASTEL_RED));
}


void RectItem::highlightLastMove() {
  this->isHighlightedLastMove = true;
  this->setBrush(getHighlightLastMoveColor(this->squareParent->getBrush().color()));
}


void RectItem::unhighlightSelectSquare() {
  if (this->isHighlightedSelect) {
    this->isHighlightedSelect = false;
    if (this->isHighlightedCheck) highlightCheckSquare();
    else if (this->isHighlightedLastMove) highlightLastMove();
    else this->setBrush(this->squareParent->getBrush());
  }
}


void RectItem::unhighlightCheckSquare() {
  if (this->isHighlightedCheck) {
    this->isHighlightedCheck = false;
    this->setBrush(this->squareParent->getBrush());
  }
}


void RectItem::unhighlightLastMove() {
  if (this->isHighlightedLastMove) {
    this->isHighlightedLastMove = false;
    this->setBrush(this->squareParent->getBrush());
  }
}
