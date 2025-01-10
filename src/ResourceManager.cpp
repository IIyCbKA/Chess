#include <ResourceManager.hpp>

ResourceManager& ResourceManager::instance() {
  static ResourceManager instance;

  return instance;
}


ResourceManager::ResourceManager() {
  renderers[PiecesConstants::COLORS::WHITE][PiecesConstants::PIECES::PAWN] =
    new QSvgRenderer(QString(":/images/wPawn.svg"));
  renderers[PiecesConstants::COLORS::BLACK][PiecesConstants::PIECES::PAWN] =
    new QSvgRenderer(QString(":/images/bPawn.svg"));
  renderers[PiecesConstants::COLORS::WHITE][PiecesConstants::PIECES::KING] =
    new QSvgRenderer(QString(":/images/wKing.svg"));
  renderers[PiecesConstants::COLORS::BLACK][PiecesConstants::PIECES::KING] =
    new QSvgRenderer(QString(":/images/bKing.svg"));
  renderers[PiecesConstants::COLORS::WHITE][PiecesConstants::PIECES::QUEEN] =
    new QSvgRenderer(QString(":/images/wQueen.svg"));
  renderers[PiecesConstants::COLORS::BLACK][PiecesConstants::PIECES::QUEEN] =
    new QSvgRenderer(QString(":/images/bQueen.svg"));
  renderers[PiecesConstants::COLORS::WHITE][PiecesConstants::PIECES::ROOK] =
    new QSvgRenderer(QString(":/images/wRook.svg"));
  renderers[PiecesConstants::COLORS::BLACK][PiecesConstants::PIECES::ROOK] =
    new QSvgRenderer(QString(":/images/bRook.svg"));
  renderers[PiecesConstants::COLORS::WHITE][PiecesConstants::PIECES::BISHOP] =
    new QSvgRenderer(QString(":/images/wBishop.svg"));
  renderers[PiecesConstants::COLORS::BLACK][PiecesConstants::PIECES::BISHOP] =
    new QSvgRenderer(QString(":/images/bBishop.svg"));
  renderers[PiecesConstants::COLORS::WHITE][PiecesConstants::PIECES::KNIGHT] =
    new QSvgRenderer(QString(":/images/wKnight.svg"));
  renderers[PiecesConstants::COLORS::BLACK][PiecesConstants::PIECES::KNIGHT] =
    new QSvgRenderer(QString(":/images/bKnight.svg"));
}


QSvgRenderer* ResourceManager::getRenderer(
  PiecesConstants::COLORS color,
  PiecesConstants::PIECES piece
) const {
  if (renderers.contains(color) && renderers[color].contains(piece)) {
    return renderers[color][piece];
  }

  return nullptr;
}
