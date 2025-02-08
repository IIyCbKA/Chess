#include <models/BoardModel.hpp>
#include <models/Bishop.hpp>
#include <models/King.hpp>
#include <models/Knight.hpp>
#include <models/Pawn.hpp>
#include <models/Queen.hpp>
#include <models/Rook.hpp>
#include <GameState.hpp>

void BoardModel::setupPieces() {
  for (size_t col = 0; col < BoardConstants::SQUARES_ROWS_COLS; ++col) {
    this->board[6][col] = createPiece(
      PiecesConstants::PIECE_TYPES::PAWN, PiecesConstants::PIECE_COLORS::WHITE);
  }

  this->board[7][0] = createPiece(
    PiecesConstants::PIECE_TYPES::ROOK, PiecesConstants::PIECE_COLORS::WHITE);
  this->board[7][1] = createPiece(
    PiecesConstants::PIECE_TYPES::KNIGHT, PiecesConstants::PIECE_COLORS::WHITE);
  this->board[7][2] = createPiece(
    PiecesConstants::PIECE_TYPES::BISHOP, PiecesConstants::PIECE_COLORS::WHITE);
  this->board[7][3] = createPiece(
    PiecesConstants::PIECE_TYPES::QUEEN, PiecesConstants::PIECE_COLORS::WHITE);
  this->board[7][4] = createPiece(
    PiecesConstants::PIECE_TYPES::KING, PiecesConstants::PIECE_COLORS::WHITE);
  this->board[7][5] = createPiece(
    PiecesConstants::PIECE_TYPES::BISHOP, PiecesConstants::PIECE_COLORS::WHITE);
  this->board[7][6] = createPiece(
    PiecesConstants::PIECE_TYPES::KNIGHT, PiecesConstants::PIECE_COLORS::WHITE);
  this->board[7][7] = createPiece(
    PiecesConstants::PIECE_TYPES::ROOK, PiecesConstants::PIECE_COLORS::WHITE);

  for (size_t col = 0; col < BoardConstants::SQUARES_ROWS_COLS; ++col) {
    this->board[1][col] = createPiece(
      PiecesConstants::PIECE_TYPES::PAWN, PiecesConstants::PIECE_COLORS::BLACK);
  }

  this->board[0][0] = createPiece(
    PiecesConstants::PIECE_TYPES::ROOK, PiecesConstants::PIECE_COLORS::BLACK);
  this->board[0][1] = createPiece(
    PiecesConstants::PIECE_TYPES::KNIGHT, PiecesConstants::PIECE_COLORS::BLACK);
  this->board[0][2] = createPiece(
    PiecesConstants::PIECE_TYPES::BISHOP, PiecesConstants::PIECE_COLORS::BLACK);
  this->board[0][3] = createPiece(
    PiecesConstants::PIECE_TYPES::QUEEN, PiecesConstants::PIECE_COLORS::BLACK);
  this->board[0][4] = createPiece(
    PiecesConstants::PIECE_TYPES::KING, PiecesConstants::PIECE_COLORS::BLACK);
  this->board[0][5] = createPiece(
    PiecesConstants::PIECE_TYPES::BISHOP, PiecesConstants::PIECE_COLORS::BLACK);
  this->board[0][6] = createPiece(
    PiecesConstants::PIECE_TYPES::KNIGHT, PiecesConstants::PIECE_COLORS::BLACK);
  this->board[0][7] = createPiece(
    PiecesConstants::PIECE_TYPES::ROOK, PiecesConstants::PIECE_COLORS::BLACK);
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


void BoardModel::getPossibleMoves(const Position from) {
  if (this->board[from.row][from.col]) {
    this->selectedCanMove =
      this->board[from.row][from.col]->getPossibleMoves(this->board, from);
  }
}


std::vector<Position> BoardModel::getSelectedCanMove() const {
  return this->selectedCanMove;
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


void BoardModel::clearEnPassant() {
  if (
    const auto enPassant = GameState::instance().getEnPassant();
    enPassant.has_value() &&
    GameState::instance().getActiveColor() != enPassant->pawnColor
  ) {
    GameState::instance().clearEnPassant();
  }
}


void BoardModel::movePiece(const Position from, const Position to) {
  removePiece(this->board[from.row][from.col]->getCapturePosition(from, to));
  tryCastling(to);
  this->board[to.row][to.col] = std::move(this->board[from.row][from.col]);
  this->board[to.row][to.col]->move();
  tryPawnPromotion(to);
  clearEnPassant();
}


bool BoardModel::isSelectedCanMoveTo(const Position to) const {
  return std::ranges::any_of(
    this->selectedCanMove,
    [to](const auto& pos) { return pos.row == to.row && pos.col == to.col; }
  );
}


void BoardModel::deselectSquare() {
  this->selectedPosition.reset();
  this->selectedCanMove.clear();
}


void BoardModel::selectSquare(const Position to) {
  this->selectedPosition = to;
  getPossibleMoves(this->selectedPosition.value());
}


bool BoardModel::trySelectSquare(const Position to) const {
  return
    this->board[to.row][to.col] &&
    this->board[to.row][to.col]->getColor() == GameState::instance().getActiveColor();
}


bool BoardModel::hasSelectedPiece() const {
  return this->selectedPosition.has_value();
}


Position BoardModel::getSelectedPosition() const {
  return this->selectedPosition.value();
}


bool BoardModel::isSamePosition(const Position pos) const {
  return
    this->selectedPosition.has_value() &&
    this->selectedPosition->row == pos.row &&
    this->selectedPosition->col == pos.col;
}


bool BoardModel::isCastling(const Position to) const {
  const auto* movingPiece =
    this->board[this->selectedPosition->row][this->selectedPosition->col].get();

  return
    movingPiece->getType() == PiecesConstants::PIECE_TYPES::KING &&
    std::abs(
      static_cast<int>(to.col) - static_cast<int>(this->selectedPosition->col)
    ) == 2;
}


void BoardModel::tryCastling(const Position to) {
  if (isCastling(to)) {
    const Position from = this->selectedPosition.value();
    Position rookFrom, rookTo;
    rookFrom.row = to.row;
    rookTo.row = to.row;

    if (to.col > from.col) {
      rookFrom.col = BoardConstants::DEFAULT_KINGSIDE_ROOK_COL;
      rookTo.col = BoardConstants::KINGSIDE_CASTLING_NEW_ROOK_COL;
    } else {
      rookFrom.col = BoardConstants::DEFAULT_QUEENSIDE_ROOK_COL;
      rookTo.col = BoardConstants::QUEENSIDE_CASTLING_NEW_ROOK_COL;
    }

    emit onMoveRook(rookFrom, rookTo);
  }
}


bool BoardModel::isPawnPromotion(const Position pos) const {
  const auto* movingPiece = this->board[pos.row][pos.col].get();

  return
    movingPiece->getType() == PiecesConstants::PIECE_TYPES::PAWN &&
    (pos.row == 0 || pos.row == BoardConstants::SQUARES_ROWS_COLS - 1);
}


void BoardModel::tryPawnPromotion(const Position pos) {
  if (isPawnPromotion(pos)) {
    emit onPawnPromotion(pos, this->board[pos.row][pos.col]->getColor());
  }
}


void BoardModel::changePawnType(
  const Position pos,
  const PiecesConstants::PIECE_TYPES newType,
  const PiecesConstants::PIECE_COLORS color
) {
  if (
    this->board[pos.row][pos.col] &&
    this->board[pos.row][pos.col]->getType() == PiecesConstants::PIECE_TYPES::PAWN
  ) {
    this->board[pos.row][pos.col].reset();
    this->board[pos.row][pos.col] = createPiece(newType, color);
  }
}


std::unique_ptr<Piece> BoardModel::createPiece(
  const PiecesConstants::PIECE_TYPES type,
  const PiecesConstants::PIECE_COLORS color
) {
  switch (type) {
    case PiecesConstants::PIECE_TYPES::PAWN:
      return std::make_unique<Pawn>(Pawn(color));
    case PiecesConstants::PIECE_TYPES::QUEEN:
      return std::make_unique<Queen>(Queen(color));
    case PiecesConstants::PIECE_TYPES::ROOK:
     return std::make_unique<Rook>(Rook(color));
    case PiecesConstants::PIECE_TYPES::KNIGHT:
      return std::make_unique<Knight>(Knight(color));
    case PiecesConstants::PIECE_TYPES::BISHOP:
      return std::make_unique<Bishop>(Bishop(color));
    case PiecesConstants::PIECE_TYPES::KING:
      return std::make_unique<King>(King(color));
    default:
      return std::make_unique<Queen>(Queen(color));
  }
}
