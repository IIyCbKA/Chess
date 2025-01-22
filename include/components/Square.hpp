#ifndef SQUARE_HPP
#define SQUARE_HPP

#include <components/RectItem.hpp>
#include <pieces/Piece.hpp>
#include <utils/position.hpp>

#include <QBrush>
#include <QGraphicsEllipseItem>

using namespace std;

class Square : public QObject {
  Q_OBJECT

  RectItem* rect = nullptr;
  QGraphicsEllipseItem* circle = nullptr;
  unique_ptr<Piece> piece = nullptr;
  const Position realPosition = {0, 0};
  Position drawPosition = {0, 0};
  QBrush brush;

public:
  explicit Square(Position initPosition, double squareSize);

  void revertPos();
  void setRectByPos(double squareSize);

  void setCircleByPos(double squareSize);
  void showCircle() { circle->setVisible(true); }
  void hideCircle() { circle->setVisible(false); }

  void addPiece(unique_ptr<Piece> piece) { this->piece = std::move(piece); }
  void pieceSvgIconUpdate(const double squareSize) {
    this->piece->svgIconUpdate(this->drawPosition, squareSize);
  }
  void clearPiece();

  [[nodiscard]] Piece* getPiece() const { return this->piece.get(); }
  [[nodiscard]] RectItem* getRect() const { return this->rect; }
  [[nodiscard]] Position getRealPos() const { return this->realPosition; }
  [[nodiscard]] QBrush getBrush() const { return this->brush; }
  [[nodiscard]] unique_ptr<Piece> releasePiece() { return std::move(this->piece); }

signals:
  void squareClick(Square* square);
};

#endif
