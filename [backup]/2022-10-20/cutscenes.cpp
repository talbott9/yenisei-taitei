#include "renderer.cpp"
#include "button.cpp"
#include <SDL_ttf.h>
#include "cutscenes.h"

bool interactValue = 1;
bool saveGame = 0;
int trigger = 0;
bool promptSelect = 0;
bool inBattle = 0;
bool battleIntro = 0;
std::string dialogueText = "";
int wrpBnd = textbox.getWidth() - 150;

void unshowTextbox(Textbox* textbox) {
	activeDialogue = 0;
	trigger = 0;
	promptSelect = 0;
	selectedDirection = 2;
}

void Cutscene::handleEvent(SDL_Event& e) {
	if(e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		switch(e.key.keysym.sym) {
			case SDLK_z: freeText(&gText);
			     	     trigger++; break;
		}
	}
}
