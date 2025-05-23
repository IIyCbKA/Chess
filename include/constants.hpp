#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <utils/position.hpp>

#include <array>
#include <QColor>
#include <QFont>
#include <QHash>
#include <QString>

#define PAWN_TYPE PiecesConstants::PIECE_TYPES::PAWN
#define ROOK_TYPE PiecesConstants::PIECE_TYPES::ROOK
#define BISHOP_TYPE PiecesConstants::PIECE_TYPES::BISHOP
#define QUEEN_TYPE PiecesConstants::PIECE_TYPES::QUEEN
#define KING_TYPE PiecesConstants::PIECE_TYPES::KING
#define KNIGHT_TYPE PiecesConstants::PIECE_TYPES::KNIGHT

#define BLACK_COLOR PiecesConstants::PIECE_COLORS::BLACK
#define WHITE_COLOR PiecesConstants::PIECE_COLORS::WHITE

QFont createFont(int pointSize);

namespace Colors {
  inline constexpr QColor BEIGE{195, 166, 111};
  inline constexpr QColor HIGHLIGHTED_LAST_MOVE_BEIGE{179, 180, 65};
  inline constexpr QColor HIGHLIGHTED_SELECTED_BEIGE{108, 126, 71};
  inline constexpr QColor BROWN{129, 90, 54};
  inline constexpr QColor HIGHLIGHTED_LAST_MOVE_BROWN{140, 135, 32};
  inline constexpr QColor HIGHLIGHTED_SELECTED_BROWN{75, 88, 42};
  inline constexpr QColor PASTEL_RED{219, 88, 86};
  inline constexpr QColor TRANSPARENT_BLACK{26, 26, 26, 60};
  inline constexpr QColor MIDNIGHT{40, 57, 72};
}

namespace PiecesConstants {
  inline constexpr char QUEEN_CHAR =  'Q';
  inline constexpr char ROOK_CHAR =   'R';
  inline constexpr char KNIGHT_CHAR = 'N';
  inline constexpr char BISHOP_CHAR = 'B';
  inline constexpr char KING_CHAR =   'K';
  inline constexpr char PAWN_CHAR =   'P';

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
  inline const auto STOCKFISH_PATH_IN_BUILD = QStringLiteral("/stockfish");

  const QHash<
    PiecesConstants::PIECE_COLORS,
    QHash<PiecesConstants::PIECE_TYPES, QString>
  > PIECES_PATHS = {
    {
      WHITE_COLOR, {
        {KING_TYPE,   QStringLiteral(":images/wKing.svg")},
        {QUEEN_TYPE,  QStringLiteral(":images/wQueen.svg")},
        {ROOK_TYPE,   QStringLiteral(":images/wRook.svg")},
        {KNIGHT_TYPE, QStringLiteral(":images/wKnight.svg")},
        {BISHOP_TYPE, QStringLiteral(":images/wBishop.svg")},
        {PAWN_TYPE,   QStringLiteral(":images/wPawn.svg")},
      },
    },
    {
      BLACK_COLOR, {
        {KING_TYPE,   QStringLiteral(":images/bKing.svg")},
        {QUEEN_TYPE,  QStringLiteral(":images/bQueen.svg")},
        {ROOK_TYPE,   QStringLiteral(":images/bRook.svg")},
        {KNIGHT_TYPE, QStringLiteral(":images/bKnight.svg")},
        {BISHOP_TYPE, QStringLiteral(":images/bBishop.svg")},
        {PAWN_TYPE,   QStringLiteral(":images/bPawn.svg")},
      },
    },
  };
}

namespace GameStateConstants {
  inline constexpr size_t DEFAULT_FULL_MOVE_NUMBER = 1;

  enum GAME_STATUS {
    ACTIVE,
    CHECKMATE,
    STALEMATE,
  };
}

namespace ConstantsUI {
  inline constexpr size_t SCENE_X_INDENTATION = 0;
  inline constexpr size_t SCENE_Y_INDENTATION = 0;

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
    COUNT = 3,
  };

  inline constexpr size_t EMPTY_HISTORY_TABLE_ROWS = 0;
  inline constexpr size_t HISTORY_TABLE_COL_NUMBER_OF_PAIR_WIDTH = 64;

  inline const auto HISTORY_DEFAULT_MASK = QStringLiteral("%1%2%3%4");
  inline const auto HISTORY_KINGSIDE_CASTLING = QStringLiteral("O-O");
  inline const auto HISTORY_QUEENSIDE_CASTLING = QStringLiteral("O-O-O");

  inline const auto HISTORY_PROMOTION_TO_QUEEN  = QStringLiteral("=Q");
  inline const auto HISTORY_PROMOTION_TO_ROOK   = QStringLiteral("=R");
  inline const auto HISTORY_PROMOTION_TO_KNIGHT = QStringLiteral("=N");
  inline const auto HISTORY_PROMOTION_TO_BISHOP = QStringLiteral("=B");

  inline constexpr size_t DIALOG_BTN_ICON_WIDTH = 80;
  inline constexpr size_t DIALOG_BTN_ICON_HEIGHT = 80;

  const QHash<
    PiecesConstants::PIECE_COLORS, // active color
    QHash<GameStateConstants::GAME_STATUS, QString>
  > ENDGAME_TEXTS = {
    {
      BLACK_COLOR, {
        {GameStateConstants::GAME_STATUS::CHECKMATE, QStringLiteral("White checkmated!")},
        {GameStateConstants::GAME_STATUS::STALEMATE, QStringLiteral("White stalemated!")},
      }
    },
    {
      WHITE_COLOR, {
        {GameStateConstants::GAME_STATUS::CHECKMATE, QStringLiteral("Black checkmated!")},
        {GameStateConstants::GAME_STATUS::STALEMATE, QStringLiteral("Black stalemated!")},
      }
    },
  };

  inline const auto DEFAULT_DIFFICULTY_BTN_STYLESHEET = QStringLiteral(
    "QPushButton {\n background-color: rgb(70, 66, 65);\n outline: none;\n"
      "border: none;\n border-radius: 10px;\n}\n\n"
    "QPushButton:hover {\n background-color: rgb(82, 78, 77);\n}\n\n"
    "QPushButton:pressed {\n padding: 0;\n background-color: rgb(63, 59, 58);\n}\n");

  inline const auto SELECTED_DIFFICULTY_BTN_STYLESHEET = QStringLiteral(
    "QPushButton {\n background-color: rgb(70, 66, 65);\n outline: none;\n"
      "border: 2px solid rgb(252, 252, 252);\n border-radius: 10px;\n}\n\n"
    "QPushButton:hover {\n background-color: rgb(82, 78, 77);\n}\n\n"
    "QPushButton:pressed {\n padding: 0;\n background-color: rgb(63, 59, 58);\n}\n");
}

namespace ConstantsFEN {
  const QHash<PiecesConstants::PIECE_COLORS, char> colorInFEN = {
    {WHITE_COLOR, 'w'},
    {BLACK_COLOR, 'b'},
  };

  const QHash<
    PiecesConstants::PIECE_COLORS,
    QHash<PiecesConstants::PIECE_TYPES, char>
  > piecesInFEN = {
    {
      WHITE_COLOR, {
          {PAWN_TYPE,   'P'},
          {ROOK_TYPE,   'R'},
          {KNIGHT_TYPE, 'N'},
          {BISHOP_TYPE, 'B'},
          {QUEEN_TYPE,  'Q'},
          {KING_TYPE,   'K'},
        },
      },
      {
        BLACK_COLOR, {
          {PAWN_TYPE,   'p'},
          {ROOK_TYPE,   'r'},
          {KNIGHT_TYPE, 'n'},
          {BISHOP_TYPE, 'b'},
          {QUEEN_TYPE,  'q'},
          {KING_TYPE,   'k'},
        },
      },
    };

  inline constexpr char ROW_DIVIDER_FOR_BOARD = '/';
  inline constexpr char EMPTY_EN_PASSANT = '-';
  inline constexpr char WHITE_KINGSIDE_CASTLING_FEN = 'K';
  inline constexpr char WHITE_QUEENSIDE_CASTLING_FEN = 'Q';
  inline constexpr char BLACK_KINGSIDE_CASTLING_FEN = 'k';
  inline constexpr char BLACK_QUEENSIDE_CASTLING_FEN = 'q';
  inline constexpr char EMPTY_CASTLING_FEN = '-';

  inline const auto FEN_DEFAULT_MASK = QStringLiteral("%1 %2 %3 %4 %5 %6");
}

namespace StockfishConstants {
  inline const auto STOCKFISH_ERROR = QStringLiteral("Stockfish don't started");
  inline const auto SET_POSITION_MASK = QStringLiteral("position fen %1\n");
  inline const auto CALCULATE_MOVE_MASK = QStringLiteral("go depth %1\n");
  inline const auto DEBUG_TITLE = QStringLiteral("Stockfish:");
  inline const auto BESTMOVE_LINE_START = QStringLiteral("bestmove");
  inline const auto BESTMOVE_SEPARATOR = QStringLiteral(" ");

  inline constexpr size_t MIN_VALID_BESTMOVE_TOKENS = 2;
  inline constexpr size_t BESTMOVE_TOKEN_IND = 1;
  inline constexpr size_t BESTMOVE_SIZE_WITH_PROMOTION = 5;

  inline constexpr size_t BESTMOVE_FROM_ROW_IND = 1;
  inline constexpr size_t BESTMOVE_FROM_COL_IND = 0;
  inline constexpr size_t BESTMOVE_TO_ROW_IND = 3;
  inline constexpr size_t BESTMOVE_TO_COL_IND = 2;
  inline constexpr size_t BESTMOVE_PROMOTION_IND = 4;

  inline constexpr size_t EASY_DEPTH   = 3;
  inline constexpr size_t MEDIUM_DEPTH = 5;
  inline constexpr size_t HARD_DEPTH   = 7;
}

namespace BoardConstants {
  inline constexpr size_t SQUARES_ROWS_COLS = 8;
  inline constexpr size_t PAWN_ROWS_MOVE_FOR_EN_PASSANT = 2;

  const std::vector<size_t> KINGSIDE_CASTLING_CHECKED_COLS = {5, 6};
  const std::vector<size_t> QUEENSIDE_CASTLING_CHECKED_COLS = {1, 2, 3};

  inline constexpr size_t DEFAULT_KINGSIDE_ROOK_COL = 7;
  inline constexpr size_t DEFAULT_QUEENSIDE_ROOK_COL = 0;
  inline constexpr size_t KINGSIDE_CASTLING_NEW_ROOK_COL = 5;
  inline constexpr size_t QUEENSIDE_CASTLING_NEW_ROOK_COL = 3;
  inline constexpr size_t KINGSIDE_CASTLING_NEW_KING_COL = 6;
  inline constexpr size_t QUEENSIDE_CASTLING_NEW_KING_COL = 2;

  inline const Position DEFAULT_WHITE_KING_POS = {7, 4};
  inline const Position DEFAULT_WHITE_QUEEN_ROOK_POS = {7, 0};
  inline const Position DEFAULT_WHITE_KING_ROOK_POS = {7, 7};

  inline const Position DEFAULT_BLACK_KING_POS = {0, 4};
  inline const Position DEFAULT_BLACK_QUEEN_ROOK_POS = {0, 0};
  inline const Position DEFAULT_BLACK_KING_ROOK_POS = {0, 7};

  inline constexpr size_t DEFAULT_COORDINATES_Z_INDEX = 1;
  inline constexpr size_t DEFAULT_COL_FOR_ROWS_COORDINATES = 0;
  inline constexpr size_t DEFAULT_ROW_FOR_COLS_COORDINATES = 7;

  enum COORDINATES_TYPE {
    ROWS = 0,
    COLS = 1,
  };

  inline constexpr char MAX_ROW_COORDINATE = '8';
  inline constexpr char MIN_ROW_COORDINATE = '1';
  inline constexpr char MAX_COL_COORDINATE = 'h';
  inline constexpr char MIN_COL_COORDINATE = 'a';
  inline constexpr double FONT_SIZE_DEPENDS_ON_SQUARE = 0.125;

  const QHash<size_t, char> NUM_COL_TO_CHAR = {
    {0, 'a'},
    {1, 'b'},
    {2, 'c'},
    {3, 'd'},
    {4, 'e'},
    {5, 'f'},
    {6, 'g'},
    {7, 'h'},
  };

  const QHash<char, size_t> CHAR_TO_NUM_COL = {
    {'a', 0},
    {'b', 1},
    {'c', 2},
    {'d', 3},
    {'e', 4},
    {'f', 5},
    {'g', 6},
    {'h', 7},
  };

  const QHash<char, size_t> CHAR_NUM_TO_NUM = {
    {'8', 0},
    {'7', 1},
    {'6', 2},
    {'5', 3},
    {'4', 4},
    {'3', 5},
    {'2', 6},
    {'1', 7},
  };

  const std::array<std::tuple<
    Position,
    PiecesConstants::PIECE_COLORS,
    PiecesConstants::PIECE_TYPES
  >, 32> STANDARD_SETUP = {{
    {{0, 0}, BLACK_COLOR, ROOK_TYPE  },
    {{0, 1}, BLACK_COLOR, KNIGHT_TYPE},
    {{0, 2}, BLACK_COLOR, BISHOP_TYPE},
    {{0, 3}, BLACK_COLOR, QUEEN_TYPE },
    {{0, 4}, BLACK_COLOR, KING_TYPE  },
    {{0, 5}, BLACK_COLOR, BISHOP_TYPE},
    {{0, 6}, BLACK_COLOR, KNIGHT_TYPE},
    {{0, 7}, BLACK_COLOR, ROOK_TYPE  },

    {{1, 0}, BLACK_COLOR, PAWN_TYPE  },
    {{1, 1}, BLACK_COLOR, PAWN_TYPE  },
    {{1, 2}, BLACK_COLOR, PAWN_TYPE  },
    {{1, 3}, BLACK_COLOR, PAWN_TYPE  },
    {{1, 4}, BLACK_COLOR, PAWN_TYPE  },
    {{1, 5}, BLACK_COLOR, PAWN_TYPE  },
    {{1, 6}, BLACK_COLOR, PAWN_TYPE  },
    {{1, 7}, BLACK_COLOR, PAWN_TYPE  },

    {{7, 0}, WHITE_COLOR, ROOK_TYPE  },
    {{7, 1}, WHITE_COLOR, KNIGHT_TYPE},
    {{7, 2}, WHITE_COLOR, BISHOP_TYPE},
    {{7, 3}, WHITE_COLOR, QUEEN_TYPE },
    {{7, 4}, WHITE_COLOR, KING_TYPE  },
    {{7, 5}, WHITE_COLOR, BISHOP_TYPE},
    {{7, 6}, WHITE_COLOR, KNIGHT_TYPE},
    {{7, 7}, WHITE_COLOR, ROOK_TYPE  },

    {{6, 0}, WHITE_COLOR, PAWN_TYPE  },
    {{6, 1}, WHITE_COLOR, PAWN_TYPE  },
    {{6, 2}, WHITE_COLOR, PAWN_TYPE  },
    {{6, 3}, WHITE_COLOR, PAWN_TYPE  },
    {{6, 4}, WHITE_COLOR, PAWN_TYPE  },
    {{6, 5}, WHITE_COLOR, PAWN_TYPE  },
    {{6, 6}, WHITE_COLOR, PAWN_TYPE  },
    {{6, 7}, WHITE_COLOR, PAWN_TYPE  },
  }};
}

#endif
