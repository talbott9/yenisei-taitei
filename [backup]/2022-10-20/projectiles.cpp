#include "projectiles.h"
#include <cmath>

SDL_Rect showBox[NUM_PROJECTILES];

Projectile::Projectile() {
	mBox.x = 0.0; mBox.y = 0.0;
	posX = 333.3; posY = 201.8;
	activeProjectiles = 0;
	projectile1.setVariables(9, 9, 6.0, 5, &gHGArrow1Texture, 0, 9, 32);
	projectile2.setVariables(5, 5, 7.0, 30, &gBullet2, 0, 10, 10);
	projectile3.setVariables(15, 15, 6.0, 10, &gBullet1, 0, 25, 25);
	projectile4.setVariables(5, 5, 7.0, 5, &gBullet2);
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

void Projectile::shootHG(int x, int y) {
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

void Projectile::shootEnemy1(double x, double y, Chara* hildegarde) {
	defaultPosX = x; defaultPosY = y;
	if(projectileTicks / intv >= NUM_PROJECTILES)
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
}

void Projectile::shootEnemy2(double x, double y, Chara* hildegarde) {
	defaultPosX = x; defaultPosY = y;
	if(projectileTicks / intv >= NUM_PROJECTILES)
		projectileTicks = 0;
	//printf("%i/%i/%g/%g/%b\n", projectileTicks/intv, projectileTicks%intv, projectiles2[projectileTicks/intv].dx, projectiles2[projectileTicks/intv].dy, projectiles2[projectileTicks/intv].shotBullet);
	if(!shootReturn) {
		shootTicks +=20; 
		if(shootTicks >= SCREEN_WIDTH)
			shootReturn = 1;
	} else {
		shootTicks -=20;
		if(shootTicks <= 0)
			shootReturn = 0;
	}
	if(projectileTicks % intv == 0 && (projectiles2[projectileTicks/intv].dx == 0.0 && projectiles2[projectileTicks/intv].dy == 0.0)) {
		projectiles2[projectileTicks/intv].posX = defaultPosX; projectiles2[projectileTicks/intv].posY = defaultPosY;
		projectiles2[projectileTicks/intv].defaultPosX = defaultPosX; projectiles2[projectileTicks/intv].defaultPosY = defaultPosY;
		projectiles2[projectileTicks/intv].mBox.x = posX; projectiles2[projectileTicks/intv].mBox.y = posY;
		projectiles2[projectileTicks/intv].targetX = shootTicks; projectiles2[projectileTicks/intv].targetY = hildegarde->getY(projectiles2[projectileTicks/intv].posY);
		projectiles2[projectileTicks/intv].speed = speed;
		projectiles2[projectileTicks/intv].mBox.w = mBox.w;
		projectiles2[projectileTicks/intv].mBox.h = mBox.h;
		projectiles2[projectileTicks/intv].moveToXY(projectiles2[projectileTicks/intv].targetX, projectiles2[projectileTicks/intv].targetY);
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
			gTexture->render(projectiles2[i].mBox.x - projectiles2[i].mBox.w/3, projectiles2[i].mBox.y - projectiles2[i].mBox.h/3, NULL, angle);
	//		showBox[i] = projectiles2[i].getBox();
		} 
		//printf("%i/%i/%b/%i/%i/%i/%i\n", projectiles2[i].dx, projectiles2[i].dy, checkCollision(projectiles2[i].mBox, camera), hildegarde->getBox().x, hildegarde->getBox().y, projectiles2[i].targetX, projectiles2[i].targetY);
	}
	projectileTicks++;
	//SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
//	for(int i = 0; i < NUM_PROJECTILES; i++)
	//	SDL_RenderFillRect(gRenderer, &showBox[i]);
}

void Projectile::shootEnemy3(double x, double y, Chara* hildegarde) {
	defaultPosX = x; defaultPosY = y;
	if(projectileTicks / intv >= NUM_PROJECTILES)
		projectileTicks = 0;
	//printf("%i/%i/%g/%g/%b\n", projectileTicks/intv, projectileTicks%intv, projectiles2[projectileTicks/intv].dx, projectiles2[projectileTicks/intv].dy, projectiles2[projectileTicks/intv].shotBullet);
	gravityTicks++;

	if(projectileTicks % intv == 0 && (projectiles2[projectileTicks/intv].dx == 0.0 && projectiles2[projectileTicks/intv].dy == 0.0)) {
		projectiles2[projectileTicks/intv].posX = defaultPosX; projectiles2[projectileTicks/intv].posY = defaultPosY;
		projectiles2[projectileTicks/intv].defaultPosX = defaultPosX; projectiles2[projectileTicks/intv].defaultPosY = defaultPosY;
		projectiles2[projectileTicks/intv].mBox.x = posX; projectiles2[projectileTicks/intv].mBox.y = posY;
		projectiles2[projectileTicks/intv].targetX = rand()%SCREEN_WIDTH; projectiles2[projectileTicks/intv].targetY = rand()%(SCREEN_HEIGHT/4);
		projectiles2[projectileTicks/intv].speed = speed;
		projectiles2[projectileTicks/intv].mBox.w = mBox.w;
		projectiles2[projectileTicks/intv].mBox.h = mBox.h;
		//projectiles2[projectileTicks/intv].moveToXY(projectiles2[projectileTicks/intv].targetX, projectiles2[projectileTicks/intv].targetY);
		//printf("%i/%i\n", projectiles2[projectileTicks/intv].targetX, projectiles2[projectileTicks/intv].targetY);
		projectiles2[projectileTicks/intv].moveGravityBullet = 1;
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
}

void Projectile::shootEnemy4(double x, double y, Chara* hildegarde) {
	defaultPosX = x; defaultPosY = y;
	if(!shootReturn) {
		shootTicks += 5; 
		if(shootTicks >= SCREEN_WIDTH + 100)
			shootReturn = 1;
	} else {
		shootTicks -= 5;
		if(shootTicks <= -100)
			shootReturn = 0;
	}
	if(!initialisedLaser) {
		projectiles2[0].posX = defaultPosX; projectiles2[0].posY = defaultPosY;
		projectiles2[0].defaultPosX = defaultPosX; projectiles2[0].defaultPosY = defaultPosY;
		projectiles2[0].mBox.x = posX; projectiles2[0].mBox.y = posY;
		projectiles2[0].speed = speed;
		projectiles2[0].mBox.w = mBox.w;
		projectiles2[0].mBox.h = mBox.h;
		for(int i = 0; i < NUM_PROJECTILES; i++) {
			laserBoxes[i].w = mBox.w;
			laserBoxes[i].h = mBox.h;
		}
		initialisedLaser = 1;
	}
	if(checkCollision(projectiles2[0].mBox, camera)) {
		projectiles2[0].targetX = shootTicks; 
		projectiles2[0].targetY = SCREEN_HEIGHT;
		projectiles2[0].shotBullet = 0;
		projectiles2[0].moveToXY(projectiles2[0].targetX, projectiles2[0].targetY);
		int j;
		for(int i = 0; i < 100; i++) {
			projectiles2[0].posX += projectiles2[0].dx;
			projectiles2[0].posY += projectiles2[0].dy;
			projectiles2[0].mBox.x = projectiles2[0].posX;
			projectiles2[0].mBox.y = projectiles2[0].posY;
			laserBoxes[i].x = projectiles2[0].mBox.x;
			laserBoxes[i].y = projectiles2[0].mBox.y;
		}
	} else {
		projectiles2[0].posX = defaultPosX;
		projectiles2[0].posY = defaultPosY;
		projectiles2[0].mBox.x = projectiles2[0].posX;
		projectiles2[0].mBox.y = projectiles2[0].posY;
		projectiles2[0].dx = 0.0; projectiles2[0].dy = 0.0;
		projectiles2[0].shotBullet = 0;
	}
	if(projectiles2[0].dx != 0.0 || projectiles2[0].dy != 0.0) {
		//gTexture->render(projectiles2[i].mBox.x - projectiles2[i].mBox.w/3, projectiles2[i].mBox.y - projectiles2[i].mBox.h/3, NULL);
	} 
	//printf("%i/%i/%b/%i/%i/%i/%i\n", projectiles2[i].dx, projectiles2[i].dy, checkCollision(projectiles2[i].mBox, camera), hildegarde->getBox().x, hildegarde->getBox().y, projectiles2[i].targetX, projectiles2[i].targetY);
	projectileTicks++;
	SDL_SetRenderDrawColor(gRenderer, 255, 50, 0, 255);
	for(int i = 0; i < 100; i++)
		SDL_RenderFillRect(gRenderer, &laserBoxes[i]);
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
	gravityTicks = 1; initialisedLaser = 0;
}
