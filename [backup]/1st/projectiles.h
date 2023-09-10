#define NUM_PROJECTILES 300

int activeProjectiles;

class Projectile {
	public:
		 Projectile();
		 static const int MAX_SPEED = 6;
		 void render(int x, int y);
		 void setVariables(int w, int h, int spd, int interval, LTexture* gSetTexture);
		 void setDirection(int directX, int directY);
		 void addProjectiles();
		 int getActiveProjectiles();
		 void resetProjectiles();
		 int projectileTicks; 
		 int getSpd(); int getIntv();
		 int dx, dy;
	private:
		 SDL_Rect mBox; 
		 LTexture* gTexture;
		 int defaultPosX, defaultPosY;
		 double angle;
		 int speed; int intv;
};

Projectile projectiles1[NUM_PROJECTILES];
Projectile projectile1;

