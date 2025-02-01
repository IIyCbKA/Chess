#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <utils/enPassant.hpp>
#include <utils/position.hpp>
#include <constants.hpp>

#include <optional>

class GameState {
  PiecesConstants::PIECE_COLORS userColor;
  PiecesConstants::PIECE_COLORS activeColor;
  GameStateConstants::GAME_STATUS gameStatus;
  std::optional<EnPassant> enPassant;

  GameState() :
    userColor(PiecesConstants::WHITE),
    activeColor(PiecesConstants::WHITE),
    gameStatus(GameStateConstants::ACTIVE) {}

public:
  static GameState& instance();
  void moveMade();
  void restart();
  void clearEnPassant() { this->enPassant.reset(); }
  void setEnPassant(EnPassant enPassant) { this->enPassant = enPassant; }

  [[nodiscard]] PiecesConstants::PIECE_COLORS getUserColor() const { return this->userColor; }
  [[nodiscard]] PiecesConstants::PIECE_COLORS getActiveColor() const { return this->activeColor; }
  [[nodiscard]] GameStateConstants::GAME_STATUS getGameStatus() const { return this->gameStatus; }
  [[nodiscard]] std::optional<EnPassant> getEnPassant() const { return this->enPassant; }
};

#endif
