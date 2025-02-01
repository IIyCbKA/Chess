#ifndef ENPASSANT_HPP
#define ENPASSANT_HPP

#include <utils/position.hpp>
#include <constants.hpp>

struct EnPassant {
  Position pawnPosition;
  Position enPassantPosition;
  PiecesConstants::PIECE_COLORS pawnColor;
};

#endif //ENPASSANT_HPP
