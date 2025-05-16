#include <ResourceManager.hpp>

#include <array>

ResourceManager& ResourceManager::instance() {
  static ResourceManager instance;

  return instance;
}


ResourceManager::ResourceManager() {
  constexpr std::array colors = {
    WHITE_COLOR,
    BLACK_COLOR,
  };

  constexpr std::array types = {
    PAWN_TYPE,
    KING_TYPE,
    QUEEN_TYPE,
    ROOK_TYPE,
    BISHOP_TYPE,
    KNIGHT_TYPE,
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
