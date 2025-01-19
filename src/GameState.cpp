#include <GameState.hpp>

GameState& GameState::instance() {
  static GameState instance;

  return instance;
}


void GameState::restart() {
  this->gameStatus = GameStateConstants::ACTIVE;
  this->activeColor = PiecesConstants::WHITE;
  this->userColor = this->userColor == PiecesConstants::WHITE
    ? PiecesConstants::BLACK
    : PiecesConstants::WHITE;
}


void GameState::moveMade() {
  this->activeColor = this->activeColor == PiecesConstants::WHITE
    ? PiecesConstants::BLACK
    : PiecesConstants::WHITE;
}
