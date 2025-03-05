#include <ResourceManager.hpp>

#include <array>

ResourceManager& ResourceManager::instance() {
  static ResourceManager instance;

  return instance;
}


ResourceManager::ResourceManager() {
  constexpr std::array colors = {
    PiecesConstants::PIECE_COLORS::WHITE,
    PiecesConstants::PIECE_COLORS::BLACK
  };

  constexpr std::array types = {
    PiecesConstants::PIECE_TYPES::PAWN,
    PiecesConstants::PIECE_TYPES::KING,
    PiecesConstants::PIECE_TYPES::QUEEN,
    PiecesConstants::PIECE_TYPES::ROOK,
    PiecesConstants::PIECE_TYPES::BISHOP,
    PiecesConstants::PIECE_TYPES::KNIGHT
  };

  for (auto color : colors) {
    for (auto type : types) {
      this->renderers[color][type] = std::make_unique<QSvgRenderer>(
        ResourcesConstants::PIECES_PATHS[color][type]
      );
    }
  }
}


QSvgRenderer* ResourceManager::getRenderer(
  const PiecesConstants::PIECE_COLORS color,
  const PiecesConstants::PIECE_TYPES piece
) const {
  const auto colorIter = this->renderers.find(color);
  if (colorIter == this->renderers.end()) return nullptr;

  const auto pieceIter = colorIter->second.find(piece);
  return pieceIter != colorIter->second.end() ? pieceIter->second.get() : nullptr;
}
