int activeProjectiles;

#define NUM_PROJECTILES 200

class Projectile {
public:
  Projectile();
  static const int MAX_SPEED = 6;
  void shootHG(double x, double y, Enemy* enemy);
  void shootEnemy5(double x, double y, Chara* hildegarde, enemyIDEnum enemyID, int number, double sectionAngle = 360.0, double startingAngle = 0.0, int batch = 10, double spd = 5.0, bool rotate = false);
  void shootEnemy0(double x, double y, Chara* hildegarde, enemyIDEnum enemyID, int number, double sectionAngle = 360.0, double startingAngle = 0.0, int batch = 10, double spd = 5.0, bool rotate = false, bool angleTarget = false, double slow = 1, bool shootBool = 0, bool enemyDead = 0);
  void shootEnemy1(double x, double y, Chara* hildegarde, enemyIDEnum enemyID, int number = 0, double sectionAngle = 0.0, int batch = 0, double spd = 0.0, bool rotate = false, bool shootBool = 0);
  void shootEnemy2(double x, double y, Chara* hildegarde, enemyIDEnum enemyID);
  void shootEnemy3(double x, double y, Chara* hildegarde, enemyIDEnum enemyID, double velX = 0.0, double spd = 5.0, double gravityForce = 0.1, bool rotate = false, int number = 10);
  void shootEnemy4(double x, double y, Chara* hildegarde, enemyIDEnum enemyID);
  void setVariables(int w, int h, double spd, int interval, LTexture* gSetTexture, int orient = 0, int spriteW = 5, int spriteH = 5, bool isLong = false);
  void setProj(SDL_Rect box, double x, double y, double spd, bool isLong);
  void setDirection(int directX, int directY);
  void clearProjectiles();
  int getActiveProjectiles();
  void resetProjectiles();
  void setLongProjBox();
  int projectileTicks, projectilesShot; 
  int getSpd(); int getIntv();
  double dx, dy;
  void moveToXY(double x, double y, bool moveY = true);
  void moveAcc(double x, double y, double acc);
  void moveGravity(double x, double y, double acc, bool moveX = true);
  void moveAngle(double angle);
  void moveOscillate(double x, double y, bool startRight = 1);
  void addAngle(double angle);
  double getAngle(double x, double y);
  double projectileAngle;
  int spriteWidth, spriteHeight;
  SDL_Rect getBox();
  void clearProjectilesPlus();
  int shootTicks, moveTicks; bool shootReturn, moveReturn;
  double distance;
  double gravityTicks = 1;
  double sinAngle, cosAngle;
  bool moveGravityBullet;
  bool initialiseLaser; bool shootLaser;
  int shootAttack4Rand; bool rolledShootAttack4Rand;
  bool initialiseStimulant = 1;
  bool shootStimulant = 1; int stimulantTicks;
  void checkDie(Chara* hildegarde);
  void checkDie1(Chara* hildegarde);
  void checkDiePlus(Chara* hildegarde);
  bool createdProjs;
  void createProjs(int num);
  void destroyProjs(int num);
  void renewProj(int num);
  bool deleteProjs;
  double angle;

  bool shotBatch, disabled;
  bool explode;
  int disableScreenShakeTicks;
  int counter;
  int oscillationTicks, oscillationTicks2;
  bool switchOsc, horizontalOsc;
  bool firstOsc = 1;
  int bouncesOffScreen = 0;
  bool projectileIsLong;
private:
  SDL_Rect mBox;
  SDL_Rect mBox1;
  LTexture* gTexture;
  double posX, posY;
  double defaultPosX, defaultPosY;
  double speed; int intv;
  int actualIntv;
  int orientation;
  int targetX, targetY, originalTargetX, originalTargetY;
  bool shotBullet, isDead;
public:
  Projectile* projs[NUM_PROJECTILES];
};
