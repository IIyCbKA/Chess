#include <GameState.hpp>

GameState& GameState::instance() {
  static GameState instance;

  return instance;
}


void GameState::restart() {
  this->userColor = this->userColor == PiecesConstants::WHITE
    ? PiecesConstants::BLACK
    : PiecesConstants::WHITE;
  this->activeColor   = PiecesConstants::WHITE;
  this->inactiveColor = PiecesConstants::BLACK;
  this->gameStatus    = GameStateConstants::ACTIVE;
  this->enPassant.reset();
  this->checkColor.reset();
  this->fullMoveNumber = GameStateConstants::DEFAULT_FULL_MOVE_NUMBER;
}


void GameState::clearEnPassant() {
  if (this->enPassant.has_value() && this->enPassant->pawnColor != this->activeColor) {
    this->enPassant.reset();
  }
}


void GameState::moveMade() {
  std::swap(this->activeColor, this->inactiveColor);
  if (this->activeColor == PiecesConstants::WHITE) this->fullMoveNumber += 1;
}


std::string GameState::getStringEnPassant() const {
  std::string stringEnPassant;
  if (this->enPassant.has_value()) {
    stringEnPassant =
      BoardConstants::NUM_COL_TO_CHAR[this->enPassant->enPassantPosition.col]
      + std::to_string(
        BoardConstants::SQUARES_ROWS_COLS - this->enPassant->enPassantPosition.row
      );
  } else stringEnPassant = ConstantsFEN::EMPTY_EN_PASSANT;

  return stringEnPassant;
}
