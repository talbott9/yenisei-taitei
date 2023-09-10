class Cutscene {
	public:
		void interruptBed(Textbox* textbox, SDL_Rect& camera);
		void render( SDL_Rect& camera );
		void handleEvent(SDL_Event& e);
	private:
};
