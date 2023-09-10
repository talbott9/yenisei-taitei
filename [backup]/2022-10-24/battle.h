class Battle {
	public:
		SDL_Rect battleIntroSquare;
		SDL_Rect battleEndSquare;
		SDL_Rect battleActionBox;
		Battle();
		//void battling();
		//void battleIntroAnimation();
		//void battleEndAnimation();
		//void battleEnd2ndPart();
		//void resetBattleIntroSquare();
		//void actionBox();
		//void handleEvent(SDL_Event& e);
		bool leaveAlphaValue;
		//void levelChangeAnim();
		bool setAlpha;
	private:
		int alphaValueProgr;
};
