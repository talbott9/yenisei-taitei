#include "button.h"

SDL_Rect gArrowClip[1];

LTexture gText;
LTexture gArrow;
LTexture gYes;
LTexture gNo;

Button button;

int selectedDirection = 0;
int xSelect = 0;
int ySelect = 0;
bool whatToDoPrompt = 1;
bool selectWeapon = 0;
bool selectAssist = 0;
bool attackPrompt = 0;
bool friendsPrompt = 0;
bool coverPrompt = 0;
bool runPrompt = 0;
bool enemyDie = 0;
bool louisDie = 0;
bool endTurn = 0;
int battleTicks = 0;
bool runSuccess = 0;
bool loadedFont = 0;
bool louisHasActed = 0;
bool enemyHasActed = 0;
bool hasActed = 0;
bool enemyAct = 0;
bool activeResponse = 0;
bool activeDialogue = 0;
bool doNotAdvance = 0;
bool enemyMove = 0;
bool enemyHasMoved = 0;
bool isCutscene = 0;
bool success = 0;
int ticks = 0;
int rejectSpan = 0;
bool changeLevelAnimation = 0;

int charCount = 0;
std::string textWritten = "";
std::string battleTextWritten = "";
bool doNotType = 0;
void drawDialogueText(std::string s, LTexture* gText, Textbox* textbox) {
	int wrpBnd = textbox->getWidth() - 150;
	if(!doNotType) {
		if(charCount < s.size()) {
			textWritten += s[charCount]; charCount++;
		}
			gText->loadFromRenderedText(textWritten, White, wrpBnd, gFont); 
			gText->render(textbox->getX() + 150, textbox->getY() + 50); 
	} else {
		gText->loadFromRenderedText(s, White, wrpBnd, gFont);
		gText->render(textbox->getX() + 150, textbox->getY() + 50);
	}
}

void drawBattleText(std::string s, LTexture* gText, SDL_Rect& textbox, int x, int y) {
	int wrpBnd = textbox.w - 150;
	if(!doNotType) {
		if(charCount < s.size()) {
			battleTextWritten += s[charCount];
		}
			gText->loadFromRenderedText(battleTextWritten, White, wrpBnd, gBattleFont); charCount++;
			gText->render(x, y); 
	} else {
		gText->loadFromRenderedText(s, White, wrpBnd, gBattleFont);
		gText->render(x, y);
	}
}
void loadFont(int size) {
		gBattleFont= TTF_OpenFont("resources/fonts/battlefont.ttf", size);
		gFont= TTF_OpenFont("resources/fonts/font1.ttf", size);
}

void freeText(LTexture* gText) {
	charCount = 0;
	gText->free();
	textWritten = "";
	battleTextWritten = "";
}

void resetChars() {
	textWritten = "";	
}

void resetBattleState() {
	whatToDoPrompt = 1; selectWeapon = 0; attackPrompt = 0;
	friendsPrompt = 0; coverPrompt = 0; runPrompt = 0;
	enemyDie = 0; louisDie = 0; battleTicks = 0;
	selectAssist = 0; endTurn = 0; runSuccess = 0; 
	loadedFont = 0; enemyAct = 0; activeResponse = 0;
	freeText(&gText);
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

void Button::handleEvent( SDL_Event& e )
{
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    	{
        switch( e.key.keysym.sym )
        {
	    case SDLK_UP: selectedDirection = 0; break;
	    case SDLK_DOWN: selectedDirection = 1; break;
            case SDLK_LEFT: selectedDirection = 2; break;
	    case SDLK_RIGHT: selectedDirection = 3; break;
	    default: selectedDirection = 2; break;

        }
    }
}
