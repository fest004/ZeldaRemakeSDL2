#include "zeldaEng.h"

class tilemap {
public:
  tilemap();
  ~tilemap();

  void LoadTilemap(int array[20][25]);
  void DrawTileMap();

private:
  SDL_Rect source, destination;

  SDL_Texture *textureMissing;
  SDL_Texture *ground1;
  SDL_Texture *platform2;

  int map[20][25];
};