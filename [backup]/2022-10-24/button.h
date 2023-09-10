#include "text.h"

class Button {
	public:
		Button();
		SDL_Rect getBox();
		void handleEvent(SDL_Event& e);
		void render(std::string text1, std::string text2, SDL_Rect& camera, Textbox* textbox, int selectedDirection);
		//void battleRender(SDL_Rect& textbox, BattleChara* battleLouis);
	private:
		SDL_Rect mBox;
};

Textbox::Textbox() {
	mBox.x = 0;
	mBox.y = 335;
	mBox.w = SCREEN_WIDTH;
	mBox.h = 146;
}

bool Textbox::getTextValue() {
	return showTextbox;
}

int Textbox::getX() {
	return mBox.x;
}

int Textbox::getY() {
	return mBox.y;
}

int Textbox::getWidth() {
	return mBox.w;
}

int Textbox::getHeight() {
	return mBox.h;
}
