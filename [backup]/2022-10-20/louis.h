/*This source code copyrighted by Lazy Foo' Productions (2004-2022)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "tiling.h"
#include "objects.h"

//Walking animation
const int WALKING_ANIMATION_FRAMES = 11;
const int BATTLE_ANIM_FRAMES = 1;
const int HG_FRAMES = 6;
SDL_Rect gSpriteClips[WALKING_ANIMATION_FRAMES];
SDL_Rect gHGSpriteClips[HG_FRAMES];
SDL_Rect gBattleClips[BATTLE_ANIM_FRAMES];
SDL_Rect* currentClip;

bool louisMove = 0;
bool louisHasMoved = 0;
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
		//The dimensions of the dot
		static const int DOT_WIDTH = 150;
		static const int DOT_HEIGHT = 103;
		static const int HGDOT_WIDTH = 58;
		static const int HGDOT_HEIGHT = 72;

		//Maximum axis velocity of the dot
		double DOT_VEL = 5.0;

		//Initializes the variables
		Chara();

		//Takes key presses and adjusts the dot's velocity
		void handleEvent( SDL_Event& e );

		//Moves the dot
		void move();
		void moveHG();
	
		//Centers the camera over the dot
		void setCamera( SDL_Rect& camera );

		SDL_Rect getBox();
		double getX(double x), getY(double y);
		int getVelX(); int getVelY();

		//Shows the dot on the screen
		void render(SDL_Rect& camera, LTexture* gSpriteSheetTexture);
		void renderHG(SDL_Rect& camera, LTexture* gSpriteSheetTexture);

		int checkState(int x);
		int moveState = 1;
		int turnState = 1;
		int count = 0;
		int cutsceneTurnState = 1;
		void setState(int x);
		void setPos(int x, int y);
		void moveToXY(int x, int y, int speed);
		void moveRandomly();
		bool resetAnim;
		int animWobble;
		void shoot(Projectile* projectile);
		
		void warp(int warpLevelID);
    private:
		//Collision box of the dot
		SDL_Rect mBox;

		double posX, posY;

		//The velocity of the dot
		double mVelX, mVelY; int mVelXNP, mVelYNP;
};

Chara yenisei;
Chara hildegarde;
