#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <utils/enPassant.hpp>
#include <utils/position.hpp>
#include <constants.hpp>

#include <optional>

class GameState {
  PiecesConstants::PIECE_COLORS userColor;
  PiecesConstants::PIECE_COLORS activeColor;
  PiecesConstants::PIECE_COLORS inactiveColor;
  GameStateConstants::GAME_STATUS gameStatus;
  std::optional<EnPassant> enPassant;
  std::optional<PiecesConstants::PIECE_COLORS> checkColor;
  size_t fullMoveNumber;

  GameState() :
    userColor(PiecesConstants::WHITE),
    activeColor(PiecesConstants::WHITE),
    inactiveColor(PiecesConstants::BLACK),
    gameStatus(GameStateConstants::ACTIVE),
    fullMoveNumber(GameStateConstants::DEFAULT_FULL_MOVE_NUMBER) {}

public:
  static GameState& instance();
  void moveMade();
  void restart();
  void clearEnPassant();
  void setEnPassant(EnPassant enPassant) { this->enPassant = enPassant; }
  void clearCheck() { this->checkColor.reset(); }
  void setCheck(PiecesConstants::PIECE_COLORS color) { this->checkColor = color; }
  void setGameStatus(GameStateConstants::GAME_STATUS status) { this->gameStatus = status; }

  [[nodiscard]] PiecesConstants::PIECE_COLORS getActiveColor() const { return this->activeColor; }
  [[nodiscard]] GameStateConstants::GAME_STATUS getGameStatus() const { return this->gameStatus; }
  [[nodiscard]] std::optional<EnPassant> getEnPassant() const { return this->enPassant; }
  [[nodiscard]] PiecesConstants::PIECE_COLORS getInactiveColor() const { return this->inactiveColor; }
  [[nodiscard]] std::optional<PiecesConstants::PIECE_COLORS> getCheckColor() const { return this->checkColor; }
  [[nodiscard]] bool isGameActive() const { return this->gameStatus == GameStateConstants::ACTIVE; }
  [[nodiscard]] bool isUserMove() const { return this->userColor == this->activeColor; }
  [[nodiscard]] size_t getFullMoveNumber() const { return this->fullMoveNumber; }
  [[nodiscard]] std::string getStringEnPassant() const;
};

#endif
