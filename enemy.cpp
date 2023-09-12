#include "enemy.h"


Enemy enemy1;
Enemy saucer;

Enemy::Enemy() {
	mBox.w = 107;
	mBox.h = 97;
	defaultPosX = SCREEN_WIDTH/2 - mBox.w/2; 
	defaultPosY = -200;
	posX = defaultPosX;
	posY = defaultPosY;
	mBox.x = posX;
	mBox.y = posY;
	randX = posX; randY = SCREEN_HEIGHT/6;
	mCurrentHitPoints = 100;
	mMaxHitPoints = 100;
	enemy1.set(&gEnemy1Texture, 0);
	saucer.set(&gSaucerTexture, 1);
}

SDL_Rect Enemy::getBox() {
	return mBox;
}

int Enemy::getCrrPoints() {
	return mCurrentHitPoints;
}

void Enemy::setPosXY(double x, double y) {
	posX = x; posY = y;
	mBox.x = posX; mBox.y = posY;
}

void Enemy::restoreHP() {
	mCurrentHitPoints = mMaxHitPoints;
}

void Enemy::setVel(double x, double y) {
	dx = x; dy = y;
}

void Enemy::takeDamage() {
	if(mCurrentHitPoints - 2 <= 0) {
		enemyDead = 1;
		mCurrentHitPoints = mMaxHitPoints;
	}
	else
		mCurrentHitPoints -= 2;
}

void Enemy::moveToXY(double x, double y, double speed) {
	if(changeMove) {
		changeMove = 0;
		moved = 0;
	}
	if(!moved) {
		double side1 = y - posY;
		double side2 = posX - x;
		double r = sqrt(side1 * side1 + side2 * side2);
		double sinAngle = (side1/r);
		double cosAngle = (side2/r);
		distance = r;
		if(posX > x)
			dx = -speed*cosAngle;
		else {
			cosAngle = -cosAngle;
			dx = speed*cosAngle;
		}
		if(posY < y)
			dy = speed*sinAngle;
		else {
			sinAngle = -sinAngle;
			dy = -speed*sinAngle;	
		}
		moved = 1;
	}
	int dist = distance;
	if(dist != 0) {
		double distanceX = posX - x;
		double distanceY = y - posY;
		double speedMod = sqrt(distanceX*distanceX + distanceY*distanceY)/distance;
		if(speedMod > 1)
			speedMod = 0.1;
		dx *= speedMod;	
		dy *= speedMod;
		posX += dx; posY += dy;
		mBox.x = posX; mBox.y = posY;
		if(speedMod != 0) {
		  dx /= speedMod;
		  dy /= speedMod;
		}
		//printf("%g/%g/%g/%g/%g/%g/%g/%g\n", distanceX, distanceY, distance, speedMod, dx, dy, x, y);
	} else {
		posX = x; posY = y;
		dx = 0; dy = 0;
	}
}



