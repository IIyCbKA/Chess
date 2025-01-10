#include <GameState.hpp>

void GameState::restart() {
  this->gameStatus = GameStateConstants::ACTIVE;
  this->activeColor = PiecesConstants::WHITE;
  this->userColor = this->userColor == PiecesConstants::WHITE
    ? PiecesConstants::BLACK
    : PiecesConstants::WHITE;
}
