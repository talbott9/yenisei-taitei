const int ENEMY_BATTLE_ANIM_FRAMES = 1;
SDL_Rect gEnemyBattleClips[ENEMY_BATTLE_ANIM_FRAMES];

#define NUM_COMPS 5 //companions

class Projectile; class Chara;

enum enemyIDEnum {conradID, saucerID};

class Enemy {
public:
  Enemy();
  SDL_Rect getBox();
  SDL_Rect* currentClip;
  int getCrrPoints();
  void restoreHP();
  void takeDamage();
  //int attack(BattleChara* battleLouis);
  void moveToXY(double x, double y, double speed);
  void doThings(Projectile* projectile1, Projectile* projectile2, Projectile* projectile3, Chara* hildegarde, Projectile* projectile4 = NULL);
  void reset();
  bool moved; bool changeMove;
  int reachedTarget;
  double distanceX, distanceY, distance;
  int actionTicks; bool enemyDead;
  int randX, randY;
  int shotType;
  int pattern, lastPattern;
  double renderAngle;
  double targetX, targetY;
  double speedMod;
  double defaultPosX, defaultPosY;
  void setPosXY(double x, double y);
  void setVel(double x, double y);
  int moveThreshold;
  LTexture* gEnemyTexture;
  enemyIDEnum enemyID;
  void createComps(int num);
  void destroyComps(int num);
  void renewComp(int num);
  bool createdComps, clearComps;
  void setComp(SDL_Rect box, double x, double y, enemyIDEnum id);
  bool ready;
public:
  void set(LTexture* texture, enemyIDEnum id) {
    this->gEnemyTexture = texture;
    this->enemyID = id;
  }
private:
  SDL_Rect mBox;
  int mCurrentHitPoints;
  int mMaxHitPoints;
  double dx, dy;
  double posX, posY;
  Enemy* companions[NUM_COMPS];
};

