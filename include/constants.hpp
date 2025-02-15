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
  inline constexpr QColor YELLOW{204, 148, 44};
  inline constexpr QColor PASTEL_RED{219, 88, 86};
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

namespace ResourcesConstants {
  const QHash<
    PiecesConstants::PIECE_COLORS,
    QHash<PiecesConstants::PIECE_TYPES, QString>
  > PIECES_PATHS = {
    {
      PiecesConstants::PIECE_COLORS::WHITE,
      {
        {PiecesConstants::PIECE_TYPES::KING,   QStringLiteral(":images/wKing.svg")},
        {PiecesConstants::PIECE_TYPES::QUEEN,  QStringLiteral(":images/wQueen.svg")},
        {PiecesConstants::PIECE_TYPES::ROOK,   QStringLiteral(":images/wRook.svg")},
        {PiecesConstants::PIECE_TYPES::KNIGHT, QStringLiteral(":images/wKnight.svg")},
        {PiecesConstants::PIECE_TYPES::BISHOP, QStringLiteral(":images/wBishop.svg")},
        {PiecesConstants::PIECE_TYPES::PAWN,   QStringLiteral(":images/wPawn.svg")},
      },
    },
    {
      PiecesConstants::PIECE_COLORS::BLACK,
      {
        {PiecesConstants::PIECE_TYPES::KING,   QStringLiteral(":images/bKing.svg")},
        {PiecesConstants::PIECE_TYPES::QUEEN,  QStringLiteral(":images/bQueen.svg")},
        {PiecesConstants::PIECE_TYPES::ROOK,   QStringLiteral(":images/bRook.svg")},
        {PiecesConstants::PIECE_TYPES::KNIGHT, QStringLiteral(":images/bKnight.svg")},
        {PiecesConstants::PIECE_TYPES::BISHOP, QStringLiteral(":images/bBishop.svg")},
        {PiecesConstants::PIECE_TYPES::PAWN,   QStringLiteral(":images/bPawn.svg")},
      },
    },
  };
}

namespace GameStateConstants {
  enum GAME_STATUS {
    ACTIVE,
    CHECKMATE,
    STALEMATE,
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

  inline const auto HISTORY_PROMOTION_TO_QUEEN  = QStringLiteral("=Q");
  inline const auto HISTORY_PROMOTION_TO_ROOK   = QStringLiteral("=R");
  inline const auto HISTORY_PROMOTION_TO_KNIGHT = QStringLiteral("=N");
  inline const auto HISTORY_PROMOTION_TO_BISHOP = QStringLiteral("=B");

  inline constexpr size_t DIALOG_BTN_ICON_WIDTH = 80;
  inline constexpr size_t DIALOG_BTN_ICON_HEIGHT = 80;

  inline const auto WHITE_CHECKMATED = QStringLiteral("White checkmated!");
  inline const auto BLACK_CHECKMATED = QStringLiteral("Black checkmated!");
  inline const auto WHITE_STALEMATED = QStringLiteral("White stalemated!");
  inline const auto BLACK_STALEMATED = QStringLiteral("Black stalemated!");
}

#endif
