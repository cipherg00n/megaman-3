#ifndef CLIENT_LIFEVIEW_H_
#define CLIENT_LIFEVIEW_H_

#include "client_RenderedView.h"
#include "../../../common/common_Point.h"
#include "../../../common/common_MapConstants.h"
#include <SDL2pp/SDL2pp.hh>

class LifeView : public AnimatedView {
private:
  SDL2pp::Texture *texture;

public:
  LifeView(unsigned int id, SDL2pp::Renderer *renderer) : AnimatedView(id, renderer) {
    texture = new SDL2pp::Texture(*getRenderer(), "res/drawable/powerups/hp/hp.png");
  }

  virtual ~LifeView() {
    delete texture;
  }

  virtual SDL2pp::Texture * getTexture(ORIENTATION orient) {
    return texture;
  }

  virtual SDL2pp::Rect * getSRCRect() {
    return new SDL2pp::Rect(0, 0, TERRAIN_REAL_TILE_SIZE, TERRAIN_REAL_TILE_SIZE);
  }

};

#endif
