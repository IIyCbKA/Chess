#include <Piece.hpp>
#include <ResourceManager.hpp>

Piece::Piece(PiecesConstants::COLORS color, PiecesConstants::PIECES piece) {
  this->color = color;
  QSvgRenderer* renderer = ResourceManager::instance()
    .getRenderer(color, piece);

  if (renderer) {
    this->svgIcon = new QGraphicsSvgItem();
    this->svgIcon->setSharedRenderer(renderer);
  } else { this->svgIcon = nullptr; }
}


void Piece::svgIconUpdate(size_t row, size_t col, double squareSize) {
  this->svgIcon->setPos(col * squareSize, row * squareSize);
  this->svgIcon->setScale(squareSize / this->svgIcon->boundingRect().width());
}
