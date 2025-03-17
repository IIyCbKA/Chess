#ifndef BOARDTYPES_HPP
#define BOARDTYPES_HPP

#include <constants.hpp>

#include <array>
#include <bitset>
#include <memory>

class Piece;
class SquareItem;

using ModelBoard = std::array<
  std::array<std::unique_ptr<Piece>, BoardConstants::SQUARES_ROWS_COLS>,
  BoardConstants::SQUARES_ROWS_COLS
>;

using ViewBoard = std::array<
  std::array<SquareItem*, BoardConstants::SQUARES_ROWS_COLS>,
  BoardConstants::SQUARES_ROWS_COLS
>;

using AttackMap = std::array<
  std::bitset<BoardConstants::SQUARES_ROWS_COLS>,
  BoardConstants::SQUARES_ROWS_COLS
>;

#endif //BOARDTYPES_HPP
