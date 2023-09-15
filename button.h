#include "text.h"

int score = 0;
int actualScore = 0;
bool doAddScore;
bool reset;
enum difficultyLevel {easy, normal, hard};
difficultyLevel difficulty = hard;

class Button {
	public:
		Button();
		SDL_Rect getBox();
		void handleEvent(SDL_Event& e);
		void render(std::string text1, std::string text2, SDL_Rect& camera, Textbox* textbox, int selectedDirection);
	private:
		SDL_Rect mBox;
};
