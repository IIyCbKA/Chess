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
      this->renderers[color][type] = new QSvgRenderer(
        ResourcesConstants::PIECES_PATHS[color][type]
      );
    }
  }
}


QSvgRenderer* ResourceManager::getRenderer(
  const PiecesConstants::PIECE_COLORS color,
  const PiecesConstants::PIECE_TYPES piece
) const {
  if (this->renderers.contains(color) && this->renderers[color].contains(piece)) {
    return this->renderers[color][piece];
  }

  return nullptr;
}
