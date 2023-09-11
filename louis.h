/*This source code copyrighted by Lazy Foo' Productions (2004-2022)
  and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>

//Walking animation
const int WALKING_ANIMATION_FRAMES = 11;
const int BATTLE_ANIM_FRAMES = 1;
const int HG_FRAMES = 7;
SDL_Rect gSpriteClips[WALKING_ANIMATION_FRAMES];
SDL_Rect gHGSpriteClips[HG_FRAMES];
SDL_Rect gBattleClips[BATTLE_ANIM_FRAMES];
SDL_Rect* currentClip;

int attackDirectionTicks = 0;
int attackDirection = 0;
bool rotateDown = 0;
bool rotateUp = 0;
bool HGAttacking = 0;

class Enemy;
class LTexture;
class Projectile;

class Chara {
public:
  static const int DOT_WIDTH = 150;
  static const int DOT_HEIGHT = 103;
  static const int HGDOT_WIDTH = 58;
  static const int HGDOT_HEIGHT = 72;

  double DOT_VEL = 7.0;

  Chara();

  void handleEvent( SDL_Event& e );

  void move();
  void moveHG();

  SDL_Rect getBox();
  double getX(double x), getY(double y);
  int getVelX(); int getVelY();

  void render(SDL_Rect& camera, LTexture* gSpriteSheetTexture);
  void renderHG(SDL_Rect& camera, LTexture* gSpriteSheetTexture);

  int count = 0;
  void setState(int x);
  void setPos(int x, int y);
  void setVel(double dx, double dy);
  bool resetAnim; bool didResetAnim;
  bool moveUp, moveDown, moveLeft, moveRight;
  bool gracePeriod;
  int graceTicks;
  
  int animWobble;
  void shoot(Projectile* projectile, Enemy* enemy);
  bool death; void die();
  bool moved; int deathTicks;
  void moveToXY(double x, double y, double speed);
  double distance; bool changeMove;
  void moveToAcc(double x, double y, double speed, double acc);
  int accTicks;
  double defaultPosX, defaultPosY;
private:
  SDL_Rect mBox;
  double posX, posY;
  double mVelX, mVelY; int mVelXNP, mVelYNP;
};

Chara yenisei;
Chara hildegarde;
