#define NUM_TILES 300

class Background { 
public:
  Background();
  void render(SDL_Rect& camera, int levelID);
  SDL_Rect background;
  SDL_Rect floor;
  SDL_Rect getBox();
  void addXY(int x, int y);
  SDL_Rect mBox;
  void createTiles(int num);
  bool createdTiles;
  int tileXMultiplier = 0;
  void renderTiles(int startX, int startY, int num);
  LTexture gTexture;
  Background* tiles[NUM_TILES];
  SDL_Rect backgroundColor;
  bool renderVertically = 1;
  void renderBackground();
  int intvFloor, intvBackground;
private:
  int backgroundTicks = 0;
};

LTexture gBackground; LTexture gBackgroundSup;
LTexture gFloor; LTexture gFloorSup;
LTexture gLevel1Background, gForestBackground, gIceBackground;
LTexture gLevel1Floor, gForestFloor;
LTexture gMountainBack, gMountainFront, gMountainClouds, gDesertTile, gDesertTile1, gDesertTower, gBackgroundMoon, gIceTile, gIceTile1, gIceTile2;
