#include "enemy.h"


Enemy enemy1, saucer, hyacinthe, troubadour, bohemond;



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
	enemy1.set(&gEnemy1Texture, conradID, 107, 97, 1);
	saucer.set(&gSaucerTexture, saucerID, 107, 97, 1);
	hyacinthe.set(&gHyacintheTexture, hyacintheID, 37, 64, 2);
	troubadour.set(&gTroubadourTexture, troubadourID, 46, 85, 4);
	bohemond.set(&gBohemondTexture, bohemondID, 59, 100, 3);
	enemy1.setClips(enemy1.mBox.w, enemy1.mBox.h);
	saucer.setClips(saucer.mBox.w, saucer.mBox.h);
	hyacinthe.setClips(hyacinthe.mBox.w, hyacinthe.mBox.h);
	troubadour.setClips(troubadour.mBox.w, troubadour.mBox.h);
	bohemond.setClips(bohemond.mBox.w, bohemond.mBox.h);
}

void Enemy::setClips(int w, int h) {
  for(int i = 0; i < numberOfClips; i++) {
    gEnemyClips[i].x = w*i;
    gEnemyClips[i].y = 0;
    gEnemyClips[i].w = w;
    gEnemyClips[i].h = h;
  }
}

void Enemy::setComp(SDL_Rect box, double x, double y, enemyIDEnum id) {
  posX = x;
  posY = y;
  mBox.x = posX;
  mBox.y = posY;
  mBox.w = box.w;
  mBox.h = box.h;
  defaultPosX = posX;
  defaultPosY = posY;
  enemyID = id;
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

void Enemy::moveToXY(double x, double y, double speed, bool drag) {
	if(changeMove) {
		changeMove = 0;
		moved = 0;
		dx = 0.0; dy = 0.0;
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
		reachedTarget = 0;
		moved = 1;
	}
	double distanceX = posX - x;
	double distanceY = y - posY;
	if(drag) {
	  if(abs(distanceX) > abs(dx) || abs(distanceY) > abs(dy)) {
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
	} else {
	  if(abs(distanceX) > abs(dx) || abs(distanceY) > abs(dy)) {
	    posX += dx; posY += dy;
	    mBox.x = posX; mBox.y = posY;
	  } else {
	    posX = x; posY = y;
	    dx = 0; dy = 0;
	    reachedTarget = 1;
	  }
	}
}

void Enemy::createComps(int num) { //companions
  if(!createdComps) {
    for(int i = 0; i < num; i++) {
      companions[i] = new Enemy();
      companions[i]->enemyID = enemyID;
    }
    //printf("created bullets #%i, %i, %i\n", num, mBox.w, mBox.h);
    createdComps = 1;
  }
}

void Enemy::destroyComps(int num) {
  for(int i = 0; i < num; i++) {
    //projs[i]->clearProjectilesPlus();
    delete companions[i];
  }
  //printf("deleted bullet #%i\n", num);
  createdComps = 0;
}

void Enemy::renewComp(int num) {
  delete companions[num];
  companions[num] = new Enemy();
}

void Enemy::showTime() {
  int time = timeTicks/60;
  gTime.loadFromRenderedText(std::to_string(time), White, 0, gBattleFontSmall);
  gStoredTime.loadFromRenderedText(std::to_string(storedTime), Yellow, 0, gBattleFontSmall);
  if(time >= 10)
    gTime.render(camera.w - 30, camera.y + 5);
  else
    gTime.render(camera.w - 20, camera.y + 5);
  if(storedTime >= 10)
    gStoredTime.render(camera.w - 70, camera.y + 5);
  else
    gStoredTime.render(camera.w - 60, camera.y + 5);
}
