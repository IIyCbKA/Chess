#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <QColor>

namespace BoardConstants {
  constexpr size_t SQUARES_ROWS_COLS = 8;

  namespace COLORS {
    inline const QColor BEIGE("#c3a66f");
    inline const QColor BROWN("#815a36");
  }
}

namespace PiecesConstants {
  enum COLORS {
    WHITE,
    BLACK,
  };

  enum PIECES {
    KING,
    ROOK,
    KNIGHT,
    BISHOP,
    PAWN,
    QUEEN,
  };
}


namespace GameStateConstants {
  enum GAME_STATUS {
    ACTIVE,
    END,
  };
}

#endif
