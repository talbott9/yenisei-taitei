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
bool unlockedCredits;
bool isCreditsScene;
int creditsTicks; 
bool speedUpCredits;
bool finishedCredits;

void loadFont(int size) {
		gBattleFont= TTF_OpenFont("resources/fonts/battlefont.ttf", size);
		gBattleFontSmall= TTF_OpenFont("resources/fonts/battlefont.ttf", 20);
		gFont= TTF_OpenFont("resources/fonts/font1.ttf", 20);
		gFancyFont = TTF_OpenFont("resources/fonts/Basic Roman-BoldItalic.ttf", 25);
}

int alphaTicks;
SDL_Rect alphaSquare;
bool isGameOverScreen;
bool gameOverScreenSuccess;
//std::string deathMessage[10] {"Doth bitter death separate thus?", "Is this the promised end? Or the image of that horror?" };
void gameOverScreen() {
	isGameOverScreen = 1;
	/*if(actualScore >= 10000 && !createdMessage) {
		if(!createdMessage) {
			createdMessage = 1;	
			std::ofstream thanks("thanks");
			thanks << "Thank you for playing!\nLeave comments to 'alves967@yahoo.co.jp'.";
		}
	}*/
	if(actualScore >= 15000) {
		if(!createdCredits) {
			std::ofstream credits("credits");
			credits << "Programming: Henricus\n\n"
				   "Art: Henricus\n\n"
				   "Music: \"Kozato\" by Henricus\n" 
				   "       \"Tachanka\"\n"
				   "       \"Khayan\" by Vladimir Oyun Oidupaa\n"
				   "       \"Men tyva men\" by the Tuvan National Orchestra\n\n" 
				   "(C) 2023 alves967@yahoo.co.jp";
			createdCredits = 1;
		}
		unlockedCredits = 1;
	}
	if(alphaTicks < 255)
		alphaTicks+=15;
	else
		gameOverScreenSuccess = 1;
	//SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);	
	//SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, alphaTicks);
	//SDL_RenderFillRect(gRenderer, &alphaSquare);
	if(!unlockedCredits) {
		gGameOverScreen.setBlendMode(SDL_BLENDMODE_BLEND);
		gGameOverScreen.setAlpha(alphaTicks);
		gGameOverScreen.render(0, 0);
	} else {
		gGameOverScreen2.setBlendMode(SDL_BLENDMODE_BLEND);
		gGameOverScreen2.setAlpha(alphaTicks);
		gGameOverScreen2.render(0, 0);
	}
	std::string s = "Score....." + std::to_string(actualScore);
	gText.loadFromRenderedText(s, Grey, 0, gBattleFont);
	gText.render(camera.w/4, camera.h/4);
	if(!unlockedCredits)
		gText1.loadFromRenderedText("Press 'x' to try again, 'q' to quit", White, 0, gFont);
	else
		gText1.loadFromRenderedText("Press 'x' to try again, 'q' to quit, 'c' for credits", White, 0, gFont);
	gText1.render(camera.w/3, camera.h - 40);
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
		if(menuBuffer >= 15 && !isCreditsScene) {
        		inMenuScreen = 0;
			Mix_HaltMusic();
			gBattleSong = Mix_LoadMUS("resources/music/battlesong.ogg");
		} 
	}
	if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_z && e.key.repeat == 0) {
		if(!finishedCredits) {
			speedUpCredits = 1;
		} else {
			reset = 1; inMenuScreen = 1;
		}
	}
	if(e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_z)
		speedUpCredits = 0;
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
	if(Mix_PlayingMusic() == 0) {
		gKozato = Mix_LoadMUS("resources/music/kozato.ogg");
		Mix_PlayMusic(gKozato, -1);
	}
	gTuvaMap.render(0, 0);
	gText.loadFromRenderedText("Press any key to start", White, 0, gBattleFontSmall);
	if(menuTicks > 30)
		gText.render(125, SCREEN_HEIGHT - SCREEN_HEIGHT/6 + 25);
	if(menuTicks >= 60)
		menuTicks = 0;
}

void creditsScene() {
	if(!(creditsTicks >= 6000)) {
		creditsTicks += 2;
		if(speedUpCredits)
			creditsTicks += 4;
	} else {
		finishedCredits = 1;
	}
	//printf("%i\n", creditsTicks);
	isCreditsScene = 1;
	int illust2y = camera.h + 250 - creditsTicks/4;
	int illust1y = 0;
	if(!(illust2y <= camera.y - 500)) {
		gIllust2.render(camera.w/2 + 50, camera.h + 450 - creditsTicks/4);
	}
	if(!(illust1y <= camera.y - 400)) {
		gIllust1.render(camera.w/2 - 150, camera.h + 1100 - creditsTicks/4);
	}
	gText.loadFromRenderedText(
			"          Programming\n\n\n\n             Henricus\n\n\n\n\n\n"
			"                Art    \n\n\n\n           Henricus\n\n\n\n\n\n"
			"             Music   \n\n\n\n" 
					     "\"Kozato\" by Henricus\n"
			                     "\"Tachanka\"\n"
					     "\"Khayan\" by Vladimir Oidupaa\n"
					     "\"Men Tyva Men\" by the Tuvan National Orchestra\n\n\n\n\n\n"
			"                  Thank you for playing!", White, 0, gFancyFont);
	gText.render(camera.w/2 - 200, camera.h + 150 - creditsTicks/4);
}
