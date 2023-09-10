#define NUM_PROJECTILES 500

int activeProjectiles;

class Projectile {
public:
  Projectile();
  static const int MAX_SPEED = 6;
  void shootHG(int x, int y, Enemy* enemy);
  void shootEnemy0(double x, double y, Chara* hildegarde, int number);
  void shootEnemy1(double x, double y, Chara* hildegarde);
  void shootEnemy2(double x, double y, Chara* hildegarde);
  void shootEnemy3(double x, double y, Chara* hildegarde);
  void shootEnemy4(double x, double y, Chara* hildegarde);
  void setVariables(int w, int h, double spd, int interval, LTexture* gSetTexture, int orient = 0, int spriteW = 5, int spriteH = 5);
  void setDirection(int directX, int directY);
  void addProjectiles();
  int getActiveProjectiles();
  void resetProjectiles();
  int projectileTicks, projectilesShot; 
  int getSpd(); int getIntv();
  double dx, dy;
  void moveToXY(double x, double y);
  void moveGravity(double x, double y, double acc);
  void moveAngle(double angle);
  double projectileAngle;
  int spriteWidth, spriteHeight;
  SDL_Rect getBox();
  void clearProjectiles(); void clearProjectilesHG();
  void clearProjectiles1();
  void clearProjectilesPlus();
  int shootTicks, moveTicks; bool shootReturn, moveReturn;
  double distance;
  double gravityTicks = 1;
  double sinAngle, cosAngle;
  bool moveGravityBullet;
  SDL_Rect laserBoxes[NUM_PROJECTILES];
  bool initialiseLaser; bool shootLaser;
  int shootAttack4Rand; bool rolledShootAttack4Rand;
  bool initialiseStimulant = 1;
  bool shootStimulant = 1; int stimulantTicks;
  void checkDie(Chara* hildegarde);
  void checkDie1(Chara* hildegarde);
  void checkDiePlus(Chara* hildegarde);
private:
  SDL_Rect mBox; 
  LTexture* gTexture;
  double posX, posY;
  double defaultPosX, defaultPosY;
  double angle;
  double speed; int intv;
  int actualIntv;
  int orientation;
  int targetX, targetY;
  bool shotBullet;
};

Projectile projectiles[NUM_PROJECTILES];
Projectile projectiles1[NUM_PROJECTILES];
Projectile projectile1;
Projectile projectiles2[NUM_PROJECTILES];
Projectile projectile2;
Projectile projectiles3[NUM_PROJECTILES];
Projectile projectile3;
Projectile projectiles4[NUM_PROJECTILES];
Projectile projectile4;
Projectile projectile5;
Projectile saucerProjectiles[NUM_PROJECTILES];
Projectile saucerProjectile;
