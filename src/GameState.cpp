#include <GameState.hpp>

GameState& GameState::instance() {
  static GameState instance;

  return instance;
}


void GameState::restart() {
  this->gameStatus = GameStateConstants::ACTIVE;
  this->activeColor = PiecesConstants::WHITE;
  this->inactiveColor = PiecesConstants::BLACK;
  this->userColor = this->userColor == PiecesConstants::WHITE
    ? PiecesConstants::BLACK
    : PiecesConstants::WHITE;
}


void GameState::moveMade() {
  std::swap(this->activeColor, this->inactiveColor);
}
