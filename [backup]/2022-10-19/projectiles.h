#define NUM_PROJECTILES 300

int activeProjectiles;

class Projectile {
	public:
		 Projectile();
		 static const int MAX_SPEED = 6;
		 void shootHG(int x, int y);
		 void shootEnemy(int x, int y, Chara* hildegarde);
		 void setVariables(int w, int h, double spd, int interval, LTexture* gSetTexture, int orient = 0, int spriteW = 5, int spriteH = 5);
		 void setDirection(int directX, int directY);
		 void addProjectiles();
		 int getActiveProjectiles();
		 void resetProjectiles();
		 int projectileTicks; 
		 int getSpd(); int getIntv();
		 double dx, dy;
		 void moveToXY(int x, int y);
		 int spriteWidth, spriteHeight;
		 SDL_Rect getBox();

	private:
		 SDL_Rect mBox; 
		 LTexture* gTexture;
		 int defaultPosX, defaultPosY;
		 double angle;
		 double speed; int intv;
		 int orientation;
		 int targetX; int targetY;
		 bool shotBullet;
};

Projectile projectiles1[NUM_PROJECTILES];
Projectile projectile1;
Projectile projectiles2[NUM_PROJECTILES];
Projectile projectile2;
