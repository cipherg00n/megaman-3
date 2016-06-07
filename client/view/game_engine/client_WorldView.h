#ifndef CLIENT_WORLDVIEW_H_
#define CLIENT_WORLDVIEW_H_

#include <iostream>

#include "client_RenderedView.h"
#include <SDL2pp/SDL2pp.hh>
#include <map>

#include "../../../common/common_MapView.h"
#include "../../../common/common_ObstacleView.h"
#include "../../../common/common_Point.h"
#include "../../../common/common_MapConstants.h"

#define PATH_LADDER "./res/drawable/blocks/ladder.png"
#define PATH_BLOCK "./res/drawable/blocks/block.png"
#define PATH_NEEDLE "./res/drawable/blocks/spike.png"
#define PATH_SKY "./res/drawable/blocks/sky.jpg"

class WorldView : public RenderedView {
private:
  SDL2pp::Texture *backgroundTexture;
  SDL2pp::Texture *mapTexture;
  bool textureExists;

public:
  WorldView(SDL2pp::Renderer *renderer) : RenderedView(renderer), backgroundTexture(NULL), mapTexture(NULL), textureExists(false) {
  }

  virtual void draw(Point &massCenter) {
    if (textureExists) {
      Point cameraPoint;
      if (massCenter.getX() - (unsigned int) (renderer->GetOutputWidth() / 2) < 0) {
        cameraPoint.setX(0);
        massCenter.setX(renderer->GetOutputWidth() / 2);
      } else if ((unsigned int) getRenderer()->GetOutputWidth() < massCenter.getX() + renderer->GetOutputWidth() / 2) {
        cameraPoint.setX(mapTexture->GetWidth() - renderer->GetOutputWidth());
        massCenter.setX(mapTexture->GetWidth() - renderer->GetOutputWidth() / 2);
      } else cameraPoint.setX(massCenter.getX() - renderer->GetOutputWidth() / 2);

      if (massCenter.getY() - (unsigned int) (renderer->GetOutputHeight() / 2) < 0) {
        cameraPoint.setY(0);
        massCenter.setY(renderer->GetOutputHeight() / 2);
      } else if ((unsigned int) getRenderer()->GetOutputHeight() < massCenter.getY() + renderer->GetOutputHeight() / 2) {
        cameraPoint.setY(mapTexture->GetHeight() - renderer->GetOutputHeight());
        massCenter.setY(mapTexture->GetHeight() - renderer->GetOutputHeight() / 2);
      } else cameraPoint.setY(massCenter.getY() - renderer->GetOutputHeight() / 2);

      renderer->Copy(*backgroundTexture, SDL2pp::Rect(
            cameraPoint.getX(),
            cameraPoint.getY(),
            renderer->GetOutputWidth(), renderer->GetOutputHeight()));
      renderer->Copy(*mapTexture, SDL2pp::Rect(
            cameraPoint.getX(),
            cameraPoint.getY(),
            renderer->GetOutputWidth(), renderer->GetOutputHeight()));
    }
  }

  void from(MapView *mapView) {
    textureExists = false;

    std::map<ObstacleViewType, SDL2pp::Surface*> texturesMap;
    texturesMap[ObstacleViewTypeLadder] = new SDL2pp::Surface(PATH_LADDER);
    texturesMap[ObstacleViewTypeBlock] = new SDL2pp::Surface(PATH_BLOCK);
    texturesMap[ObstacleViewTypeNeedle] = new SDL2pp::Surface(PATH_NEEDLE);
    texturesMap[ObstacleViewTypePrecipice] = new SDL2pp::Surface(PATH_SKY);

    if (mapTexture)
      delete mapTexture;

    if (backgroundTexture)
      delete backgroundTexture;

    mapTexture = new SDL2pp::Texture(*getRenderer(), SDL_PIXELFORMAT_RGBA8888,
          SDL_TEXTUREACCESS_TARGET, mapView->getWidth(), mapView->getHeight());

    backgroundTexture = new SDL2pp::Texture(*getRenderer(), SDL_PIXELFORMAT_RGBA8888,
          SDL_TEXTUREACCESS_TARGET, mapView->getWidth(), mapView->getHeight());

    mapTexture->SetBlendMode(SDL_BLENDMODE_BLEND);

    //Fill all the texture with sky
    SDL2pp::Surface *skySurface = new SDL2pp::Surface(PATH_SKY);
    for (unsigned int i = 0 ; i < mapView->getWidth() ; i += TERRAIN_TILE_SIZE) {
      for (unsigned int j = 0 ; j < mapView->getHeight() ; j += TERRAIN_TILE_SIZE) {
        backgroundTexture->Update(SDL2pp::Rect(i, j, TERRAIN_TILE_SIZE, TERRAIN_TILE_SIZE),
          *skySurface);
      }
    }

    //Iterate the map with the stuff we should draw and if its of that type, draw it where it is
    std::vector<ObstacleView*> * views = mapView->getObstacles();
    for (unsigned int i = 0 ; i < views->size() ; ++i) {
      ObstacleView *view = views->at(i);

      std::map<ObstacleViewType, SDL2pp::Surface*>::iterator it = texturesMap.find(view->getType());
      if (it != texturesMap.end()) {
        mapTexture->Update(SDL2pp::Rect(view->getPoint().getX(), view->getPoint().getY(),
            TERRAIN_TILE_SIZE, TERRAIN_TILE_SIZE),
            *texturesMap[view->getType()]);
      }
    }

    delete texturesMap[ObstacleViewTypeLadder];
    delete texturesMap[ObstacleViewTypeBlock];
    delete texturesMap[ObstacleViewTypeNeedle];
    delete texturesMap[ObstacleViewTypePrecipice];
    delete skySurface;

    textureExists = true;
  }

  virtual ~WorldView() {
    if (mapTexture)
      delete mapTexture;

    if (backgroundTexture)
      delete backgroundTexture;
  }

};

#endif
