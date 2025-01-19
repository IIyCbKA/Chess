#include <ResourceManager.hpp>

ResourceManager& ResourceManager::instance() {
  static ResourceManager instance;

  return instance;
}


ResourceManager::ResourceManager() {
  this->renderers[PiecesConstants::PIECE_COLORS::WHITE][PiecesConstants::PIECE_TYPES::PAWN] =
    new QSvgRenderer(QString(":/images/wPawn.svg"));
  this->renderers[PiecesConstants::PIECE_COLORS::BLACK][PiecesConstants::PIECE_TYPES::PAWN] =
    new QSvgRenderer(QString(":/images/bPawn.svg"));
  this->renderers[PiecesConstants::PIECE_COLORS::WHITE][PiecesConstants::PIECE_TYPES::KING] =
    new QSvgRenderer(QString(":/images/wKing.svg"));
  this->renderers[PiecesConstants::PIECE_COLORS::BLACK][PiecesConstants::PIECE_TYPES::KING] =
    new QSvgRenderer(QString(":/images/bKing.svg"));
  this->renderers[PiecesConstants::PIECE_COLORS::WHITE][PiecesConstants::PIECE_TYPES::QUEEN] =
    new QSvgRenderer(QString(":/images/wQueen.svg"));
  this->renderers[PiecesConstants::PIECE_COLORS::BLACK][PiecesConstants::PIECE_TYPES::QUEEN] =
    new QSvgRenderer(QString(":/images/bQueen.svg"));
  this->renderers[PiecesConstants::PIECE_COLORS::WHITE][PiecesConstants::PIECE_TYPES::ROOK] =
    new QSvgRenderer(QString(":/images/wRook.svg"));
  this->renderers[PiecesConstants::PIECE_COLORS::BLACK][PiecesConstants::PIECE_TYPES::ROOK] =
    new QSvgRenderer(QString(":/images/bRook.svg"));
  this->renderers[PiecesConstants::PIECE_COLORS::WHITE][PiecesConstants::PIECE_TYPES::BISHOP] =
    new QSvgRenderer(QString(":/images/wBishop.svg"));
  this->renderers[PiecesConstants::PIECE_COLORS::BLACK][PiecesConstants::PIECE_TYPES::BISHOP] =
    new QSvgRenderer(QString(":/images/bBishop.svg"));
  this->renderers[PiecesConstants::PIECE_COLORS::WHITE][PiecesConstants::PIECE_TYPES::KNIGHT] =
    new QSvgRenderer(QString(":/images/wKnight.svg"));
  this->renderers[PiecesConstants::PIECE_COLORS::BLACK][PiecesConstants::PIECE_TYPES::KNIGHT] =
    new QSvgRenderer(QString(":/images/bKnight.svg"));
}


QSvgRenderer* ResourceManager::getRenderer(
  PiecesConstants::PIECE_COLORS color,
  PiecesConstants::PIECE_TYPES piece
) const {
  if (this->renderers.contains(color) && this->renderers[color].contains(piece)) {
    return this->renderers[color][piece];
  }

  return nullptr;
}
