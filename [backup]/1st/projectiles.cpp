#include "projectiles.h"

Projectile::Projectile() {
	activeProjectiles = 0;
	projectile1.setVariables(9, 32, 6, 5, &gHGArrow1Texture);
}

void Projectile::setVariables(int w, int h, int spd, int interval, LTexture* gSetTexture) {
	gTexture = gSetTexture;
	mBox.w = w; mBox.h = h;
	speed = spd;
	intv = interval;
}
int Projectile::getSpd() {
	return speed;
}
int Projectile::getIntv() {
	return intv;
}

void Projectile::render(int x, int y) {
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
			gTexture->render(projectiles1[i].mBox.x, projectiles1[i].mBox.y, NULL, angle);
		} else {
			projectiles1[i].mBox.x = defaultPosX;
			projectiles1[i].mBox.y = defaultPosY;
		}
	}
	projectileTicks++;
}

void Projectile::addProjectiles() {
	activeProjectiles++;
}

int Projectile::getActiveProjectiles() {
	return activeProjectiles;
}

