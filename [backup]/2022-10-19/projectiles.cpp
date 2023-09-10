#include "projectiles.h"
#include <cmath>

SDL_Rect showBox[NUM_PROJECTILES];

Projectile::Projectile() {
	activeProjectiles = 0;
	projectile1.setVariables(9, 9, 6.0, 5, &gHGArrow1Texture, 0, 9, 32);
	projectile2.setVariables(5, 5, 6.0, 5, &gHGArrow1Texture, 0, 9, 32);
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

void Projectile::moveToXY(int x, int y) {
	if(!shotBullet) {
		double side1 = y - mBox.y;
		double side2 = mBox.x - x;
		double r = sqrt(side1 * side1 + side2 * side2);
		double sinAngle = (side1/r);
		double cosAngle = (side2/r);
		if(mBox.x > x)
			dx = -speed*cosAngle;
		else {
			cosAngle = -cosAngle;
			dx = speed*cosAngle;
		}
		if(mBox.y < y)
			dy = speed*sinAngle;
		else {
			sinAngle = -sinAngle;
			dy = -speed*sinAngle;
		}
		shotBullet = 1;
		printf("%g/%g/%g/%g/%g/%g/%g/%g\n", dx, dy, side1, side2, r, sinAngle, cosAngle, speed);
	}
}

void Projectile::shootEnemy(int x, int y, Chara* hildegarde, Projectile projectiles2[]) {
	defaultPosX = x; defaultPosY = y;
	if(projectileTicks / intv >= NUM_PROJECTILES)
		projectileTicks = 0;
	if(projectileTicks % intv == 0 && (projectiles2[projectileTicks/intv].dx == 0 && projectiles2[projectileTicks/intv].dy == 0)) {
		projectiles2[projectileTicks/intv].targetX = hildegarde->getBox().x; projectiles2[projectileTicks/intv].targetY = hildegarde->getBox().y; 
		projectiles2[projectileTicks/intv].speed = projectile2.speed;
		projectiles2[projectileTicks/intv].mBox.w = projectile2.mBox.w;
		projectiles2[projectileTicks/intv].mBox.h = projectile2.mBox.h;
		projectiles2[projectileTicks/intv].moveToXY(projectiles2[projectileTicks/intv].targetX, projectiles2[projectileTicks/intv].targetY);
	}
	for(int i = 0; i < NUM_PROJECTILES; i++) {
		if(checkCollision(projectiles2[i].mBox, camera)) {
			projectiles2[i].mBox.x += projectiles2[i].dx;
			projectiles2[i].mBox.y += projectiles2[i].dy;

			if(projectiles2[i].dx > 0) {
				if(projectiles2[i].dy > 0) {
					angle = 135.0;
				} else if(projectiles2[i].dy < 0) {
					angle = 45.0;
				} else if(projectiles2[i].dy == 0) {
					angle = 90.0;
				}
			} else if(projectiles2[i].dx < 0) {
				if(projectiles2[i].dy > 0) {
					angle = -135.0;
				} else if(projectiles2[i].dy < 0) {
					angle = -45.0;
				} else if(projectiles2[i].dy == 0) {
					angle = -90.0;
				}
			} else if(projectiles2[i].dx == 0) {
				if(projectiles2[i].dy > 0) {
					angle = 180.0;
				} else if(projectiles2[i].dy < 0) {
					angle = 0.0;
				} else if(projectiles2[i].dy == 0) {
					angle = 0.0;
				}
			}
		} else {
			projectiles2[i].mBox.x = defaultPosX;
			projectiles2[i].mBox.y = defaultPosY;
			projectiles2[i].dx = 0.0; projectiles2[i].dy = 0.0;
			shotBullet = 0;
		}
		if(projectiles2[i].dx != 0 || projectiles2[i].dy != 0) {
			gTexture->render(projectiles2[i].mBox.x, projectiles2[i].mBox.y, NULL, angle);
		} else {
			projectiles2[i].mBox.x = defaultPosX;
			projectiles2[i].mBox.y = defaultPosY;
		}
		//printf("%i/%i/%b/%i/%i/%i/%i\n", projectiles2[i].dx, projectiles2[i].dy, checkCollision(projectiles2[i].mBox, camera), hildegarde->getBox().x, hildegarde->getBox().y, projectiles2[i].targetX, projectiles2[i].targetY);
	}
	projectileTicks++;
}
