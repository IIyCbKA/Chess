#include <models/BoardModel.hpp>
#include <models/Bishop.hpp>
#include <models/King.hpp>
#include <models/Knight.hpp>
#include <models/Pawn.hpp>
#include <models/Queen.hpp>
#include <models/Rook.hpp>

void BoardModel::setupPieces() {
  for (size_t col = 0; col < BoardConstants::SQUARES_ROWS_COLS; ++col) {
    this->board[6][col] = std::make_unique<Pawn>(Pawn(PiecesConstants::PIECE_COLORS::WHITE));
  }

  this->board[7][0] = std::make_unique<Rook>(Rook(PiecesConstants::PIECE_COLORS::WHITE));
  this->board[7][1] = std::make_unique<Knight>(Knight(PiecesConstants::PIECE_COLORS::WHITE));
  this->board[7][2] = std::make_unique<Bishop>(Bishop(PiecesConstants::PIECE_COLORS::WHITE));
  this->board[7][3] = std::make_unique<Queen>(Queen(PiecesConstants::PIECE_COLORS::WHITE));
  this->board[7][4] = std::make_unique<King>(King(PiecesConstants::PIECE_COLORS::WHITE));
  this->board[7][5] = std::make_unique<Bishop>(Bishop(PiecesConstants::PIECE_COLORS::WHITE));
  this->board[7][6] = std::make_unique<Knight>(Knight(PiecesConstants::PIECE_COLORS::WHITE));
  this->board[7][7] = std::make_unique<Rook>(Rook(PiecesConstants::PIECE_COLORS::WHITE));

  for (size_t col = 0; col < BoardConstants::SQUARES_ROWS_COLS; ++col) {
    this->board[1][col] = std::make_unique<Pawn>(Pawn(PiecesConstants::PIECE_COLORS::BLACK));
  }

  this->board[0][0] = std::make_unique<Rook>(Rook(PiecesConstants::PIECE_COLORS::BLACK));
  this->board[0][1] = std::make_unique<Knight>(Knight(PiecesConstants::PIECE_COLORS::BLACK));
  this->board[0][2] = std::make_unique<Bishop>(Bishop(PiecesConstants::PIECE_COLORS::BLACK));
  this->board[0][3] = std::make_unique<Queen>(Queen(PiecesConstants::PIECE_COLORS::BLACK));
  this->board[0][4] = std::make_unique<King>(King(PiecesConstants::PIECE_COLORS::BLACK));
  this->board[0][5] = std::make_unique<Bishop>(Bishop(PiecesConstants::PIECE_COLORS::BLACK));
  this->board[0][6] = std::make_unique<Knight>(Knight(PiecesConstants::PIECE_COLORS::BLACK));
  this->board[0][7] = std::make_unique<Rook>(Rook(PiecesConstants::PIECE_COLORS::BLACK));
}


void BoardModel::cleanBoard() {
  for (size_t row = 0; row < BoardConstants::SQUARES_ROWS_COLS; ++row) {
    for (size_t col = 0; col < BoardConstants::SQUARES_ROWS_COLS; ++col) {
      this->board[row][col].reset();
    }
  }
}


Piece* BoardModel::getPiece(const Position piecePosition) const {
  return this->board[piecePosition.row][piecePosition.col].get();
}


std::vector<Position> BoardModel::getPossibleMoves(const Position from) const {
  if (this->board[from.row][from.col]) {
    return this->board[from.row][from.col]->getPossibleMoves(this->board, from);
  }

  return {};
}


void BoardModel::boardReset() {
  cleanBoard();
  setupPieces();
  emit onBoardReset();
}


void BoardModel::removePiece(const Position from) {
  this->board[from.row][from.col].reset();
  emit onPieceRemoved(from);
}


void BoardModel::movePiece(const Position from, const Position to) {
  removePiece(to);
  this->board[to.row][to.col] = std::move(this->board[from.row][from.col]);
  this->board[to.row][to.col]->move();
  emit onPieceMoved(from, to);
}
