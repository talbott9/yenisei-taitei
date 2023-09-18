class Background { 
public:
  Background();
  void render(SDL_Rect& camera, int levelID);
  SDL_Rect background;
  SDL_Rect floor;
  SDL_Rect getBox();
  void addXY(int x, int y);
private:
  int backgroundTicks = 0;
};

LTexture gBackground; LTexture gBackgroundSup;
LTexture gFloor; LTexture gFloorSup;
LTexture gLevel1Background, gForestBackground;
LTexture gLevel1Floor, gForestFloor;
