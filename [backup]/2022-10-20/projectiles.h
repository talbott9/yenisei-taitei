#define NUM_PROJECTILES 500

int activeProjectiles;

class Projectile {
	public:
		 Projectile();
		 static const int MAX_SPEED = 6;
		 void shootHG(int x, int y);
		 void shootEnemy1(double x, double y, Chara* hildegarde);
		 void shootEnemy2(double x, double y, Chara* hildegarde);
		 void shootEnemy3(double x, double y, Chara* hildegarde);
		 void shootEnemy4(double x, double y, Chara* hildegarde);
		 void shootEnemy5(double x, double y, Chara* hildegarde);
		 void setVariables(int w, int h, double spd, int interval, LTexture* gSetTexture, int orient = 0, int spriteW = 5, int spriteH = 5);
		 void setDirection(int directX, int directY);
		 void addProjectiles();
		 int getActiveProjectiles();
		 void resetProjectiles();
		 int projectileTicks; 
		 int getSpd(); int getIntv();
		 double dx, dy;
		 void moveToXY(double x, double y);
		 void moveGravity(double x, double y, double acc);
		 int spriteWidth, spriteHeight;
		 SDL_Rect getBox();
		 void clearProjectiles();
		 int shootTicks; bool shootReturn;
		 double distance;
		 double gravityTicks = 1;
		 double sinAngle, cosAngle;
		 bool moveGravityBullet;
		 SDL_Rect laserBoxes[NUM_PROJECTILES];
		 bool initialisedLaser;
	private:
		 SDL_Rect mBox; 
		 LTexture* gTexture;
		 double posX, posY;
		 double defaultPosX, defaultPosY;
		 double angle;
		 double speed; int intv;
		 int orientation;
		 int targetX, targetY;
		 bool shotBullet;
};

Projectile projectiles1[NUM_PROJECTILES];
Projectile projectile1;
Projectile projectiles2[NUM_PROJECTILES];
Projectile projectile2;
Projectile projectiles3[NUM_PROJECTILES];
Projectile projectile3;
Projectile projectiles4[NUM_PROJECTILES];
Projectile projectile4;
