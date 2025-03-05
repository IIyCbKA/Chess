#include <models/BoardModel.hpp>
#include <models/Bishop.hpp>
#include <models/King.hpp>
#include <models/Knight.hpp>
#include <models/Pawn.hpp>
#include <models/Queen.hpp>
#include <models/Rook.hpp>
#include <GameState.hpp>

void BoardModel::setupPiece(
  const Position pos,
  const PiecesConstants::PIECE_COLORS color,
  const PiecesConstants::PIECE_TYPES type
) {
  this->board[pos.row][pos.col] = createPiece(type, color);
}


void BoardModel::cleanBoard() {
  this->halfMoveClock = 0;
  for (size_t row = 0; row < BoardConstants::SQUARES_ROWS_COLS; ++row) {
    for (size_t col = 0; col < BoardConstants::SQUARES_ROWS_COLS; ++col) {
      this->board[row][col].reset();
    }

    this->attackMap[row].reset();
  }
}


Piece* BoardModel::getPiece(const Position piecePosition) const {
  return this->board[piecePosition.row][piecePosition.col].get();
}


void BoardModel::updateHalfMoveClock(const Position from, const Position to) {
  if (
    this->board[to.row][to.col] ||
    this->board[from.row][from.col]->getType() == PiecesConstants::PIECE_TYPES::PAWN
  ) {
    this->halfMoveClock = 0;
  } else this->halfMoveClock++;
}


std::vector<Position> BoardModel::getPossibleMoves(const Position pos) const {
  if (this->board[pos.row][pos.col]) {
    return this->board[pos.row][pos.col]->getPossibleMoves(
      this->board,
      this->attackMap,
      pos
    );
  }

  return {};
}


std::vector<Position> BoardModel::getSelectedCanMove() const {
  return this->selectedCanMove;
}


void BoardModel::removePiece(const Position pos) {
  this->board[pos.row][pos.col].reset();
}


Position BoardModel::getCapturePos(const Position from, const Position to) const {
  return this->board[from.row][from.col]->getCapturePosition(from, to);
}


void BoardModel::movePiece(const Position from, const Position to) {
  updateHalfMoveClock(from, to);
  tryCastling(from, to);
  this->board[to.row][to.col] = std::move(this->board[from.row][from.col]);
  this->board[to.row][to.col]->move();
  tryPawnPromotion(to);
  GameState::instance().clearEnPassant();
  updateAttackMap(GameState::instance().getActiveColor());
  searchCheck();
}


bool BoardModel::isSelectedCanMoveTo(const Position to) const {
  return std::ranges::any_of(
    this->selectedCanMove,
    [to](const auto& pos) { return pos == to; }
  );
}


void BoardModel::deselectSquare() {
  this->selectedPosition.reset();
  this->selectedCanMove.clear();
}


bool BoardModel::checkPossibleMove(const Position from, const Position to) {
  auto originalTo = std::move(this->board[to.row][to.col]); // save piece
  this->board[to.row][to.col] = std::move(this->board[from.row][from.col]); // move
  const Position kingPos = getKingPosByColor(GameState::instance().getActiveColor());

  // if pos is not under opponent attack - move is acceptable
  const bool isAcceptable = !isPosUnderAttack(kingPos, GameState::instance().getInactiveColor());

  this->board[from.row][from.col] = std::move(this->board[to.row][to.col]); // unmove
  this->board[to.row][to.col] = std::move(originalTo); // return piece

  return isAcceptable;
}


void BoardModel::selectSquare(const Position to) {
  this->selectedPosition = to;
  std::vector<Position> defaultPossibleMoves =
    getPossibleMoves(*this->selectedPosition);

  for (const auto& possibleMove : defaultPossibleMoves) {
    if (checkPossibleMove(*this->selectedPosition, possibleMove)) {
      this->selectedCanMove.emplace_back(possibleMove);
    }
  }
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
  return *this->selectedPosition;
}


bool BoardModel::isSamePosition(const Position pos) const {
  return
    this->selectedPosition.has_value() &&
    *this->selectedPosition == pos;
}


bool BoardModel::isCastling(const Position from, const Position to) const {
  const auto* movingPiece = this->board[from.row][from.col].get();

  return
    movingPiece->getType() == PiecesConstants::PIECE_TYPES::KING &&
    std::abs(static_cast<int>(to.col) - static_cast<int>(from.col)) == 2;
}


void BoardModel::tryCastling(const Position from, const Position to) {
  if (isCastling(from, to)) {
    // to prevent castling from adding 2, we subtract the first addition
    if (this->halfMoveClock) this->halfMoveClock--;

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


void BoardModel::searchCheck() {
  PiecesConstants::PIECE_COLORS opponentColor = GameState::instance().getInactiveColor();
  Position posOpponentKing = getKingPosByColor(opponentColor);
  if (this->attackMap[posOpponentKing.row][posOpponentKing.col]) {
    emit onCheck(posOpponentKing, opponentColor);
  }
}


Position BoardModel::getKingPosByColor(const PiecesConstants::PIECE_COLORS color) const {
  auto isDesiredKing = [this, color](const Position pos)->bool {
    return
      this->board[pos.row][pos.col]
      && this->board[pos.row][pos.col]->getColor() == color
      && this->board[pos.row][pos.col]->getType() == PiecesConstants::PIECE_TYPES::KING;
  };

  for (size_t row = 0; row < BoardConstants::SQUARES_ROWS_COLS; ++row) {
    for (size_t col = 0; col < BoardConstants::SQUARES_ROWS_COLS; ++col) {
      if (isDesiredKing({row, col})) return {row, col};
    }
  }

  return {};
}


void BoardModel::updateAttackMap(const PiecesConstants::PIECE_COLORS color) {
  for (size_t row = 0; row < BoardConstants::SQUARES_ROWS_COLS; ++row) {
    this->attackMap[row].reset();
  }

  for (size_t row = 0; row < BoardConstants::SQUARES_ROWS_COLS; ++row) {
    for (size_t col = 0; col < BoardConstants::SQUARES_ROWS_COLS; ++col) {
      if (this->board[row][col] && this->board[row][col]->getColor() == color) {
        std::vector<Position> canMove = getPossibleMoves({row, col});
        for (const auto& position : canMove) {
          this->attackMap[position.row][position.col] = true;
        }
      }
    }
  }
}


bool BoardModel::isPosUnderAttack(
  const Position checkPos,
  const PiecesConstants::PIECE_COLORS opponentColor
) const {
  for (size_t row = 0; row < BoardConstants::SQUARES_ROWS_COLS; ++row) {
    for (size_t col = 0; col < BoardConstants::SQUARES_ROWS_COLS; ++col) {
      if (this->board[row][col] && this->board[row][col]->getColor() == opponentColor) {
        std::vector<Position> canMove = getPossibleMoves({row, col});
        for (const auto& position : canMove) {
          if (position == checkPos) return true;
        }
      }
    }
  }

  return false;
}


bool BoardModel::isPlayerHavePossibleMove() {
  const PiecesConstants::PIECE_COLORS color = GameState::instance().getActiveColor();
  for (size_t row = 0; row < BoardConstants::SQUARES_ROWS_COLS; ++row) {
    for (size_t col = 0; col < BoardConstants::SQUARES_ROWS_COLS; ++col) {
      if (this->board[row][col] && this->board[row][col]->getColor() == color) {
        std::vector<Position> canMove = getPossibleMoves({row, col});
        for (const auto& position : canMove) {
          if (checkPossibleMove({row, col}, position)) return true;
        }
      }
    }
  }

  return false;
}


std::string BoardModel::getBoardForFEN() const {
  std::string boardForFEN;
  for (size_t row = 0; row < BoardConstants::SQUARES_ROWS_COLS; ++row) {
    size_t emptyCount = 0;
    for (size_t col = 0; col < BoardConstants::SQUARES_ROWS_COLS; ++col) {
      if (this->board[row][col]) {
        if (emptyCount) {
          boardForFEN += std::to_string(emptyCount);
          emptyCount = 0;
        }

        boardForFEN += ConstantsFEN::piecesInFEN[
          this->board[row][col]->getColor()][this->board[row][col]->getType()];
      } else emptyCount++;

      if (col == BoardConstants::SQUARES_ROWS_COLS - 1 && emptyCount) {
        boardForFEN += std::to_string(emptyCount);
      }
    }

    if (row != BoardConstants::SQUARES_ROWS_COLS - 1) {
      boardForFEN += ConstantsFEN::ROW_DIVIDER_FOR_BOARD;
    }
  }

  return boardForFEN;
}


std::string BoardModel::getCastlingForFEN() const {
  std::string castlingForFEN;
  if (isNotMovedPiece(BoardConstants::DEFAULT_WHITE_KING_POS)) {
    if (isNotMovedPiece(BoardConstants::DEFAULT_WHITE_KING_ROOK_POS))
      castlingForFEN += ConstantsFEN::WHITE_KINGSIDE_CASTLING_FEN;
    if (isNotMovedPiece(BoardConstants::DEFAULT_WHITE_QUEEN_ROOK_POS))
      castlingForFEN += ConstantsFEN::WHITE_QUEENSIDE_CASTLING_FEN;
  }

  if (isNotMovedPiece(BoardConstants::DEFAULT_BLACK_KING_POS)) {
    if (isNotMovedPiece(BoardConstants::DEFAULT_BLACK_KING_ROOK_POS))
      castlingForFEN += ConstantsFEN::BLACK_KINGSIDE_CASTLING_FEN;
    if (isNotMovedPiece(BoardConstants::DEFAULT_BLACK_QUEEN_ROOK_POS))
      castlingForFEN += ConstantsFEN::BLACK_QUEENSIDE_CASTLING_FEN;
  }

  if (castlingForFEN.empty()) castlingForFEN = ConstantsFEN::EMPTY_CASTLING_FEN;

  return castlingForFEN;
}


bool BoardModel::isNotMovedPiece(const Position pos) const {
  return
    this->board[pos.row][pos.col] && !this->board[pos.row][pos.col]->getIsMoved();
}


size_t BoardModel::getHalfMoveClock() const {
  return this->halfMoveClock;
}