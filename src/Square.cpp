#include <constants.hpp>
#include <Square.hpp>

#include <iostream>

void Square::addRect(
  QGraphicsRectItem *rect,
  const size_t xPos,
  const size_t yPos
) {
  this->rect = rect;
  this->xPos = xPos;
  this->yPos = yPos;
}


void Square::setRectByPos(double squareSize) {
  this->rect->setRect(
    this->xPos * squareSize,
    this->yPos * squareSize,
    squareSize,
    squareSize
  );
}


void Square::revertPos() {
  this->xPos = BoardConstants::SQUARES_ROWS_COLS - 1 - this->xPos;
  this->yPos = BoardConstants::SQUARES_ROWS_COLS - 1 - this->yPos;
}
