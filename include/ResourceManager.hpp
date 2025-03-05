#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <constants.hpp>

#include <QSvgRenderer>
#include <unordered_map>

class ResourceManager {
  std::unordered_map <
    PiecesConstants::PIECE_COLORS,
    std::unordered_map<PiecesConstants::PIECE_TYPES, std::unique_ptr<QSvgRenderer>>
  > renderers;

  ResourceManager();

public:
  static ResourceManager& instance();

  [[nodiscard]] QSvgRenderer* getRenderer(
    PiecesConstants::PIECE_COLORS color,
    PiecesConstants::PIECE_TYPES piece
  ) const;

  ResourceManager(const ResourceManager&) = delete;
  ResourceManager& operator=(const ResourceManager&) = delete;

  ~ResourceManager() = default;
};

#endif
