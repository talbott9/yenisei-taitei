#include "background.h"


Background::Background() {
	background.x = 0; background.y = 0;
	background.w = 1600; background.h = 600;
	floor.w = 800; floor.h = 80;
	floor.x = 0; floor.y = SCREEN_HEIGHT - 80;
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

	switch(levelID) {
	case 3:
	  gFloor = gForestFloor;
	  gFloorSup = gForestFloor;	
	  gBackground = gForestBackground;	
	  gBackgroundSup = gForestBackground;
	  floor.h = 300;
	  break;
	default:
	  gFloor = gLevel1Floor;	
	  gFloorSup = gLevel1Floor;	
	  gBackground = gLevel1Background;	
	  gBackgroundSup = gLevel1Background;
	  break;
	}

	floor.y =  SCREEN_HEIGHT - floor.h;
	  
	int intvFloor = 1/slowValue;
	int intvBackground = 25/slowValue;
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

Background background;
