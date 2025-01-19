#include <pieces/Piece.hpp>
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
