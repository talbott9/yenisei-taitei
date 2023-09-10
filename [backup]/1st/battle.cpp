#include "battle.h"
#include "enemy.cpp"

Battle battle;
Cutscene cutscene;

bool endBattle = 0;

void resetCamera(SDL_Rect* camera) {
	camera->x = 0;
	camera->y = 0;
}

Battle::Battle() {
	battleIntroSquare.x = camera.w/2; battleIntroSquare.y = camera.h/2;
	battleIntroSquare.w = 1; battleIntroSquare.h = 1;

        battleActionBox.w = 500; battleActionBox.h = 150;
	battleActionBox.x = camera.w/2 - battleActionBox.w/2; battleActionBox.y = camera.y + 20;

	battleEndSquare.x = camera.x; battleEndSquare.y = camera.y;
	battleEndSquare.w = camera.w; battleEndSquare.h = camera.h;

	int alphaValueProgr = 0; setAlpha = 0;
}

int getXthButton() {
	//Gets button from 1st to 16th, column by column
	switch(xSelect) {
		case 0: switch(ySelect) {
				case 0: return 1; break;
				case 1: return 2; break;
				case 2: return 3; break;
				case 3: return 4; break;
			} break;
		case 1: switch(ySelect) {
				case 0: return 5; break;
				case 1: return 6; break;
				case 2: return 7; break;
				case 3: return 8; break;
			} break;
		case 2: switch(ySelect) {
				case 0: return 9; break;
				case 1: return 10; break;
				case 2: return 11; break;
				case 3: return 12; break;
			} break;
		case 3: switch(ySelect) {
				case 0: return 13; break;
				case 1: return 14; break;
				case 2: return 15; break;
				case 3: return 16; break;
			} break;
	}
}
