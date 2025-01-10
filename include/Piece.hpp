#ifndef PIECE_HPP
#define PIECE_HPP

#include <constants.hpp>

#include <QGraphicsSvgItem>

class Piece {
protected:
  QGraphicsSvgItem* svgIcon;
  PiecesConstants::COLORS color;

public:
  Piece(PiecesConstants::COLORS color, PiecesConstants::PIECES piece);

  [[nodiscard]] QGraphicsSvgItem* getSvgIcon() const { return this->svgIcon; }
  void svgIconUpdate(size_t row, size_t col, double squareSize);

  virtual ~Piece() { delete this->svgIcon; }
};

#endif
