#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <constants.hpp>

class GameState {
  PiecesConstants::PIECE_COLORS userColor;
  PiecesConstants::PIECE_COLORS activeColor;
  GameStateConstants::GAME_STATUS gameStatus;

  GameState() :
    userColor(PiecesConstants::WHITE),
    activeColor(PiecesConstants::WHITE),
    gameStatus(GameStateConstants::ACTIVE) {}

public:
  static GameState& instance();
  void moveMade();
  void restart();

  [[nodiscard]] PiecesConstants::PIECE_COLORS getUserColor() const { return this->userColor; }
  [[nodiscard]] PiecesConstants::PIECE_COLORS getActiveColor() const { return this->activeColor; }
  [[nodiscard]] GameStateConstants::GAME_STATUS getGameStatus() const { return this->gameStatus; }
};

#endif
