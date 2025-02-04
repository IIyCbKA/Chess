#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <array>
#include <QColor>
#include <QFont>
#include <QHash>
#include <QString>

QFont createFont(int pointSize);

namespace Colors {
  inline constexpr QColor BEIGE{195, 166, 111};
  inline constexpr QColor BROWN{129, 90, 54};
  inline constexpr QColor DEFAULT_YELLOW{204, 148, 44};
  inline constexpr QColor TRANSPARENT_BLACK{26, 26, 26, 60};
  inline constexpr QColor MIDNIGHT{40, 57, 72};
}

namespace BoardConstants {
  inline constexpr size_t SQUARES_ROWS_COLS = 8;
  inline constexpr size_t PAWN_ROWS_MOVE_FOR_EN_PASSANT = 2;

  inline constexpr size_t CASTLING_FIRST_OFFSET = 1;
  inline constexpr size_t CASTLING_SECOND_OFFSET = 2;
  inline constexpr size_t CASTLING_THIRD_OFFSET = 3;
  inline constexpr size_t KINGSIDE_CASTLING_ROOK_OFFSET = 3;
  inline constexpr size_t QUEENSIDE_CASTLING_ROOK_OFFSET = 4;

  inline constexpr size_t DEFAULT_KINGSIDE_ROOK_COL = 7;
  inline constexpr size_t DEFAULT_QUEENSIDE_ROOK_COL = 0;
  inline constexpr size_t KINGSIDE_CASTLING_NEW_ROOK_COL = 5;
  inline constexpr size_t QUEENSIDE_CASTLING_NEW_ROOK_COL = 3;
}

namespace PiecesConstants {
  enum PIECE_COLORS {
    WHITE,
    BLACK,
  };

  enum PIECE_TYPES {
    KING,
    ROOK,
    KNIGHT,
    BISHOP,
    PAWN,
    QUEEN,
  };

  constexpr std::array<std::pair<int, int>, 4> BISHOP_MOVES = {{
    {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
  }};

  constexpr std::array<std::pair<int, int>, 8> KNIGHT_MOVES = {{
    {2, 1}, {-2, 1}, {-1, -2}, {-1, 2},
    {1, -2}, {1, 2}, {2, -1}, {-2, -1}
  }};

  constexpr std::array<std::pair<int, int>, 8> QUEEN_MOVES = {{
    {-1, 0}, {0, 1}, {1, 0}, {0, -1},
    {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
  }};

  constexpr std::array<std::pair<int, int>, 4> ROOK_MOVES = {{
    {-1, 0}, {0, 1}, {1, 0}, {0, -1}
  }};

  constexpr std::array<std::pair<int, int>, 8> KING_MOVES = {{
    {-1, -1}, {-1, 0}, {-1, 1}, {0, 1},
    {1, 1}, {1, 0}, {1, -1}, {0, -1}
  }};

  const QHash<PIECE_COLORS, std::pair<int, int>> PAWN_DEFAULT_MOVE = {
    {PIECE_COLORS::WHITE, {-1, 0}},
    {PIECE_COLORS::BLACK, {1, 0}},
  };

  const QHash<PIECE_COLORS, std::array<std::pair<int, int>, 2>> PAWN_ATTACK_MOVES = {
    {PIECE_COLORS::WHITE, {{{-1, -1}, {-1, 1}}}},
    {PIECE_COLORS::BLACK, {{{1, -1}, {1, 1}}}},
  };
}

namespace GameStateConstants {
  enum GAME_STATUS {
    ACTIVE,
    END,
  };
}

namespace ConstantsUI {
  inline const auto YOUR_MOVE = QStringLiteral("Your move");
  inline const auto BOT_MOVE = QStringLiteral("Waiting for opponent");

  inline const auto FIRST_HISTORY_TITLE = QString("");
  inline const auto SECOND_HISTORY_TITLE = QStringLiteral("White moves");
  inline const auto THIRD_HISTORY_TITLE = QStringLiteral("Black moves");

  inline const QFont FONT_TEXT = createFont(10);
  inline const QFont FONT_TITLE = createFont(12);

  enum HISTORY_TABLE_COLS {
    NUMBER_OF_PAIR = 0,
    WHITE_MOVE = 1,
    BLACK_MOVE = 2,
  };

  inline const auto HISTORY_DEFAULT_MASK = QStringLiteral("%1%2%3%4");
  inline const auto HISTORY_KINGSIDE_CASTLING = QStringLiteral("O-O");
  inline const auto HISTORY_QUEENSIDE_CASTLING = QStringLiteral("O-O-O");
}

#endif
