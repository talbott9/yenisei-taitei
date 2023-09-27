#define ENEMY_FRAMES 10
#define NUM_COMPS 50 //companions


class Projectile; class Chara;

enum enemyIDEnum {conradID, saucerID, hyacintheID, troubadourID, bohemondID, ghost1ID = 11};

class Enemy {
public:
  Enemy();
  SDL_Rect getBox();
  int getCrrPoints();
  void restoreHP();
  void takeDamage();
  void takeDamageZako(Projectile* projectile);
  //int attack(BattleChara* battleLouis);
  void moveToXY(double x, double y, double speed, bool drag = true);
  void doThings(Projectile* projectile1, Projectile* projectile2, Projectile* projectile3, Projectile* projectile4, Chara* hildegarde, Chara* yenisei);
  //void zakoDoThings(Chara* hildegarde);
  void reset();
  bool moved; bool changeMove;
  double distanceX, distanceY, distance;
  int actionTicks, timeTicks; bool enemyDead;
  int randX, randY, moveX, moveY;
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
  void createComps(int num, double x, double y);
  void createSingleComp(int num, double x, double y);
  void destroyComps(int num);
  void renewComp(int num);
  bool createdComps, clearComps;
  int numberOfComps;
  void setComp(SDL_Rect box, double x, double y, enemyIDEnum id, LTexture* gTexture, int hitpoints);
  SDL_Rect gEnemyClips[ENEMY_FRAMES];
  int numberOfClips;
  SDL_Rect* currentClip = &gEnemyClips[0];
  void setClips(int w, int h);
  bool ready;
  bool clear = 1;
  int deaths;
  SDL_RendererFlip flipType = SDL_FLIP_NONE;
  void freezeAnim();
  SDL_Rect freezeBox;
  int spriteWidth, spriteHeight;
  bool attackAnim;
  void showTime();
  LTexture gTime, gStoredTime;
  int storedTime;
  bool shoot = 1;
  bool switchMove, reachedTarget;
  bool moveDrag = 1;
  double moveSpeed = 15.0;
  bool deallocated[NUM_COMPS];
  int shootingInterval;
public:
  void set(LTexture* texture, enemyIDEnum id, int w, int h, int numClips) {
    this->gEnemyTexture = texture;
    this->enemyID = id;
    this->mBox.w = w;
    this->mBox.h = h;
    this->numberOfClips = numClips;
  }
private:
  SDL_Rect mBox;
  int mCurrentHitPoints;
  int mMaxHitPoints;
  double dx, dy;
  double posX, posY;
public:
  Enemy* companions[NUM_COMPS];
};

