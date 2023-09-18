#define ENEMY_FRAMES 10
#define NUM_COMPS 5 //companions

class Projectile; class Chara;

enum enemyIDEnum {conradID, saucerID, hyacintheID, troubadourID};

class Enemy {
public:
  Enemy();
  SDL_Rect getBox();
  int getCrrPoints();
  void restoreHP();
  void takeDamage();
  //int attack(BattleChara* battleLouis);
  void moveToXY(double x, double y, double speed);
  void doThings(Projectile* projectile1, Projectile* projectile2, Projectile* projectile3, Projectile* projectile4, Chara* hildegarde, Chara* yenisei);
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
  int numberOfComps;
  void setComp(SDL_Rect box, double x, double y, enemyIDEnum id);
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
  Enemy* companions[NUM_COMPS];
};

