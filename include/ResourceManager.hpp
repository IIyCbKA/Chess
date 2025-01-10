#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <constants.hpp>

#include <QHash>
#include <QSvgRenderer>

class ResourceManager {
  QHash <
    PiecesConstants::COLORS,
    QHash<PiecesConstants::PIECES, QSvgRenderer*>
  > renderers;

  ResourceManager();

public:
  static ResourceManager& instance();

  [[nodiscard]] QSvgRenderer* getRenderer(
    PiecesConstants::COLORS color,
    PiecesConstants::PIECES piece
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
