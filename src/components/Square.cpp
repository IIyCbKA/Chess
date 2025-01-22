#include <components/Square.hpp>
#include <constants.hpp>

#include<QBrush>
#include<QPen>

Square::Square(const Position initPosition, const double squareSize)
  : rect(new RectItem(this)), circle(new QGraphicsEllipseItem(rect)),
    realPosition(initPosition)
{
  this->drawPosition = this->realPosition;

  this->brush = (this->drawPosition.row + this->drawPosition.col) % 2 == 0
    ? QBrush(Colors::BEIGE)
    : QBrush(Colors::BROWN);

  setRectByPos(squareSize);
  this->rect->setBrush(this->brush);
  this->rect->setPen(Qt::NoPen);

  setCircleByPos(squareSize);
  this->circle->setBrush(Colors::TRANSPARENT_BLACK);
  this->circle->setPen(Qt::NoPen);
  hideCircle();
}


void Square::setRectByPos(const double squareSize) {
  this->rect->setRect(
    this->drawPosition.col * squareSize,
    this->drawPosition.row * squareSize,
    squareSize,
    squareSize
  );
}


void Square::setCircleByPos(const double squareSize) {
  const double circleSize = squareSize * 0.3;
  this->circle->setRect(
    this->drawPosition.col * squareSize + (squareSize - circleSize) / 2,
    this->drawPosition.row * squareSize + (squareSize - circleSize) / 2,
    circleSize,
    circleSize
  );
}


void Square::revertPos() {
  this->drawPosition.col = BoardConstants::SQUARES_ROWS_COLS - 1 - this->drawPosition.col;
  this->drawPosition.row = BoardConstants::SQUARES_ROWS_COLS - 1 - this->drawPosition.row;
}


void Square::clearPiece() {
  if (this->piece->getSvgIcon()) delete this->piece->getSvgIcon();
  this->piece.reset();
}
