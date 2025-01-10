#ifndef SQUARE_HPP
#define SQUARE_HPP

#include <Piece.hpp>

#include <QGraphicsRectItem>

using namespace std;

class Square {
  QGraphicsRectItem* rect = nullptr;
  Piece* piece = nullptr;
  size_t xPos = 0;
  size_t yPos = 0;

public:
  explicit Square() = default;

  void revertPos();

  void addRect(QGraphicsRectItem* rect, size_t xPos, size_t yPos);
  void setRectByPos(double squareSize);

  void addPiece(Piece* piece) { this->piece = piece; }
  void pieceSvgIconUpdate(double squareSize) {
    this->piece->svgIconUpdate(this->yPos, this->xPos, squareSize);
  }

  [[nodiscard]] Piece* getPiece() const { return this->piece; }
  [[nodiscard]] QGraphicsRectItem* getRect() const { return this->rect; }
};

#endif
