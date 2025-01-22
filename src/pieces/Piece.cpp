#include <pieces/Piece.hpp>
#include <utils/utils.hpp>
#include <ResourceManager.hpp>

Piece::Piece(PiecesConstants::PIECE_COLORS color, PiecesConstants::PIECE_TYPES piece) {
  this->color = color;
  QSvgRenderer* renderer = ResourceManager::instance()
    .getRenderer(color, piece);

  if (renderer) {
    this->svgIcon = new QGraphicsSvgItem();
    this->svgIcon->setSharedRenderer(renderer);
  } else { this->svgIcon = nullptr; }
}


void Piece::svgIconUpdate(const Position curPosition, const double squareSize) {
  this->svgIcon->setPos(curPosition.col * squareSize, curPosition.row * squareSize);
  this->svgIcon->setScale(squareSize / this->svgIcon->boundingRect().width());
}


bool Piece::isWithinBounds(
  const Position curPosition,
  const int moveRow,
  const int moveCol
) {
  const int newRow = static_cast<int>(curPosition.row) + moveRow;
  const int newCol = static_cast<int>(curPosition.col) + moveCol;

  return
    inRange(newRow, 0, BoardConstants::SQUARES_ROWS_COLS) &&
    inRange(newCol, 0, BoardConstants::SQUARES_ROWS_COLS);
}
