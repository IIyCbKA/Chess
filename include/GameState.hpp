#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <constants.hpp>

class GameState {
  PiecesConstants::COLORS userColor;
  PiecesConstants::COLORS activeColor;
  GameStateConstants::GAME_STATUS gameStatus;

public:
  GameState() :
    userColor(PiecesConstants::WHITE),
    activeColor(PiecesConstants::WHITE),
    gameStatus(GameStateConstants::ACTIVE) {}

  void restart();

  [[nodiscard]] PiecesConstants::COLORS getUserColor() const { return userColor; }
  [[nodiscard]] GameStateConstants::GAME_STATUS getGameStatus() const { return gameStatus; }
};

#endif
