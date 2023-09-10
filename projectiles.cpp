#include "projectiles.h"
#include <cmath>

#define PI 3.14159265

SDL_Rect showBox[NUM_PROJECTILES];
int enemyIDGlobal;

Projectile::Projectile() {
	mBox.x = 0.0; mBox.y = 0.0;
	posX = 333.3; posY = 201.8;
	activeProjectiles = 0;
	projectile1.setVariables(9, 9, 6.0, 5, &gHGArrow1Texture, 0, 9, 32);
	projectile2.setVariables(5, 5, 7.0, 30, &gBullet2, 0, 10, 10);
	projectile3.setVariables(15, 15, 6.0, 10, &gBullet1, 0, 25, 25);
	projectile4.setVariables(5, 5, 7.0, 5, &gBullet2);
	projectile5.setVariables(15, 15, 9.0, 2, &gBullet1, 0, 25, 25);
	saucerProjectile.setVariables(10, 23, 9.0, 2, &gSaucerBullet, 0, 23, 23);
}

void Projectile::setVariables(int w, int h, double spd, int interval, LTexture* gSetTexture, int orient, int spriteW, int spriteH) {
	gTexture = gSetTexture;
	mBox.w = w; mBox.h = h;
	speed = spd;
	intv = interval;
	orientation = orient;
	spriteWidth = spriteW;
	spriteHeight = spriteH;
}
int Projectile::getSpd() {
	return speed;
}
int Projectile::getIntv() {
	return intv;
}
SDL_Rect Projectile::getBox() {
	return mBox;
}

void Projectile::shootHG(int x, int y, Enemy* enemy) {
	defaultPosX = x; defaultPosY = y;
	if(projectileTicks / intv >= NUM_PROJECTILES)
		projectileTicks = 0;
	if(HGAttacking && projectileTicks % intv == 0 && (projectiles1[projectileTicks/intv].dx == 0 && projectiles1[projectileTicks/intv].dy == 0)) {
		switch(attackDirection) {
			case 0: projectiles1[projectileTicks/intv].dx = 0;
				projectiles1[projectileTicks/intv].dy = -speed; 
				break;
			case 1: projectiles1[projectileTicks/intv].dx = speed;
				projectiles1[projectileTicks/intv].dy = 0; 
				break;
			case 2: projectiles1[projectileTicks/intv].dx = speed;
				projectiles1[projectileTicks/intv].dy = -speed; 
				break;
			case 3: projectiles1[projectileTicks/intv].dx = 0;
				projectiles1[projectileTicks/intv].dy = -speed; 
				break;
			case 4: projectiles1[projectileTicks/intv].dx = -speed;
				projectiles1[projectileTicks/intv].dy = -speed; 
				break;
			case 5: projectiles1[projectileTicks/intv].dx = -speed;
				projectiles1[projectileTicks/intv].dy = 0; 
				break;
		}
		projectiles1[projectileTicks/intv].mBox.w = projectile1.mBox.w;
		projectiles1[projectileTicks/intv].mBox.h = projectile1.mBox.h;
	}
	for(int i = 0; i < NUM_PROJECTILES; i++) {
		if(checkCollision(enemy->getBox(), projectiles1[i].mBox)) {
			enemy->takeDamage();
			projectiles1[i].dx = 0; projectiles1[i].dy = 0;
		}
		if(checkCollision(projectiles1[i].mBox, camera)) {
			projectiles1[i].mBox.x += projectiles1[i].dx;
			projectiles1[i].mBox.y += projectiles1[i].dy;
			if(projectiles1[i].dx > 0) {
				if(projectiles1[i].dy > 0) {
					angle = 135.0;
				} else if(projectiles1[i].dy < 0) {
					angle = 45.0;
				} else if(projectiles1[i].dy == 0) {
					angle = 90.0;
				}
			} else if(projectiles1[i].dx < 0) {
				if(projectiles1[i].dy > 0) {
					angle = -135.0;
				} else if(projectiles1[i].dy < 0) {
					angle = -45.0;
				} else if(projectiles1[i].dy == 0) {
					angle = -90.0;
				}
			} else if(projectiles1[i].dx == 0) {
				if(projectiles1[i].dy > 0) {
					angle = 180.0;
				} else if(projectiles1[i].dy < 0) {
					angle = 0.0;
				} else if(projectiles1[i].dy == 0) {
					angle = 0.0;
				}
			}
		} else {
			projectiles1[i].mBox.x = defaultPosX;
			projectiles1[i].mBox.y = defaultPosY;
			projectiles1[i].dx = 0; projectiles1[i].dy = 0;
		}
		if(projectiles1[i].dx != 0 || projectiles1[i].dy != 0) {
			int renderX = projectiles1[i].mBox.x;
			int renderY = projectiles1[i].mBox.y;
			int angleInt = angle;
			switch(angleInt) {
				case 0: break;
				case 45: renderX += -spriteWidth/2 - 7; break;
				case 90: renderX += -spriteWidth/2 - 10; 
					 renderY += -spriteHeight/2 + 5; break;
				case 135: break;
				case -45: renderX -= -spriteWidth/2 - 7; break;
				case -90: renderX -= -spriteWidth/2 - 10; 
					  renderY += -spriteHeight/2 + 5;break;
				case -135: break;
				case 180: renderX += -spriteWidth/2 - 5;
					  renderY += -spriteHeight/2 + 10;
					  break;
			} 
			gTexture->render(renderX, renderY, NULL, angle);
			//showBox[i] = projectiles1[i].getBox();
		} else {
			projectiles1[i].mBox.x = defaultPosX;
			projectiles1[i].mBox.y = defaultPosY;
		}
	}
	projectileTicks++;
	//SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
	//for(int i = 0; i < NUM_PROJECTILES; i++)
	//	SDL_RenderFillRect(gRenderer, &showBox[i]);
}

void Projectile::moveToXY(double x, double y) {
	if(!shotBullet) {
		double side1 = y - posY;
		double side2 = posX - x;
		double r = sqrt(side1 * side1 + side2 * side2);
		double sinAngle = (side1/r);
		double cosAngle = (side2/r);
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
		shotBullet = 1;
		//printf("%g/%g/%g/%g/%g/%g/%g/%g\n", dx, dy, side1, side2, r, sinAngle, cosAngle, speed);
	}
}

void Projectile::moveAngle(double angle) {
  if(!shotBullet) {
    double sinAngle = std::sin(angle*PI/180.0);
    double cosAngle = std::cos(angle*PI/180.0);

    dx = speed*cosAngle;
    dy = speed*sinAngle;
    shotBullet = 1;
    //printf("%g/%g/%g/%g/%g/%g/%g/%g\n", dx, dy, side1, side2, r, sinAngle, cosAngle, speed);
  }
}

void Projectile::moveGravity(double x, double y, double acc) {
	if(!shotBullet) {
		if(x > 700)
			x -= 300;
		else if(x > 600)
			x -= 200;
		else if(x > 500)
			x -= 100;
		else if(x < 100)
			x += 300;
		else if(x < 200)
			x += 200;
		else if(x < 300)
			x += 100;
		double side1 = y - posY;
		double side2 = posX - x;
		double r = sqrt(side1 * side1 + side2 * side2);
		sinAngle = (side1/r);
		cosAngle = (side2/r);
		shotBullet = 1;
		//printf("%g/%g/%g/%g/%g/%g/%g/%g\n", dx, dy, side1, side2, r, sinAngle, cosAngle, speed);
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
	}
	dy += acc*gravityTicks;
}

void Projectile::shootEnemy0(double x, double y, Chara* hildegarde, int number) {
  defaultPosX = x; defaultPosY = y;
  switch(enemyIDGlobal) {
  case 0: //Conrad
    if(projectileTicks / intv >= number)
      projectileTicks = 0;
    //printf("%i/%i/%g/%g/%b\n", projectileTicks/intv, projectileTicks%intv, projectiles2[projectileTicks/intv].dx, projectiles2[projectileTicks/intv].dy, projectiles2[projectileTicks/intv].shotBullet);
    if(projectileTicks % intv == 0 && (projectiles2[projectileTicks/intv].dx == 0.0 && projectiles2[projectileTicks/intv].dy == 0.0)) {
      projectiles2[projectileTicks/intv].posX = defaultPosX; projectiles2[projectileTicks/intv].posY = defaultPosY;
      projectiles2[projectileTicks/intv].defaultPosX = defaultPosX; projectiles2[projectileTicks/intv].defaultPosY = defaultPosY;
      projectiles2[projectileTicks/intv].mBox.x = posX; projectiles2[projectileTicks/intv].mBox.y = posY;
      projectiles2[projectileTicks/intv].targetX = hildegarde->getX(projectiles2[projectileTicks/intv].posX); projectiles2[projectileTicks/intv].targetY = hildegarde->getY(projectiles2[projectileTicks/intv].posY);
      projectiles2[projectileTicks/intv].speed = speed;
      projectiles2[projectileTicks/intv].mBox.w = mBox.w;
      projectiles2[projectileTicks/intv].mBox.h = mBox.h;
      projectiles2[projectileTicks/intv].moveToXY(projectiles2[projectileTicks/intv].targetX, projectiles2[projectileTicks/intv].targetY);
    }
    for(int i = 0; i < number; i++) {
      if(checkCollision(projectiles2[number-1].mBox, camera)) {
	projectiles2[i].posX += projectiles2[i].dx;
	projectiles2[i].posY += projectiles2[i].dy;
	projectiles2[i].mBox.x = projectiles2[i].posX;
	projectiles2[i].mBox.y = projectiles2[i].posY;
      } else {
	projectiles2[i].posX = defaultPosX;
	projectiles2[i].posY = defaultPosY;
	projectiles2[i].mBox.x = projectiles2[i].posX;
	projectiles2[i].mBox.y = projectiles2[i].posY;
	projectiles2[i].dx = 0.0; projectiles2[i].dy = 0.0;
	projectiles2[i].shotBullet = 0;
      }
      if(projectiles2[i].dx != 0.0 || projectiles2[i].dy != 0.0) {
	gTexture->render(projectiles2[i].mBox.x - projectiles2[i].mBox.w/3, projectiles2[i].mBox.y - projectiles2[i].mBox.h/3, NULL);
	//	showBox[i] = projectiles2[i].getBox();
      } 
      //printf("%i/%i/%b/%i/%i/%i/%i\n", projectiles2[i].dx, projectiles2[i].dy, checkCollision(projectiles2[i].mBox, camera), hildegarde->getBox().x, hildegarde->getBox().y, projectiles2[i].targetX, projectiles2[i].targetY);
    }
    projectileTicks++;
    //SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
    //	for(int i = 0; i < NUM_PROJECTILES; i++)
    //	SDL_RenderFillRect(gRenderer, &showBox[i]);
    break;
  case 1:  //Saucer enemy ID
    if(difficulty == 0)
      actualIntv = 2;
    else if(difficulty == 1)
      actualIntv = 2;
    else if(difficulty == 2)
      actualIntv = 2;
    if(projectilesShot >= NUM_PROJECTILES) {
      projectileTicks = 0; projectilesShot = 0;
    }
    // Shoots batches of bullets according to intv., bullets are tracked
    // using projectilesShot variable
    if(projectileTicks % actualIntv == 0) {
      for(int i = 0; i < 9; i++) {
	projectiles2[projectilesShot+i].posX = defaultPosX;
	projectiles2[projectilesShot+i].posY = defaultPosY;
	projectiles2[projectilesShot+i].mBox = mBox;
	projectiles2[projectilesShot+i].mBox.x = projectiles2[projectilesShot+i].posX;
	projectiles2[projectilesShot+i].mBox.y = projectiles2[projectilesShot+i].posY;
	projectiles2[projectilesShot+i].speed = 10.0;
	if(!(projectileAngle >= 360.0)) {
	  projectileAngle += 9.0;
	} else {
	  projectileAngle = 0.0;
	}
	projectiles2[projectilesShot+i].moveAngle(projectileAngle);
	projectilesShot++;
      }
    }
    for(int i = 0; i < NUM_PROJECTILES; i++) {
      //printf("%b", checkCollision(projectiles2[i].mBox, camera));
      if(checkCollision(projectiles2[i].mBox, camera)) {
	projectiles2[i].posX += projectiles2[i].dx;
	projectiles2[i].posY += projectiles2[i].dy;
	projectiles2[i].mBox.x = projectiles2[i].posX;
	projectiles2[i].mBox.y = projectiles2[i].posY;
      } else {
	projectiles2[i].posX = defaultPosX;
	projectiles2[i].posY = defaultPosY;
	projectiles2[i].mBox.x = projectiles2[i].posX;
	projectiles2[i].mBox.y = projectiles2[i].posY;
	projectiles2[i].dx = 0.0; projectiles2[i].dy = 0.0;
	projectiles2[i].shotBullet = 0; projectiles2[i].dx = 0;
	projectiles2[i].dy = 0;
      }
      if(projectiles2[i].dx != 0.0 || projectiles2[i].dy != 0.0) {
	gTexture->render(projectiles2[i].mBox.x - projectiles2[i].mBox.w/3, projectiles2[i].mBox.y - projectiles2[i].mBox.h/3, NULL, angle);
	projectiles2[i].checkDiePlus(hildegarde);
      }
    }
    projectileTicks++;
    break;
  }
}

void Projectile::shootEnemy1(double x, double y, Chara* hildegarde) {
  defaultPosX = x; defaultPosY = y;
  switch(enemyIDGlobal) {
  case 0: // Conrad ID
    if(difficulty == 0)
      actualIntv = intv;
    else if(difficulty == 1)
      actualIntv = intv-2;
    else if(difficulty == 2)
      actualIntv = intv-4;
    if(projectileTicks / actualIntv >= NUM_PROJECTILES)
      projectileTicks = 0;
    //printf("%i/%i/%g/%g/%b\n", projectileTicks/actualIntv, projectileTicks%actualIntv, projectiles2[projectileTicks/actualIntv].dx, projectiles2[projectileTicks/actualIntv]!.dy, projectiles2[projectileTicks/actualIntv].shotBullet);
    if(projectileTicks % actualIntv == 0 && (projectiles2[projectileTicks/actualIntv].dx == 0.0 && projectiles2[projectileTicks/actualIntv].dy == 0.0)) {
      projectiles2[projectileTicks/actualIntv].posX = defaultPosX; projectiles2[projectileTicks/actualIntv].posY = defaultPosY;
      projectiles2[projectileTicks/actualIntv].defaultPosX = defaultPosX; projectiles2[projectileTicks/actualIntv].defaultPosY = defaultPosY;
      projectiles2[projectileTicks/actualIntv].mBox.x = posX; projectiles2[projectileTicks/actualIntv].mBox.y = posY;
      projectiles2[projectileTicks/actualIntv].targetX = hildegarde->getX(projectiles2[projectileTicks/actualIntv].posX); projectiles2[projectileTicks/actualIntv].targetY = hildegarde->getY(projectiles2[projectileTicks/actualIntv].posY);
      projectiles2[projectileTicks/actualIntv].speed = speed;
      projectiles2[projectileTicks/actualIntv].mBox.w = mBox.w;
      projectiles2[projectileTicks/actualIntv].mBox.h = mBox.h;
      projectiles2[projectileTicks/actualIntv].moveToXY(projectiles2[projectileTicks/actualIntv].targetX, projectiles2[projectileTicks/actualIntv].targetY);
    }
    for(int i = 0; i < NUM_PROJECTILES; i++) {
      if(checkCollision(projectiles2[i].mBox, camera)) {
	projectiles2[i].posX += projectiles2[i].dx;
	projectiles2[i].posY += projectiles2[i].dy;
	projectiles2[i].mBox.x = projectiles2[i].posX;
	projectiles2[i].mBox.y = projectiles2[i].posY;
      } else {
	projectiles2[i].posX = defaultPosX;
	projectiles2[i].posY = defaultPosY;
	projectiles2[i].mBox.x = projectiles2[i].posX;
	projectiles2[i].mBox.y = projectiles2[i].posY;
	projectiles2[i].dx = 0.0; projectiles2[i].dy = 0.0;
	projectiles2[i].shotBullet = 0;
      }
      if(projectiles2[i].dx != 0.0 || projectiles2[i].dy != 0.0) {
	gTexture->render(projectiles2[i].mBox.x - projectiles2[i].mBox.w/3, projectiles2[i].mBox.y - projectiles2[i].mBox.h/3, NULL);
	//	showBox[i] = projectiles2[i].getBox();
      } 
      //printf("%i/%i/%b/%i/%i/%i/%i\n", projectiles2[i].dx, projectiles2[i].dy, checkCollision(projectiles2[i].mBox, camera), hildegarde->getBox().x, hildegarde->getBox().y, projectiles2[i].targetX, projectiles2[i].targetY);
    }
    projectileTicks++;
    //SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
    //	for(int i = 0; i < NUM_PROJECTILES; i++)
    //	SDL_RenderFillRect(gRenderer, &showBox[i]);
    break;
  case 1: //Saucer enemy ID
    if(difficulty == 0)
      actualIntv = 1;
    else if(difficulty == 1)
      actualIntv = 2;
    else if(difficulty == 2)
      actualIntv = 2;
    if(projectilesShot >= NUM_PROJECTILES) {
      projectileTicks = 0; projectilesShot = 0;
    }
    // Shoots batches of bullets according to intv., bullets are tracked
    // using projectilesShot variable
    if(projectileTicks % actualIntv == 0) {
      for(int i = 0; i < 9; i++) {
	projectiles2[projectilesShot+i].posX = defaultPosX;
	projectiles2[projectilesShot+i].posY = defaultPosY;
	projectiles2[projectilesShot+i].mBox = mBox;
	projectiles2[projectilesShot+i].mBox.x = projectiles2[projectilesShot+i].posX;
	projectiles2[projectilesShot+i].mBox.y = projectiles2[projectilesShot+i].posY;
	projectiles2[projectilesShot+i].speed = 10.0;
	if(!(projectileAngle >= 360.0)) {
	  projectileAngle += 9.0;
	} else {
	  projectileAngle = 0.0;
	}
	projectiles2[projectilesShot+i].moveAngle(projectileAngle);
	projectilesShot++;
      }
    }
    for(int i = 0; i < NUM_PROJECTILES; i++) {
      //printf("%b", checkCollision(projectiles2[i].mBox, camera));
      if(checkCollision(projectiles2[i].mBox, camera)) {
	projectiles2[i].posX += projectiles2[i].dx;
	projectiles2[i].posY += projectiles2[i].dy;
	projectiles2[i].mBox.x = projectiles2[i].posX;
	projectiles2[i].mBox.y = projectiles2[i].posY;
      } else {
	projectiles2[i].posX = defaultPosX;
	projectiles2[i].posY = defaultPosY;
	projectiles2[i].mBox.x = projectiles2[i].posX;
	projectiles2[i].mBox.y = projectiles2[i].posY;
	projectiles2[i].dx = 0.0; projectiles2[i].dy = 0.0;
	projectiles2[i].shotBullet = 0; projectiles2[i].dx = 0;
	projectiles2[i].dy = 0;
      }
      if(projectiles2[i].dx != 0.0 || projectiles2[i].dy != 0.0) {
	gTexture->render(projectiles2[i].mBox.x - projectiles2[i].mBox.w/3, projectiles2[i].mBox.y - projectiles2[i].mBox.h/3, NULL, angle);
	projectiles2[i].checkDiePlus(hildegarde);
      }
    }
    projectileTicks++;
    break;
  }
}

void Projectile::shootEnemy2(double x, double y, Chara* hildegarde) {
	projectile5.shootEnemy0(x, y, hildegarde, 5);
	if(difficulty == 0)
		actualIntv = intv;
	else if(difficulty == 1)
		actualIntv = intv-3;
	else if(difficulty == 2)
		actualIntv = intv-6;
	defaultPosX = x; defaultPosY = y;
	if(projectileTicks / actualIntv >= NUM_PROJECTILES)
		projectileTicks = 0;
	//printf("%i/%i/%g/%g/%b\n", projectileTicks/actualIntv, projectileTicks%actualIntv, projectiles3[projectileTicks/actualIntv].dx, projectiles3[projectileTicks/actualIntv].dy, projectiles3[projectileTicks/actualIntv].shotBullet);
	if(!shootReturn) {
		shootTicks +=20; 
		if(shootTicks >= SCREEN_WIDTH)
			shootReturn = 1;
	} else {
		shootTicks -=20;
		if(shootTicks <= 0)
			shootReturn = 0;
	}
	if(projectileTicks % actualIntv == 0 && (projectiles3[projectileTicks/actualIntv].dx == 0.0 && projectiles3[projectileTicks/actualIntv].dy == 0.0)) {
		projectiles3[projectileTicks/actualIntv].posX = defaultPosX; projectiles3[projectileTicks/actualIntv].posY = defaultPosY;
		projectiles3[projectileTicks/actualIntv].defaultPosX = defaultPosX; projectiles3[projectileTicks/actualIntv].defaultPosY = defaultPosY;
		projectiles3[projectileTicks/actualIntv].mBox.x = posX; projectiles3[projectileTicks/actualIntv].mBox.y = posY;
		projectiles3[projectileTicks/actualIntv].targetX = shootTicks; projectiles3[projectileTicks/actualIntv].targetY = hildegarde->getY(projectiles3[projectileTicks/actualIntv].posY);
		projectiles3[projectileTicks/actualIntv].speed = speed;
		projectiles3[projectileTicks/actualIntv].mBox.w = mBox.w;
		projectiles3[projectileTicks/actualIntv].mBox.h = mBox.h;
		projectiles3[projectileTicks/actualIntv].moveToXY(projectiles3[projectileTicks/actualIntv].targetX, projectiles3[projectileTicks/actualIntv].targetY);
	}
	for(int i = 0; i < NUM_PROJECTILES; i++) {
		if(checkCollision(projectiles3[i].mBox, camera)) {
			projectiles3[i].posX += projectiles3[i].dx;
			projectiles3[i].posY += projectiles3[i].dy;
			projectiles3[i].mBox.x = projectiles3[i].posX;
			projectiles3[i].mBox.y = projectiles3[i].posY;
		} else {
			projectiles3[i].posX = defaultPosX;
			projectiles3[i].posY = defaultPosY;
			projectiles3[i].mBox.x = projectiles3[i].posX;
			projectiles3[i].mBox.y = projectiles3[i].posY;
			projectiles3[i].dx = 0.0; projectiles3[i].dy = 0.0;
			projectiles3[i].shotBullet = 0;
		}
		if(projectiles3[i].dx != 0.0 || projectiles3[i].dy != 0.0) {
			gTexture->render(projectiles3[i].mBox.x - projectiles3[i].mBox.w/3, projectiles3[i].mBox.y - projectiles3[i].mBox.h/3, NULL, angle);
	//		showBox[i] = projectiles3[i].getBox();
		} 
		//printf("%i/%i/%b/%i/%i/%i/%i\n", projectiles3[i].dx, projectiles3[i].dy, checkCollision(projectiles3[i].mBox, camera), hildegarde->getBox().x, hildegarde->getBox().y, projectiles3[i].targetX, projectiles3[i].targetY);
	}
	projectileTicks++;
	//SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
//	for(int i = 0; i < NUM_PROJECTILES; i++)
	//	SDL_RenderFillRect(gRenderer, &showBox[i]);
}

void Projectile::shootEnemy3(double x, double y, Chara* hildegarde) {
  defaultPosX = x; defaultPosY = y;
  switch(enemyIDGlobal) {
  case 0:
    if(difficulty == 0)
      actualIntv = intv;
    else if(difficulty == 1)
      actualIntv = intv-2;
    else if(difficulty == 2)
      actualIntv = intv-4;
    if(projectileTicks / actualIntv >= NUM_PROJECTILES)
      projectileTicks = 0;
    //printf("%i/%i/%g/%g/%b\n", projectileTicks/actualIntv, projectileTicks%actualIntv, projectiles2[projectileTicks/actualIntv].dx, projectiles2[projectileTicks/actualIntv].dy, projectiles2[projectileTicks/actualIntv].shotBullet);
    gravityTicks++;

    if(projectileTicks % actualIntv == 0 && (projectiles2[projectileTicks/actualIntv].dx == 0.0 && projectiles2[projectileTicks/actualIntv].dy == 0.0)) {
      projectiles2[projectileTicks/actualIntv].posX = defaultPosX; projectiles2[projectileTicks/actualIntv].posY = defaultPosY;
      projectiles2[projectileTicks/actualIntv].defaultPosX = defaultPosX; projectiles2[projectileTicks/actualIntv].defaultPosY = defaultPosY;
      projectiles2[projectileTicks/actualIntv].mBox.x = posX; projectiles2[projectileTicks/actualIntv].mBox.y = posY;
      projectiles2[projectileTicks/actualIntv].targetX = rand()%SCREEN_WIDTH; projectiles2[projectileTicks/actualIntv].targetY = rand()%(SCREEN_HEIGHT/4);
      projectiles2[projectileTicks/actualIntv].speed = speed;
      projectiles2[projectileTicks/actualIntv].mBox.w = mBox.w;
      projectiles2[projectileTicks/actualIntv].mBox.h = mBox.h;
      //projectiles2[projectileTicks/actualIntv].moveToXY(projectiles2[projectileTicks/actualIntv].targetX, projectiles2[projectileTicks/actualIntv].targetY);
      //printf("%i/%i\n", projectiles2[projectileTicks/actualIntv].targetX, projectiles2[projectileTicks/actualIntv].targetY);
      projectiles2[projectileTicks/actualIntv].moveGravityBullet = 1;
    }
    for(int i = 0; i < NUM_PROJECTILES; i++) {
      if(checkCollision(projectiles2[i].mBox, camera)) {
	if(projectiles2[i].moveGravityBullet)
	  projectiles2[i].moveGravity(projectiles2[i].targetX, projectiles2[i].targetY, 0.1);
	projectiles2[i].posX += projectiles2[i].dx;
	projectiles2[i].posY += projectiles2[i].dy;
	projectiles2[i].mBox.x = projectiles2[i].posX;
	projectiles2[i].mBox.y = projectiles2[i].posY;
      } else {
	projectiles2[i].posX = defaultPosX;
	projectiles2[i].posY = defaultPosY;
	projectiles2[i].mBox.x = projectiles2[i].posX;
	projectiles2[i].mBox.y = projectiles2[i].posY;
	projectiles2[i].dx = 0.0; projectiles2[i].dy = 0.0;
	projectiles2[i].shotBullet = 0; projectiles2[i].moveGravityBullet = 0;
      }
      if(projectiles2[i].dx != 0.0 || projectiles2[i].dy != 0.0) {
	gTexture->render(projectiles2[i].mBox.x - projectiles2[i].mBox.w/3, projectiles2[i].mBox.y - projectiles2[i].mBox.h/3, NULL, angle);
	//		showBox[i] = projectiles2[i].getBox();
      } 
      //printf("%i/%i/%b/%i/%i/%i/%i\n", projectiles2[i].targetX, projectiles2[i].targetY);
    }
    projectileTicks++;
    //SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
    //	for(int i = 0; i < NUM_PROJECTILES; i++)
    //	SDL_RenderFillRect(gRenderer, &showBox[i]);
    break;
  case 1: //Saucer enemy ID
    if(difficulty == 0)
      actualIntv = 8;
    else if(difficulty == 1)
      actualIntv = 4;
    else if(difficulty == 2)
      actualIntv = 2;
    if(projectileTicks / actualIntv >= NUM_PROJECTILES)
      projectileTicks = 0;
    //printf("%i/%i/%g/%g/%b\n", projectileTicks/actualIntv, projectileTicks%actualIntv, projectiles2[projectileTicks/actualIntv].dx, projectiles2[projectileTicks/actualIntv].dy, projectiles2[projectileTicks/actualIntv].shotBullet);
    gravityTicks++;

    if(projectileTicks % actualIntv == 0 && (projectiles2[projectileTicks/actualIntv].dx == 0.0 && projectiles2[projectileTicks/actualIntv].dy == 0.0)) {
      projectiles2[projectileTicks/actualIntv].posX = defaultPosX; projectiles2[projectileTicks/actualIntv].posY = defaultPosY;
      projectiles2[projectileTicks/actualIntv].defaultPosX = defaultPosX; projectiles2[projectileTicks/actualIntv].defaultPosY = defaultPosY;
      projectiles2[projectileTicks/actualIntv].mBox.x = posX; projectiles2[projectileTicks/actualIntv].mBox.y = posY;
      projectiles2[projectileTicks/actualIntv].targetX = rand()%SCREEN_WIDTH; projectiles2[projectileTicks/actualIntv].targetY = SCREEN_HEIGHT;
      projectiles2[projectileTicks/actualIntv].speed = speed;
      projectiles2[projectileTicks/actualIntv].mBox.w = mBox.w;
      projectiles2[projectileTicks/actualIntv].mBox.h = mBox.h;
      //projectiles2[projectileTicks/actualIntv].moveToXY(projectiles2[projectileTicks/actualIntv].targetX, projectiles2[projectileTicks/actualIntv].targetY);
      //printf("%i/%i\n", projectiles2[projectileTicks/actualIntv].targetX, projectiles2[projectileTicks/actualIntv].targetY);
      projectiles2[projectileTicks/actualIntv].moveGravityBullet = 1;
    }
    for(int i = 0; i < NUM_PROJECTILES; i++) {
      if(checkCollision(projectiles2[i].mBox, camera)) {
	if(projectiles2[i].moveGravityBullet)
	  projectiles2[i].moveGravity(projectiles2[i].targetX, projectiles2[i].targetY, 0.1);
	projectiles2[i].posX += 1;
	projectiles2[i].posY += projectiles2[i].dy - 1;
	projectiles2[i].mBox.x = projectiles2[i].posX;
	projectiles2[i].mBox.y = projectiles2[i].posY;
      } else {
	projectiles2[i].posX = defaultPosX;
	projectiles2[i].posY = defaultPosY;
	projectiles2[i].mBox.x = projectiles2[i].posX;
	projectiles2[i].mBox.y = projectiles2[i].posY;
	projectiles2[i].dx = 0.0; projectiles2[i].dy = 0.0;
	projectiles2[i].shotBullet = 0; projectiles2[i].moveGravityBullet = 0;
      }
      if(projectiles2[i].dx != 0.0 || projectiles2[i].dy != 0.0) {
	gTexture->render(projectiles2[i].mBox.x - projectiles2[i].mBox.w/3, projectiles2[i].mBox.y - projectiles2[i].mBox.h/3, NULL, angle);
	//		showBox[i] = projectiles2[i].getBox();
	projectiles2[i].checkDiePlus(hildegarde);
      } 
      //printf("%i/%i/%b/%i/%i/%i/%i\n", projectiles2[i].targetX, projectiles2[i].targetY);
    }
    projectileTicks++;
    //SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
    //	for(int i = 0; i < NUM_PROJECTILES; i++)
    //	SDL_RenderFillRect(gRenderer, &showBox[i]);
    break;
  }
}

void Projectile::shootEnemy4(double x, double y, Chara* hildegarde) {
  defaultPosX = x; defaultPosY = y;
  switch(enemyIDGlobal) {
  case 0:
	 if(!rolledShootAttack4Rand) {
	   shootAttack4Rand = rand()%2;
	   rolledShootAttack4Rand = 1;
	 }
	 if(shootLaser) {
	   if(difficulty == 1)
	     projectile5.shootEnemy0(x, y, hildegarde, 5);
	   else if(difficulty == 2)
	     projectile5.shootEnemy0(x, y, hildegarde, 10);
	   if(!shootReturn) {
	     shootTicks += 5; 
	     if(shootTicks >= SCREEN_WIDTH)
	       shootReturn = 1;
	   } else {
	     shootTicks -= 5;
	     if(shootTicks <= 0)
	       shootReturn = 0;
	   }
	 }
	 if(initialiseLaser) {
	   projectiles3[0].posX = defaultPosX; projectiles3[0].posY = defaultPosY;
	   projectiles3[0].defaultPosX = defaultPosX; projectiles3[0].defaultPosY = defaultPosY;
	   projectiles3[0].mBox.x = posX; projectiles3[0].mBox.y = posY;
	   projectiles3[0].speed = speed;
	   projectiles3[0].mBox.w = mBox.w;
	   projectiles3[0].mBox.h = mBox.h;
	   for(int i = 0; i < NUM_PROJECTILES; i++) {
	     laserBoxes[i].w = mBox.w;
	     laserBoxes[i].h = mBox.h;
	   }
	   initialiseLaser = 0; shootLaser = 1;
	 } else if(shootStimulant) {
	   stimulantTicks++;
	   gravityTicks++;
	   if(initialiseStimulant) {
	     for(int i = 0; i < 3; i++) {
	       projectiles3[i].posX = defaultPosX; projectiles3[i].posY = defaultPosY;
	       projectiles3[i].defaultPosX = defaultPosX; projectiles3[i].defaultPosY = defaultPosY;
	       projectiles3[i].mBox.x = posX; projectiles3[i].mBox.y = posY;
	       projectiles3[i].speed = speed;
	       projectiles3[i].mBox.w = mBox.w;
	       projectiles3[i].mBox.h = mBox.h;
	       if(shootAttack4Rand == 0) {
		 projectiles3[i].targetX = SCREEN_WIDTH/2 - 100; 
		 projectiles3[i].targetY = SCREEN_HEIGHT/6;
	       } else {
		 projectiles3[i].targetX = SCREEN_WIDTH/2 + 100; 
		 projectiles3[i].targetY = SCREEN_HEIGHT/6;
	       }
	     }
	     initialiseStimulant = 0; 
	   }
	   if(checkCollision(projectiles3[2].mBox, camera)) {
	     for(int i = 0; i < 3; i++) {
	       if(projectiles3[i].dx == 0.0 && projectiles3[i].dy == 0.0) {
		 projectiles3[i].posX = defaultPosX; projectiles3[i].posY = defaultPosY;
	       }
	     }
	     projectiles3[0].moveGravity(projectiles3[0].targetX, projectiles3[0].targetY, 0.1);
	     projectiles3[0].posX += projectiles3[0].dx;
	     projectiles3[0].posY += projectiles3[0].dy;
	     projectiles3[0].mBox.x = projectiles3[0].posX;
	     projectiles3[0].mBox.y = projectiles3[0].posY;
	     if(stimulantTicks >= 30) {
	       projectiles3[1].moveGravity(projectiles3[1].targetX, projectiles3[1].targetY, 0.1);
	       projectiles3[1].posX += projectiles3[1].dx;
	       projectiles3[1].posY += projectiles3[1].dy;
	       projectiles3[1].mBox.x = projectiles3[1].posX;
	       projectiles3[1].mBox.y = projectiles3[1].posY;
	     }
	     if(stimulantTicks >= 60) {
	       projectiles3[2].moveGravity(projectiles3[2].targetX, projectiles3[2].targetY, 0.1);
	       projectiles3[2].posX += projectiles3[2].dx;
	       projectiles3[2].posY += projectiles3[2].dy;
	       projectiles3[2].mBox.x = projectiles3[2].posX;
	       projectiles3[2].mBox.y = projectiles3[2].posY;
	     }
	     for(int i = 0; i < 2; i++) {
	       if(checkCollision(projectiles3[i].mBox, hildegarde->getBox()))
		 hildegarde->death = 1;
	     }
	   } else {
	     for(int i = 0; i < 3; i++) {
	       projectiles3[i].posX = defaultPosX;
	       projectiles3[i].posY = defaultPosY;
	       projectiles3[i].mBox.x = projectiles3[i].posX;
	       projectiles3[i].mBox.y = projectiles3[i].posY;
	       projectiles3[i].dx = 0.0; projectiles3[i].dy = 0.0;
	     }
	     initialiseLaser = 1; 
	     shootStimulant = 0; gravityTicks = 0;
	   }
			
	 }
	 if(shootLaser) {
	   if(checkCollision(projectiles3[0].mBox, camera)) {
	     if(shootAttack4Rand == 0)
	       projectiles3[0].targetX = shootTicks + 100;
	     else
	       projectiles3[0].targetX = SCREEN_WIDTH - shootTicks - 100;
	     projectiles3[0].targetY = SCREEN_HEIGHT;
	     projectiles3[0].shotBullet = 0;
	     projectiles3[0].moveToXY(projectiles3[0].targetX, projectiles3[0].targetY);
	     int j;
	     for(int i = 0; i < 120; i++) {
	       projectiles3[0].posX += projectiles3[0].dx;
	       projectiles3[0].posY += projectiles3[0].dy;
	       projectiles3[0].mBox.x = projectiles3[0].posX;
	       projectiles3[0].mBox.y = projectiles3[0].posY;
	       laserBoxes[i].x = projectiles3[0].mBox.x;
	       laserBoxes[i].y = projectiles3[0].mBox.y;
	       if(checkCollision(laserBoxes[i], hildegarde->getBox()))
		 hildegarde->death = 1;
	     }
	   } else {
	     projectiles3[0].posX = defaultPosX;
	     projectiles3[0].posY = defaultPosY;
	     projectiles3[0].mBox.x = projectiles3[0].posX;
	     projectiles3[0].mBox.y = projectiles3[0].posY;
	     projectiles3[0].dx = 0.0; projectiles3[0].dy = 0.0;
	     projectiles3[0].shotBullet = 0;
	   }
	   SDL_SetRenderDrawColor(gRenderer, 255, 50, 0, 255);
	   for(int i = 0; i < 120; i++)
	     SDL_RenderFillRect(gRenderer, &laserBoxes[i]);
	 }
	 for(int i = 0; i < 3; i++) {
	   if((projectiles3[i].dx != 0.0 || projectiles3[i].dy != 0.0) && shootStimulant) {
	     gTexture->render(projectiles3[i].mBox.x - projectiles3[i].mBox.w/3, projectiles3[i].mBox.y - projectiles3[i].mBox.h/3, NULL);
	   } 
	 }
	 //printf("%i/%i/%b/%i/%i/%i/%i\n", projectiles3[i].dx, projectiles3[i].dy, checkCollision(projectiles3[i].mBox, camera), hildegarde->getBox().x, hildegarde->getBox().y, projectiles3[i].targetX, projectiles3[i].targetY);
	 projectileTicks++;
	 //printf("%i/%i/%i\n", shootAttack4Rand, projectiles3[0].targetX, shootTicks);
	 break;
  case 1: saucerProjectiles[0].mBox.x = x;
    saucerProjectiles[0].mBox.y = y;
    if(projectileTicks > 60) {
	   if(projectileTicks >= 70) {
	     projectileTicks = 0;
	   }
	   defaultPosX = x; defaultPosY = y;
	   if(checkCollision(saucerProjectiles[0].mBox, camera)) {
	     saucerProjectiles[0].mBox.w = mBox.w;
	     saucerProjectiles[0].mBox.h = mBox.h;
	     saucerProjectiles[0].targetX = defaultPosX;
	     saucerProjectiles[0].targetY = SCREEN_HEIGHT;
	     saucerProjectiles[0].shotBullet = 0;
	     saucerProjectiles[0].moveToXY(saucerProjectiles[0].targetX, saucerProjectiles[0].targetY);
	     for(int i = 1; i < 120; i++) {
	       saucerProjectiles[0].mBox.x += 0;
	       saucerProjectiles[0].mBox.y += 23;
	       saucerProjectiles[i].mBox = saucerProjectiles[0].mBox;
	     }
	   } else {
	     saucerProjectiles[0].mBox.x = x;
	     saucerProjectiles[0].mBox.y = y;
	     saucerProjectiles[0].dx = 0.0; saucerProjectiles[0].dy = 0.0;
	     saucerProjectiles[0].shotBullet = 0;
	   }
	   //SDL_SetRenderDrawColor(gRenderer, 255, 50, 0, 255);
	   for(int i = 1; i < 120; i++) {
	     gTexture->render(saucerProjectiles[i].mBox.x - mBox.w/2, saucerProjectiles[i].mBox.y, NULL, angle);
	     //SDL_RenderFillRect(gRenderer, &saucerProjectiles[i].mBox);
	     if(checkCollision(saucerProjectiles[i].mBox, hildegarde->getBox()))
	       hildegarde->death = 1;
	     saucerProjectiles[i].mBox.x = x;
	     saucerProjectiles[i].mBox.y = y;
	     //printf("%i, %i, %i, %i\n", saucerProjectiles[i].mBox.x, saucerProjectiles[i].mBox.y, saucerProjectiles[i].mBox.w, saucerProjectiles[i].mBox.h);
	   }
	 }
    projectileTicks++;
    break;
  }
}

void Projectile::checkDiePlus(Chara* hildegarde) {
    if(checkCollision(hildegarde->getBox(), mBox))
      hildegarde->death = 1;
}

void Projectile::checkDie(Chara* hildegarde) {
  for(int i = 0; i < NUM_PROJECTILES; i++) {
    if(checkCollision(hildegarde->getBox(), projectiles2[i].mBox)) {
      hildegarde->death = 1;
    }
  }
}

void Projectile::checkDie1(Chara* hildegarde) {
  for(int i = 0; i < NUM_PROJECTILES; i++) {
    if(checkCollision(hildegarde->getBox(), projectiles3[i].mBox)) {
      hildegarde->death = 1;
    }
  }
}

void Projectile::clearProjectilesPlus() {
  for(int i = 0; i < NUM_PROJECTILES; i++) {
    posX = defaultPosX;
    posY = defaultPosY;
    mBox.x = posX;
    mBox.y = posY;
    dx = 0.0; dy = 0.0;
    shotBullet = 0;
    moveGravityBullet = 0;
  }
  shootTicks = 0; shootReturn = 0;
  gravityTicks = 1; initialiseLaser = 0;
  shootLaser = 0; initialiseStimulant = 1;
  shootStimulant = 1; rolledShootAttack4Rand = 0;
  stimulantTicks = 0; projectileAngle = 0;
}

void Projectile::clearProjectiles() {
  for(int i = 0; i < NUM_PROJECTILES; i++) {
    projectiles2[i].posX = projectiles2[i].defaultPosX;
    projectiles2[i].posY = projectiles2[i].defaultPosY;
    projectiles2[i].mBox.x = projectiles2[i].posX;
    projectiles2[i].mBox.y = projectiles2[i].posY;
    projectiles2[i].dx = 0.0; projectiles2[i].dy = 0.0;
    projectiles2[i].shotBullet = 0;
    projectiles2[i].moveGravityBullet = 0;
  }
  shootTicks = 0; shootReturn = 0;
  gravityTicks = 1; initialiseLaser = 0;
  shootLaser = 0; initialiseStimulant = 1;
  shootStimulant = 1; rolledShootAttack4Rand = 0;
  stimulantTicks = 0;
}

void Projectile::clearProjectiles1() {
  for(int i = 0; i < NUM_PROJECTILES; i++) {
    projectiles3[i].posX = projectiles3[i].defaultPosX;
    projectiles3[i].posY = projectiles3[i].defaultPosY;
    projectiles3[i].mBox.x = projectiles3[i].posX;
    projectiles3[i].mBox.y = projectiles3[i].posY;
    projectiles3[i].dx = 0.0; projectiles3[i].dy = 0.0;
    projectiles3[i].shotBullet = 0;
    projectiles3[i].moveGravityBullet = 0;
  }
  }

void Projectile::clearProjectilesHG() {
  for(int i = 0; i < NUM_PROJECTILES; i++) {
    projectiles1[i].posX = projectiles1[i].defaultPosX;
    projectiles1[i].posY = projectiles1[i].defaultPosY;
    projectiles1[i].mBox.x = projectiles1[i].posX;
    projectiles1[i].mBox.y = projectiles1[i].posY;
    projectiles1[i].dx = 0.0; projectiles1[i].dy = 0.0;
    projectiles1[i].shotBullet = 0;
    projectiles1[i].moveGravityBullet = 0;
  }
}
