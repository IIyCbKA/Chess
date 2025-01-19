#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <constants.hpp>

#include <QHash>
#include <QSvgRenderer>

class ResourceManager {
  QHash <
    PiecesConstants::PIECE_COLORS,
    QHash<PiecesConstants::PIECE_TYPES, QSvgRenderer*>
  > renderers;

  ResourceManager();

public:
  static ResourceManager& instance();

  [[nodiscard]] QSvgRenderer* getRenderer(
    PiecesConstants::PIECE_COLORS color,
    PiecesConstants::PIECE_TYPES piece
  ) const ;

  ResourceManager(const ResourceManager&) = delete;
  ResourceManager& operator=(const ResourceManager&) = delete;

  ~ResourceManager() {
    for(auto colorHash : this->renderers) {
      for(auto renderer : colorHash) {
        delete renderer;
      }
    }
  }
};

#endif
