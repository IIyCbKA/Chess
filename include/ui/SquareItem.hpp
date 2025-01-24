#ifndef SQUAREITEM_HPP
#define SQUAREITEM_HPP

#include <ui/RectItem.hpp>
#include <utils/position.hpp>
#include <constants.hpp>

#include <QBrush>
#include <QGraphicsEllipseItem>
#include <QGraphicsSvgItem>
#include <QPointer>

class SquareItem : public QObject {
  Q_OBJECT

  QPointer<QGraphicsSvgItem> svgIcon = nullptr;
  RectItem* rect = nullptr;
  QGraphicsEllipseItem* circle = nullptr;
  const Position realPosition = {0, 0};
  Position drawPosition = {0, 0};
  QBrush brush;

  void setRectByPos(double squareSize) const;
  void setCircleByPos(double squareSize) const;
  void setIconByPos(double squareSize) const;

public:
  explicit SquareItem(Position initPosition, double squareSize);
  void showCircle() const { this->circle->setVisible(true); }
  void hideCircle() const { this->circle->setVisible(false); }

  void updatePosAndSize(double squareSize) const;
  void revertPos(double squareSize);

  void addIcon(
    PiecesConstants::PIECE_COLORS color,
    PiecesConstants::PIECE_TYPES type,
    double squareSize
  );
  void clearIcon();

  [[nodiscard]] QGraphicsSvgItem* getSvgIcon() const { return this->svgIcon; }
  [[nodiscard]] RectItem* getRect() const { return this->rect; }
  [[nodiscard]] Position getRealPos() const { return this->realPosition; }
  [[nodiscard]] QBrush getBrush() const { return this->brush; }

signals:
  void squareClick(SquareItem* square);
};

#endif //SQUAREITEM_HPP
