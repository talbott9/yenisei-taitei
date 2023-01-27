#include <cstdio>
#include <iostream>

class Textbox {
	public:
		bool showTextbox;
		bool getTextValue();
		void handleEvent(SDL_Event& e);
		void render(SDL_Rect& camera, std::string string);
		SDL_Rect getBox();
		int getX();
		int getY();
		int getWidth();
		int getHeight();
	private:
		SDL_Rect mBox;
};

Textbox textbox;
Textbox battleActionBox;
