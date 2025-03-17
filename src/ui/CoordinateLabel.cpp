#include <ui/CoordinateLabel.hpp>
#include <utils/utils.hpp>

#include <QChar>

CoordinateLabel::CoordinateLabel(
  const Position position,
  const BoardConstants::COORDINATES_TYPE type,
  QGraphicsItem* parent
)
  : QGraphicsTextItem(parent), type(type), position(position)
{
  this->character = this->type == BoardConstants::COORDINATES_TYPE::ROWS
    ? static_cast<char>(BoardConstants::MAX_ROW_COORDINATE - this->position.row)
    : static_cast<char>(BoardConstants::MIN_COL_COORDINATE + this->position.col);

  this->setPlainText(QChar(this->character));
  this->setZValue(BoardConstants::DEFAULT_COORDINATES_Z_INDEX);
  this->setDefaultTextColor(getRevertSquareColor(this->position));
}


void CoordinateLabel::updatePosition(const double squareSize) {
  this->setFont(
    createFont(static_cast<int>(squareSize * BoardConstants::FONT_SIZE_DEPENDS_ON_SQUARE))
  );

  double x = static_cast<double>(this->position.col) * squareSize;
  double y = static_cast<double>(this->position.row) * squareSize;
  if (this->type == BoardConstants::COORDINATES_TYPE::COLS) {
    const QRectF rect = this->boundingRect();
    x += squareSize - rect.width();
    y += squareSize - rect.height();
  }

  this->setPos(x, y);
}


void CoordinateLabel::updateCharAfterTurningBoard() {
  if (this->type == BoardConstants::COORDINATES_TYPE::ROWS) {
    this->character = getNewChar(
      BoardConstants::MAX_ROW_COORDINATE,
      BoardConstants::MIN_ROW_COORDINATE
    );
  } else {
    this->character = getNewChar(
      BoardConstants::MAX_COL_COORDINATE,
      BoardConstants::MIN_COL_COORDINATE
    );
  }

  this->setPlainText(QChar(this->character));
}


char CoordinateLabel::getNewChar(
  const char maxCoordinateChar,
  const char minCoordinateChar
) const {
  return static_cast<char>(maxCoordinateChar - (this->character - minCoordinateChar));
}
