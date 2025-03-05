#ifndef COORDINATELABEL_HPP
#define COORDINATELABEL_HPP

#include <utils/position.hpp>
#include <constants.hpp>

#include <QGraphicsTextItem>

class CoordinateLabel final : public QGraphicsTextItem {
  BoardConstants::COORDINATES_TYPE type;
  Position position;
  char character;

  [[nodiscard]] char getNewChar(char maxCoordinateChar, char minCoordinateChar) const;

public:
  CoordinateLabel(
    Position position,
    BoardConstants::COORDINATES_TYPE type,
    QGraphicsItem* parent = nullptr
  );
  void updatePosition(double squareSize);
  void updateCharAfterTurningBoard();
};

#endif //COORDINATELABEL_HPP
