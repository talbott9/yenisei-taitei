#include "button.h"

LTexture gText;
LTexture gText1;
//LTexture gText2;
LTexture gScore;

Button button;

int selectedDirection = 0;
int xSelect = 0;
int ySelect = 0;

bool inMenuScreen = 1;

bool createdMessage;
bool createdCredits;

void loadFont(int size) {
		gBattleFont= TTF_OpenFont("resources/fonts/battlefont.ttf", size);
		gBattleFontSmall= TTF_OpenFont("resources/fonts/battlefont.ttf", 20);
		gFont= TTF_OpenFont("resources/fonts/font1.ttf", 20);
}

int alphaTicks;
SDL_Rect alphaSquare;
//std::string deathMessage[10] {"Doth bitter death separate thus?", "Is this the promised end? Or the image of that horror?" };
void gameOverScreen() {
	if(actualScore >= 10000 && !createdMessage) {
		createdMessage = 1;	
		std::ofstream thanks("thanks");
		thanks << "Thank you for playing!\nComments? 'alves967@yahoo.co.jp'.";
	}
	if(actualScore >= 20000 && !createdCredits) {
		createdCredits = 1;
		std::ofstream credits("credits");
		credits << "Programming: Henricus\nMusic (if there is any): Henricus\nArt: Henricus\n";
	}
	alphaSquare.w = SCREEN_WIDTH; alphaSquare.h = SCREEN_HEIGHT;
	alphaSquare.x = camera.x; alphaSquare.y = camera.y;
	if(alphaTicks < 100)
		alphaTicks+=5;
	SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);	
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, alphaTicks);
	SDL_RenderFillRect(gRenderer, &alphaSquare);
	std::string s = "Score....." + std::to_string(actualScore);
	gText.loadFromRenderedText(s, White, 0, gBattleFont);
	gText.render(camera.w/4, camera.h/4);
	gText1.loadFromRenderedText("Press 'x' to try again, 'q' to quit", White, 0, gFont);
	gText1.render(camera.w/3, camera.h - camera.h/4);
}

void showScore() {
	gScore.loadFromRenderedText("Score....." + std::to_string(score), White, 0, gBattleFontSmall);
	gScore.render(camera.y + 5, camera.x + 5);
	if(score < actualScore)
		score += 20;
}

void resetXYSelect() {
	xSelect = 0;
	ySelect = 0;
}

Button::Button() {
	mBox.x = 50;
	mBox.y = 50;
	mBox.w = 30;
	mBox.h = 30;
}

SDL_Rect Button::getBox() {
	return mBox;
}

int menuBuffer;
void Button::handleEvent( SDL_Event& e )
{
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    	{
		if(menuBuffer >= 15)
        		inMenuScreen = 0;
	}
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

int menuTicks;
void renderMenuScreen() {
	menuTicks++;
	gTuvaMap.render(0, 0);
	gText.loadFromRenderedText("Press any key to start", White, 0, gBattleFontSmall);
	if(menuTicks > 30)
		gText.render(125, SCREEN_HEIGHT - SCREEN_HEIGHT/6 + 25);
	if(menuTicks >= 60)
		menuTicks = 0;
}
