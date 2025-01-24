#include <ui/SquareItem.hpp>
#include <constants.hpp>
#include <ResourceManager.hpp>

#include<QPen>

SquareItem::SquareItem(const Position initPosition, const double squareSize)
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


void SquareItem::setRectByPos(const double squareSize) const {
  this->rect->setRect(
    this->drawPosition.col * squareSize,
    this->drawPosition.row * squareSize,
    squareSize,
    squareSize
  );
}


void SquareItem::setCircleByPos(const double squareSize) const {
  const double circleSize = squareSize * 0.3;
  this->circle->setRect(
    this->drawPosition.col * squareSize + (squareSize - circleSize) / 2,
    this->drawPosition.row * squareSize + (squareSize - circleSize) / 2,
    circleSize,
    circleSize
  );
}


void SquareItem::setIconByPos(const double squareSize) const {
  if (this->svgIcon) {
    this->svgIcon->setPos(
      this->drawPosition.col * squareSize,
      this->drawPosition.row * squareSize
    );
    this->svgIcon->setScale(squareSize / this->svgIcon->boundingRect().width());
  }
}


void SquareItem::updatePosAndSize(const double squareSize) const {
  setRectByPos(squareSize);
  setCircleByPos(squareSize);
  setIconByPos(squareSize);
}


void SquareItem::revertPos(const double squareSize) {
  this->drawPosition.col = BoardConstants::SQUARES_ROWS_COLS - 1 - this->drawPosition.col;
  this->drawPosition.row = BoardConstants::SQUARES_ROWS_COLS - 1 - this->drawPosition.row;
  updatePosAndSize(squareSize);
}


void SquareItem::addIcon(
  const PiecesConstants::PIECE_COLORS color,
  const PiecesConstants::PIECE_TYPES type,
  const double squareSize
) {
  QSvgRenderer* renderer = ResourceManager::instance().getRenderer(color, type);

  if (renderer) {
    this->svgIcon = new QGraphicsSvgItem();
    this->svgIcon->setSharedRenderer(renderer);
    this->svgIcon->setParentItem(this->rect);
    setIconByPos(squareSize);
  } else { this->svgIcon = nullptr; }
}


void SquareItem::clearIcon() {
  delete this->svgIcon;
}
