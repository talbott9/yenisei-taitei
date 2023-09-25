#include "background.h"

Background background;
Background desertTile, desertTile1, desertTower, backgroundMoon, iceTile, iceTile1, iceTile2;


Background::Background() {
	background.x = 0; background.y = 0;
	background.w = 1600; background.h = 600;
	floor.w = 800; floor.h = 80;
	floor.x = 0; floor.y = SCREEN_HEIGHT - 80;\
	desertTile.mBox.x = 0; desertTile.mBox.y = 0;
	desertTile.mBox.w = 30; desertTile.mBox.h = 32;
	desertTile.gTexture = gDesertTile;
	desertTile1.mBox.x = 0; desertTile1.mBox.y = 0;
	desertTile1.mBox.w = 30; desertTile1.mBox.h = 32;
	desertTile1.gTexture = gDesertTile1;
	desertTower.mBox.x = 0; desertTower.mBox.y = 0;
	desertTower.mBox.w = 125 + 100; desertTower.mBox.h = 406;
	desertTower.gTexture = gDesertTower;
	desertTower.renderVertically = 0;

	iceTile.mBox = {0, 0, 30, 32};
	iceTile.gTexture = gIceTile;
	iceTile1.mBox = iceTile.mBox;
	iceTile1.gTexture = gIceTile1;
	iceTile1.renderVertically = 0;
	iceTile2.mBox = iceTile.mBox;
	iceTile2.gTexture = gIceTile2;

	backgroundColor = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
}

SDL_Rect Background::getBox() {
	return background;
}

void Background::addXY(int x, int y) {
	background.x += x;
	background.y += y;
}

void Background::render(SDL_Rect& camera, int levelID) {
	backgroundTicks++;
		  
	intvFloor = 1/slowValue;
	intvBackground = 25/slowValue;

	switch(levelID) {
	case 2:
	  SDL_SetRenderDrawColor(gRenderer, 0, 0, 50, 255);
	  SDL_RenderFillRect(gRenderer, &backgroundColor);
	  
	  gBackground = gIceBackground;
	  gBackgroundSup = gIceBackground;
	  renderBackground();

	  iceTile.renderTiles(iceTile.mBox.x - camera.x, camera.y + 535, NUM_TILES);
	  if(backgroundTicks % 1 == 0)
	    iceTile.mBox.x -= 5/intvFloor;
	  if(iceTile.mBox.x <= -iceTile.mBox.w)
	    iceTile.mBox.x = 0;
	  
	  iceTile1.renderTiles(iceTile1.mBox.x - camera.x, camera.y + 503, 30);
	  if(backgroundTicks % 1 == 0)
	    iceTile1.mBox.x -= 5/intvFloor;
	  if(iceTile1.mBox.x <= -iceTile1.mBox.w)
	    iceTile1.mBox.x = 0;

	  iceTile2.renderTiles(iceTile2.mBox.x - camera.x, camera.h - 50, 60);
	  if(backgroundTicks % 1 == 0)
	    iceTile2.mBox.x -= 5/intvFloor;
	  if(iceTile2.mBox.x <= -iceTile2.mBox.w)
	    iceTile2.mBox.x = 0;
	  
	  break;
	case 3:
	  gFloor = gForestFloor;
	  gFloorSup = gForestFloor;	
	  gBackground = gForestBackground;	
	  gBackgroundSup = gForestBackground;
	  floor.h = 300;
	  renderBackground();
	  break;
	case 4:
	  SDL_SetRenderDrawColor(gRenderer, 0, 0, 50, 255);
	  SDL_RenderFillRect(gRenderer, &backgroundColor);
	  
	  desertTile.renderTiles(desertTile.mBox.x - camera.x, camera.y + 300, NUM_TILES);
	  if(backgroundTicks % 1 == 0)
	    desertTile.mBox.x -= 5/intvFloor;
	  if(desertTile.mBox.x <= -desertTile.mBox.w)
	    desertTile.mBox.x = 0;

	  
	  desertTower.renderTiles(desertTower.mBox.x - camera.x, camera.y + camera.h-desertTower.mBox.h, 10);
	  if(backgroundTicks % 1 == 0)
	    desertTower.mBox.x -= 5/intvFloor;
	  if(desertTower.mBox.x <= -desertTower.mBox.w)
	    desertTower.mBox.x = 0;
	  
	  desertTile1.renderTiles(desertTile1.mBox.x - camera.x, camera.y + camera.h-desertTile1.mBox.h, NUM_TILES);
	  if(backgroundTicks % 1 == 0)
	    desertTile1.mBox.x -= 5/intvFloor;
	  if(desertTile1.mBox.x <= -desertTile1.mBox.w)
	    desertTile1.mBox.x = 0;

	  gBackgroundMoon.render(SCREEN_WIDTH - 150, 50);

	  break;
	default:
	  gFloor = gLevel1Floor;	
	  gFloorSup = gLevel1Floor;	
	  gBackground = gLevel1Background;	
	  gBackgroundSup = gLevel1Background;
	  renderBackground();
	  break;
	}
}


void Background::createTiles(int num) {
  if(!createdTiles) {
    for(int i = 0; i < num; i++) {
      tiles[i] = new Background();
      tiles[i]->mBox = mBox;
    }
    createdTiles = 1;
  }
}

void Background::renderTiles(int startX, int startY, int num) {
  createTiles(num);
  SDL_Rect camera2 = camera;
  camera2.w += mBox.w;
  for(int i = 0; i < num; i++) {
    tiles[i]->mBox.x = (tiles[i]->mBox.w*tileXMultiplier);
    if(checkCollision(camera2, tiles[i]->mBox)) {
      gTexture.render((startX - camera.x) + tiles[i]->mBox.x, startY);
      tileXMultiplier++;
    } else if(renderVertically) {
      startY += tiles[i]->mBox.h;
      tileXMultiplier = 0;
    }
    //printf("%b, %i, %i\n", checkCollision(camera, tiles[i]->mBox), camera.w);
  }
  tileXMultiplier = 0;
}

void Background::renderBackground() {
  floor.y =  SCREEN_HEIGHT - floor.h;

  gBackground.render(background.x, background.y);
  gBackgroundSup.render(background.x + background.w, background.y);
  gFloor.render(floor.x - camera.x, floor.y - camera.y);
  gFloorSup.render(floor.x + floor.w - camera.x, floor.y - camera.y);

  if(backgroundTicks % 1 == 0)
    floor.x -= 5/intvFloor;
  if(backgroundTicks % intvBackground == 0) {
    background.x -= 5;
    backgroundTicks = 0;
  }
  if(background.x <= -background.w)
    background.x = 0;
  if(floor.x <= -floor.w)
    floor.x = 0;
}
