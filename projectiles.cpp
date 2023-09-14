#include "projectiles.h"
#include <cmath>

#define PI 3.14159265

bool clearBullets;

Projectile projectile2;
Projectile projectile3;
Projectile projectile4;
Projectile projectile5;
Projectile saucerProjectile;
Projectile starProjectile1;
Projectile projectileHG;

SDL_Rect laserBoxes[NUM_PROJECTILES];

Projectile::Projectile() {
  clearProjectilesPlus();
	
  projectileHG.setVariables(9, 9, 10.0, 10, &gHGArrow1Texture, 0, 9, 32);
  projectile2.setVariables(5, 5, 7.0, 30, &gBullet2, 0, 10, 10);
  projectile3.setVariables(15, 15, 6.0, 10, &gBullet1, 0, 25, 25);
  projectile4.setVariables(5, 5, 7.0, 5, &gBullet2);
  projectile5.setVariables(15, 15, 9.0, 2, &gBullet1, 0, 25, 25);
  saucerProjectile.setVariables(10, 23, 9.0, 2, &gSaucerBullet, 0, 23, 23);
  starProjectile1.setVariables(7, 7, 6.0, 10, &gStarBullet1, 0, 25, 25);
}

void Projectile::setProj(SDL_Rect box, double x, double y, double spd) {
  posX = x;
  posY = y;
  mBox.x = posX;
  mBox.y = posY;
  mBox.w = box.w;
  mBox.h = box.h;
  defaultPosX = posX;
  defaultPosY = posY;
  speed = spd;
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

void Projectile::shootHG(double x, double y, Enemy* enemy) {
  defaultPosX = x; defaultPosY = y;
  if(clearBullets)
    destroyProjs(NUM_PROJECTILES);
  createProjs(NUM_PROJECTILES);
  
  if(projectileTicks / intv == intv)
    projectileTicks = 0;
  
  
  if(HGAttacking && projectileTicks % intv == 0) {
    projs[projectilesShot]->setProj(mBox, x, y, speed);
    //printf("hgshot #%i posX=%f, posY=%f, mBox.x=%f, mBox.y=%f, defX=%f, defY=%f\n", projectilesShot, projs[projectilesShot]->posX, projs[projectilesShot]->posY, projs[projectilesShot]->mBox.x,projs[projectilesShot]->mBox.y, projs[projectilesShot]->defaultPosX, projs[projectilesShot]->defaultPosY);
    switch(attackDirection) {
    case 0: projs[projectilesShot]->dx = 0;
      projs[projectilesShot]->dy = -speed; 
      break;
    case 1: projs[projectilesShot]->dx = speed;
      projs[projectilesShot]->dy = 0; 
      break;
    case 2: projs[projectilesShot]->dx = speed;
      projs[projectilesShot]->dy = -speed; 
      break;
    case 3: projs[projectilesShot]->dx = 0;
      projs[projectilesShot]->dy = -speed; 
      break;
    case 4: projs[projectilesShot]->dx = -speed;
      projs[projectilesShot]->dy = -speed; 
      break;
    case 5: projs[projectilesShot]->dx = -speed;
      projs[projectilesShot]->dy = 0; 
      break;
    }
    projectilesShot++;
    if(projectilesShot >= NUM_PROJECTILES)
      projectilesShot = 0;
  }
  
  for(int i = 0; i < NUM_PROJECTILES; i++) {
    if(checkCollision(enemy->getBox(), projs[i]->mBox)) {
      enemy->takeDamage();
      projs[i]->clearProjectilesPlus();
    }
    if(checkCollision(projs[i]->mBox, camera)) {
      projs[i]->mBox.x += projs[i]->dx;
      projs[i]->mBox.y += projs[i]->dy;
      if(projs[i]->dx > 0) {
	if(projs[i]->dy > 0) {
	  angle = 135.0;
	} else if(projs[i]->dy < 0) {
	  angle = 45.0;
	} else if(projs[i]->dy == 0) {
	  angle = 90.0;
	}
      } else if(projs[i]->dx < 0) {
	if(projs[i]->dy > 0) {
	  angle = -135.0;
	} else if(projs[i]->dy < 0) {
	  angle = -45.0;
	} else if(projs[i]->dy == 0) {
	  angle = -90.0;
	}
      } else if(projs[i]->dx == 0) {
	if(projs[i]->dy > 0) {
	  angle = 180.0;
	} else if(projs[i]->dy < 0) {
	  angle = 0.0;
	} else if(projs[i]->dy == 0) {
	  angle = 0.0;
	}
      }
    } else {
      projs[i]->clearProjectilesPlus();
    }
    if(projs[i]->dx != 0 || projs[i]->dy != 0) {
      int renderX = projs[i]->mBox.x;
      int renderY = projs[i]->mBox.y;
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
    }
  }
  projectileTicks++;
}

void Projectile::moveToXY(double x, double y, bool moveY) {
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
    if(moveY) {
      if(posY < y)
	dy = speed*sinAngle;
      else {
	sinAngle = -sinAngle;
	dy = -speed*sinAngle;
      }
    }
    shotBullet = 1;
    //printf("%g/%g/%g/%g/%g/%g/%g/%g\n", dx, dy, side1, side2, r, sinAngle, cosAngle, speed);
  }
}


void Projectile::moveAcc(double x, double y, double acc) {
  if(!shotBullet) {
    double side1 = y - posY;
    double side2 = posX - x;
    double r = sqrt(side1 * side1 + side2 * side2);
    double sinAngle = (side1/r);
    double cosAngle = (side2/r);
    if(posX > x)
      dx += -speed*cosAngle*acc;
    else {
      cosAngle = -cosAngle;
      dx += speed*cosAngle*acc;
    }
    if(posY < y)
      dy += speed*sinAngle*acc;
    else {
      sinAngle = -sinAngle;
      dy += -speed*sinAngle*acc;
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
  }
}


double Projectile::getAngle(double x, double y) {
  double angle;
  double side1 = y - posY;
  double side2 = posX - x;
  double r = sqrt(side1 * side1 + side2 * side2);
  double cosAngle = (side2/r);
  angle = (std::acos(cosAngle)/PI*180.0 - 180) * -1;
  return angle;
}

void Projectile::addAngle(double angle) {
    double sinAngle = std::sin(angle*PI/180.0);
    double cosAngle = std::cos(angle*PI/180.0);

    dx += speed*cosAngle;
    dy += speed*sinAngle;
    shotBullet = 1;
}

void Projectile::moveGravity(double x, double y, double acc, bool moveX) {
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
    if(moveX) {
      if(posX > x)
	dx = -speed*cosAngle;
      else {
	cosAngle = -cosAngle;
	dx = speed*cosAngle;
      }
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

void Projectile::shootEnemy0(double x, double y, Chara* hildegarde, enemyIDEnum enemyID, int number, double sectionAngle, double startingAngle, int batch, double spd, bool rotate, bool angleTarget) {
  defaultPosX = x; defaultPosY = y;

  if(clearBullets)
   destroyProjs(NUM_PROJECTILES);
  else
    createProjs(NUM_PROJECTILES);
  
  switch(enemyID) {
  case conradID: //Conrad
    if(projectileTicks / intv >= number)
      projectileTicks = 0;
    //printf("%i/%i/%g/%g/%b\n", projectileTicks/intv, projectileTicks%intv, projs[projectileTicks/intv].dx, projs[projectileTicks/intv].dy, projs[projectileTicks/intv].shotBullet);
    if(projectileTicks % intv == 0 && (projs[projectileTicks/intv]->dx == 0.0 && projs[projectileTicks/intv]->dy == 0.0)) {
      projs[projectileTicks/intv]->posX = defaultPosX; projs[projectileTicks/intv]->posY = defaultPosY;
      projs[projectileTicks/intv]->defaultPosX = defaultPosX; projs[projectileTicks/intv]->defaultPosY = defaultPosY;
      projs[projectileTicks/intv]->mBox.x = posX; projs[projectileTicks/intv]->mBox.y = posY;
      projs[projectileTicks/intv]->targetX = hildegarde->getX(projs[projectileTicks/intv]->posX); projs[projectileTicks/intv]->targetY = hildegarde->getY(projs[projectileTicks/intv]->posY);
      projs[projectileTicks/intv]->speed = speed;
      projs[projectileTicks/intv]->mBox.w = mBox.w;
      projs[projectileTicks/intv]->mBox.h = mBox.h;
      projs[projectileTicks/intv]->moveToXY(projs[projectileTicks/intv]->targetX, projs[projectileTicks/intv]->targetY);
    }
    for(int i = 0; i < number; i++) {
      if(checkCollision(projs[number-1]->mBox, camera)) {
	projs[i]->posX += projs[i]->dx;
	projs[i]->posY += projs[i]->dy;
	projs[i]->mBox.x = projs[i]->posX;
	projs[i]->mBox.y = projs[i]->posY;
      } else {
	projs[i]->clearProjectilesPlus();
      }
      if(projs[i]->dx != 0.0 || projs[i]->dy != 0.0) {
	gTexture->render(projs[i]->mBox.x - projs[i]->mBox.w/3, projs[i]->mBox.y - projs[i]->mBox.h/3, NULL);
	//	showBox[i] = projs[i]->getBox();
      } 
    }
    projectileTicks++;
    break;
  case saucerID:  //Saucer enemy ID
    //difficulty = 2; // delete
    actualIntv = number;
    if(!rotate) {
      if(difficulty == 0)
	actualIntv = number;
      else if(difficulty == 1)
	actualIntv = number/1.5;
      else if(difficulty == 2)
	actualIntv = number/2;
    } else {
      if(difficulty == 0)
	actualIntv = number;
      else if(difficulty == 1)
	actualIntv = number/4;
      else if(difficulty == 2)
	actualIntv = number/8;
    }

    if(projectileTicks % actualIntv == 0) {
      for(int i = 0; i < batch; i++) {
	//printf("enemyshot %i\n", projectilesShot);
	projs[projectilesShot]->posX = defaultPosX;
	projs[projectilesShot]->posY = defaultPosY;
	projs[projectilesShot]->defaultPosX = defaultPosX;
	projs[projectilesShot]->defaultPosY = defaultPosY;
	projs[projectilesShot]->mBox.w = mBox.w;
	projs[projectilesShot]->mBox.h = mBox.h;
	projs[projectilesShot]->mBox.x = projs[projectilesShot]->posX;
	projs[projectilesShot]->mBox.y = projs[projectilesShot]->posY;
	projs[projectilesShot]->speed = spd;
	projs[projectilesShot]->targetX = hildegarde->getX();
	projs[projectilesShot]->targetY = hildegarde->getY();
	if(angleTarget) {
	  if(i == 0)
	    projs[projectilesShot]->moveToXY(projs[projectilesShot]->targetX, projs[projectilesShot]->targetY);
	  else if(i != 0 && i % 2 == 0)
	    projs[projectilesShot]->moveAngle(+projs[projectilesShot]->getAngle(projs[projectilesShot]->targetX, projs[projectilesShot]->targetY) - sectionAngle/2);
	  else if(i != 0 && i % 2 != 0)
	    projs[projectilesShot]->moveAngle(+projs[projectilesShot]->getAngle(projs[projectilesShot]->targetX, projs[projectilesShot]->targetY) + sectionAngle/2);
	} else {
	  projs[projectilesShot]->moveAngle(projectileAngle+startingAngle);
	}
	//printf("%f, %i, %f, %f\n", projectileAngle, projectilesShot, projs[projectilesShot]->dx, projs[projectilesShot]->dy);
	
	if(sectionAngle == 360.0) {
	  projectileAngle += sectionAngle/batch;
	  if(projectileAngle > sectionAngle)
	    projectileAngle = sectionAngle/batch;
	} else {
	  projectileAngle += sectionAngle/(batch-1);
	  if(projectileAngle > sectionAngle)
	    projectileAngle = 0;
	}
	
	projectilesShot++;
	if(projectilesShot >= NUM_PROJECTILES)
	  projectilesShot = 0;
      }
    }
    for(int i = 0; i < NUM_PROJECTILES; i++) {
      if(checkCollision(projs[i]->mBox, camera)) {
	projs[i]->posX += projs[i]->dx;
	projs[i]->posY += projs[i]->dy;
	projs[i]->mBox.x = projs[i]->posX;
	projs[i]->mBox.y = projs[i]->posY;
	if(rotate) {
	  projs[i]->angle += 5.0;
	  if(projs[i]->angle == 360)
	    projs[i]->angle = 0.0;
	}
      } else {
	renewProj(i);
	//projs[i]->clearProjectilesPlus();
      }
      if(projs[i]->dx != 0 || projs[i]->dy != 0) {
	gTexture->render(projs[i]->mBox.x - projs[i]->mBox.w/3, projs[i]->mBox.y - projs[i]->mBox.h/3, NULL, projs[i]->angle);
        projs[i]->checkDiePlus(hildegarde);
      }
      /*SDL_SetRenderDrawColor(gRenderer, 255, 50, 0, 255);
      SDL_Rect box = projs[i]->mBox;
      SDL_RenderFillRect(gRenderer, &box);*/
    }
    projectileTicks++;
    break;
  }
}

void Projectile::shootEnemy1(double x, double y, Chara* hildegarde, enemyIDEnum enemyID, int number, double sectionAngle, int batch, double spd, bool rotate) {
  defaultPosX = x; defaultPosY = y;

  if(clearBullets)
    destroyProjs(NUM_PROJECTILES);
  createProjs(NUM_PROJECTILES);
  
  switch(enemyID) {
  case conradID: // Conrad ID
    if(difficulty == 0)
      actualIntv = intv;
    else if(difficulty == 1)
      actualIntv = intv-2;
    else if(difficulty == 2)
      actualIntv = intv-4;
    if(projectileTicks / actualIntv >= NUM_PROJECTILES)
      projectileTicks = 0;
    //printf("%i/%i/%g/%g/%b\n", projectileTicks/actualIntv, projectileTicks%actualIntv, projs[projectileTicks/actualIntv]->dx, projs[projectileTicks/actualIntv]!->dy, projs[projectileTicks/actualIntv]->shotBullet);
    if(projectileTicks % actualIntv == 0 && (projs[projectileTicks/actualIntv]->dx == 0.0 && projs[projectileTicks/actualIntv]->dy == 0.0)) {
      projs[projectileTicks/actualIntv]->posX = defaultPosX; projs[projectileTicks/actualIntv]->posY = defaultPosY;
      projs[projectileTicks/actualIntv]->defaultPosX = defaultPosX; projs[projectileTicks/actualIntv]->defaultPosY = defaultPosY;
      projs[projectileTicks/actualIntv]->mBox.x = posX; projs[projectileTicks/actualIntv]->mBox.y = posY;
      projs[projectileTicks/actualIntv]->targetX = hildegarde->getX(projs[projectileTicks/actualIntv]->posX); projs[projectileTicks/actualIntv]->targetY = hildegarde->getY(projs[projectileTicks/actualIntv]->posY);
      projs[projectileTicks/actualIntv]->speed = speed;
      projs[projectileTicks/actualIntv]->mBox.w = mBox.w;
      projs[projectileTicks/actualIntv]->mBox.h = mBox.h;
      projs[projectileTicks/actualIntv]->moveToXY(projs[projectileTicks/actualIntv]->targetX, projs[projectileTicks/actualIntv]->targetY);
    }
    for(int i = 0; i < NUM_PROJECTILES; i++) {
      if(checkCollision(projs[i]->mBox, camera)) {
	projs[i]->posX += projs[i]->dx;
	projs[i]->posY += projs[i]->dy;
	projs[i]->mBox.x = projs[i]->posX;
	projs[i]->mBox.y = projs[i]->posY;
      } else {
        renewProj(i);
      }
      if(projs[i]->dx != 0.0 || projs[i]->dy != 0.0) {
	gTexture->render(projs[i]->mBox.x - projs[i]->mBox.w/3, projs[i]->mBox.y - projs[i]->mBox.h/3, NULL);
	//	showBox[i] = projs[i]->getBox();
      } 
      //printf("%i/%i/%b/%i/%i/%i/%i\n", projs[i]->dx, projs[i]->dy, checkCollision(projs[i]->mBox, camera), hildegarde->getBox()->x, hildegarde->getBox()->y, projs[i]->targetX, projs[i]->targetY);
    }
    projectileTicks++;
    //SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
    //	for(int i = 0; i < NUM_PROJECTILES; i++)
    //	SDL_RenderFillRect(gRenderer, &showBox[i]);
    break;
  case saucerID: //Saucer enemy ID
    actualIntv = number;
    //difficulty = 2;
    
    if(difficulty == 0)
      actualIntv = number*1.5;
    else if(difficulty == 1)
      actualIntv = number*1.25;
    else if(difficulty == 2)
      actualIntv = number;
    

    gravityTicks++;

    if(projectileTicks / actualIntv >= NUM_PROJECTILES)
      projectileTicks = 0;

    if(projectileTicks % actualIntv == 0) {
      for(int i = 0; i < batch; i++) {
	//printf("enemyshot %i\n", projectilesShot);
	projs[projectilesShot]->posX = defaultPosX;
	projs[projectilesShot]->posY = defaultPosY;
	projs[projectilesShot]->defaultPosX = defaultPosX;
	projs[projectilesShot]->defaultPosY = defaultPosY;
	projs[projectilesShot]->mBox.w = mBox.w;
	projs[projectilesShot]->mBox.h = mBox.h;
	projs[projectilesShot]->mBox.x = projs[projectilesShot]->posX;
	projs[projectilesShot]->mBox.y = projs[projectilesShot]->posY;
	if(!shotBatch) {
	  projs[projectilesShot]->targetX = projs[projectilesShot]->posX - 200;
	  if(i == batch-1)
	    shotBatch = 1;
	}
	else {
	  projs[projectilesShot]->targetX = projs[projectilesShot]->posX + 400;
	  if(i == batch-1)
	    shotBatch = 0;
	}
	projs[projectilesShot]->targetY = projs[projectilesShot]->posY - 50;
	projs[projectilesShot]->speed = 5.0+(i/5.0);
	projs[projectilesShot]->moveToXY(projs[projectilesShot]->targetX, projs[projectilesShot]->targetY);
	//printf("%f, %i, %f, %f\n", projectileAngle, projectilesShot, projs[projectilesShot]->dx, projs[projectilesShot]->dy);
	
	projectilesShot++;
	if(projectilesShot >= NUM_PROJECTILES)
	  projectilesShot = 0;
      }
    }

    for(int i = 0; i < NUM_PROJECTILES; i++) {
      if(checkCollision(projs[i]->mBox, camera) && projs[i]->dx != 0 && projs[i]->dy != 0) {
	if(i % batch == 0) {
	  if(projs[i]->mBox.y + projs[i]->mBox.h*2 < hildegarde->getY(projs[i]->posY)) {
	    for(int j = 0; j < batch; j++) {
	      if(i+j <= NUM_PROJECTILES) {
		projs[i+j]->shotBullet = 0;
		projs[i+j]->targetX = hildegarde->getX(projs[i]->posX);
		projs[i+j]->targetY = hildegarde->getY(projs[i]->posY);
		projs[i+j]->moveToXY(projs[i]->targetX, projs[i]->targetY);
		projs[i+j]->moveToXY(projs[i]->targetX, projs[i]->targetY);
		//printf("#%i %f %f\n", i+j, projs[i]->dx, projs[i]->dy);
	      }
	    }
	  }
	}
	//printf("%b #%i\n", projs[i]->disabled, i);
	projs[i]->posX += projs[i]->dx;
	projs[i]->posY += projs[i]->dy + 2.0;
	projs[i]->mBox.x = projs[i]->posX;
	projs[i]->mBox.y = projs[i]->posY;
	
	if(rotate) {
	  projs[i]->angle += 5.0;
	  if(projs[i]->angle == 360)
	    projs[i]->angle = 0.0;
	}
      } else {
	renewProj(i);
	//projs[i]->clearProjectilesPlus();
      }
      if(projs[i]->dx != 0 || projs[i]->dy != 0) {
	gTexture->render(projs[i]->mBox.x - projs[i]->mBox.w/3, projs[i]->mBox.y - projs[i]->mBox.h/3, NULL, projs[i]->angle);
        projs[i]->checkDiePlus(hildegarde);
      }
    }
    projectileTicks++;
    break;
  }
}

void Projectile::shootEnemy2(double x, double y, Chara* hildegarde, enemyIDEnum enemyID) {
  projectile5.shootEnemy0(x, y, hildegarde, enemyID, 5);
  if(difficulty == 0)
    actualIntv = intv;
  else if(difficulty == 1)
    actualIntv = intv-3;
  else if(difficulty == 2)
    actualIntv = intv-6;
  defaultPosX = x; defaultPosY = y;
  if(projectileTicks / actualIntv >= NUM_PROJECTILES)
    projectileTicks = 0;
  //printf("%i/%i/%g/%g/%b\n", projectileTicks/actualIntv, projectileTicks%actualIntv, projs[projectileTicks/actualIntv]->dx, projs[projectileTicks/actualIntv]->dy, projs[projectileTicks/actualIntv]->shotBullet);
  if(!shootReturn) {
    shootTicks +=20; 
    if(shootTicks >= SCREEN_WIDTH)
      shootReturn = 1;
  } else {
    shootTicks -=20;
    if(shootTicks <= 0)
      shootReturn = 0;
  }
  if(projectileTicks % actualIntv == 0 && (projs[projectileTicks/actualIntv]->dx == 0.0 && projs[projectileTicks/actualIntv]->dy == 0.0)) {
    projs[projectileTicks/actualIntv]->posX = defaultPosX; projs[projectileTicks/actualIntv]->posY = defaultPosY;
    projs[projectileTicks/actualIntv]->defaultPosX = defaultPosX; projs[projectileTicks/actualIntv]->defaultPosY = defaultPosY;
    projs[projectileTicks/actualIntv]->mBox.x = posX; projs[projectileTicks/actualIntv]->mBox.y = posY;
    projs[projectileTicks/actualIntv]->targetX = shootTicks; projs[projectileTicks/actualIntv]->targetY = hildegarde->getY(projs[projectileTicks/actualIntv]->posY);
    projs[projectileTicks/actualIntv]->speed = speed;
    projs[projectileTicks/actualIntv]->mBox.w = mBox.w;
    projs[projectileTicks/actualIntv]->mBox.h = mBox.h;
    projs[projectileTicks/actualIntv]->moveToXY(projs[projectileTicks/actualIntv]->targetX, projs[projectileTicks/actualIntv]->targetY);
  }
  for(int i = 0; i < NUM_PROJECTILES; i++) {
    if(checkCollision(projs[i]->mBox, camera)) {
      projs[i]->posX += projs[i]->dx;
      projs[i]->posY += projs[i]->dy;
      projs[i]->mBox.x = projs[i]->posX;
      projs[i]->mBox.y = projs[i]->posY;
    } else {
      projs[i]->posX = defaultPosX;
      projs[i]->posY = defaultPosY;
      projs[i]->mBox.x = projs[i]->posX;
      projs[i]->mBox.y = projs[i]->posY;
      projs[i]->dx = 0.0; projs[i]->dy = 0.0;
      projs[i]->shotBullet = 0;
    }
    if(projs[i]->dx != 0.0 || projs[i]->dy != 0.0) {
      gTexture->render(projs[i]->mBox.x - projs[i]->mBox.w/3, projs[i]->mBox.y - projs[i]->mBox.h/3, NULL, angle);
      //		showBox[i] = projs[i]->getBox();
    } 
    //printf("%i/%i/%b/%i/%i/%i/%i\n", projs[i]->dx, projs[i]->dy, checkCollision(projs[i]->mBox, camera), hildegarde->getBox()->x, hildegarde->getBox()->y, projs[i]->targetX, projs[i]->targetY);
  }
  projectileTicks++;
  //SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
  //	for(int i = 0; i < NUM_PROJECTILES; i++)
  //	SDL_RenderFillRect(gRenderer, &showBox[i]);
}

void Projectile::shootEnemy3(double x, double y, Chara* hildegarde, enemyIDEnum enemyID) {
  defaultPosX = x; defaultPosY = y;

  if(clearBullets)
    destroyProjs(NUM_PROJECTILES);
  createProjs(NUM_PROJECTILES);
  
  switch(enemyID) {
  case conradID:
    if(difficulty == 0)
      actualIntv = intv;
    else if(difficulty == 1)
      actualIntv = intv-2;
    else if(difficulty == 2)
      actualIntv = intv-4;
    if(projectileTicks / actualIntv >= NUM_PROJECTILES)
      projectileTicks = 0;
    //printf("%i/%i/%g/%g/%b\n", projectileTicks/actualIntv, projectileTicks%actualIntv, projs[projectileTicks/actualIntv]->dx, projs[projectileTicks/actualIntv]->dy, projs[projectileTicks/actualIntv]->shotBullet);
    gravityTicks++;

    if(projectileTicks % actualIntv == 0 && (projs[projectileTicks/actualIntv]->dx == 0.0 && projs[projectileTicks/actualIntv]->dy == 0.0)) {
      projs[projectileTicks/actualIntv]->posX = defaultPosX; projs[projectileTicks/actualIntv]->posY = defaultPosY;
      projs[projectileTicks/actualIntv]->defaultPosX = defaultPosX; projs[projectileTicks/actualIntv]->defaultPosY = defaultPosY;
      projs[projectileTicks/actualIntv]->mBox.x = posX; projs[projectileTicks/actualIntv]->mBox.y = posY;
      projs[projectileTicks/actualIntv]->targetX = rand()%SCREEN_WIDTH; projs[projectileTicks/actualIntv]->targetY = rand()%(SCREEN_HEIGHT/4);
      projs[projectileTicks/actualIntv]->speed = speed;
      projs[projectileTicks/actualIntv]->mBox.w = mBox.w;
      projs[projectileTicks/actualIntv]->mBox.h = mBox.h;
      //projs[projectileTicks/actualIntv]->moveToXY(projs[projectileTicks/actualIntv]->targetX, projs[projectileTicks/actualIntv]->targetY);
      //printf("%i/%i\n", projs[projectileTicks/actualIntv]->targetX, projs[projectileTicks/actualIntv]->targetY);
      projs[projectileTicks/actualIntv]->moveGravityBullet = 1;
    }
    for(int i = 0; i < NUM_PROJECTILES; i++) {
      if(checkCollision(projs[i]->mBox, camera)) {
	if(projs[i]->moveGravityBullet)
	  projs[i]->moveGravity(projs[i]->targetX, projs[i]->targetY, 0.1);
	projs[i]->posX += projs[i]->dx;
	projs[i]->posY += projs[i]->dy;
	projs[i]->mBox.x = projs[i]->posX;
	projs[i]->mBox.y = projs[i]->posY;
      } else {
	renewProj(i);
      }
      if(projs[i]->dx != 0.0 || projs[i]->dy != 0.0) {
	gTexture->render(projs[i]->mBox.x - projs[i]->mBox.w/3, projs[i]->mBox.y - projs[i]->mBox.h/3, NULL, angle);
	//		showBox[i] = projs[i]->getBox();
      } 
      //printf("%i/%i/%b/%i/%i/%i/%i\n", projs[i]->targetX, projs[i]->targetY);
    }
    projectileTicks++;
    //SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
    //	for(int i = 0; i < NUM_PROJECTILES; i++)
    //	SDL_RenderFillRect(gRenderer, &showBox[i]);
    break;
  case saucerID: //Saucer enemy ID
    if(difficulty == 0)
      actualIntv = 8;
    else if(difficulty == 1)
      actualIntv = 4;
    else if(difficulty == 2)
      actualIntv = 2;
    if(projectileTicks / actualIntv >= NUM_PROJECTILES)
      projectileTicks = 0;
    //printf("%i/%i/%g/%g/%b\n", projectileTicks/actualIntv, projectileTicks%actualIntv, projs[projectileTicks/actualIntv]->dx, projs[projectileTicks/actualIntv]->dy, projs[projectileTicks/actualIntv]->shotBullet);
    gravityTicks++;

    if(projectileTicks % actualIntv == 0 && (projs[projectileTicks/actualIntv]->dx == 0.0 && projs[projectileTicks/actualIntv]->dy == 0.0)) {
      projs[projectileTicks/actualIntv]->posX = defaultPosX; projs[projectileTicks/actualIntv]->posY = defaultPosY;
      projs[projectileTicks/actualIntv]->defaultPosX = defaultPosX; projs[projectileTicks/actualIntv]->defaultPosY = defaultPosY;
      projs[projectileTicks/actualIntv]->mBox.x = posX; projs[projectileTicks/actualIntv]->mBox.y = posY;
      projs[projectileTicks/actualIntv]->targetX = rand()%SCREEN_WIDTH; projs[projectileTicks/actualIntv]->targetY = SCREEN_HEIGHT;
      projs[projectileTicks/actualIntv]->speed = speed;
      projs[projectileTicks/actualIntv]->mBox.w = mBox.w;
      projs[projectileTicks/actualIntv]->mBox.h = mBox.h;
      //projs[projectileTicks/actualIntv]->moveToXY(projs[projectileTicks/actualIntv]->targetX, projs[projectileTicks/actualIntv]->targetY);
      //printf("%i/%i\n", projs[projectileTicks/actualIntv]->targetX, projs[projectileTicks/actualIntv]->targetY);
      projs[projectileTicks/actualIntv]->moveGravityBullet = 1;
    }
    for(int i = 0; i < NUM_PROJECTILES; i++) {
      if(checkCollision(projs[i]->mBox, camera)) {
	if(projs[i]->moveGravityBullet)
	  projs[i]->moveGravity(projs[i]->targetX, projs[i]->targetY, 0.1);
	projs[i]->posX += 1;
	projs[i]->posY += projs[i]->dy - 1;
	projs[i]->mBox.x = projs[i]->posX;
	projs[i]->mBox.y = projs[i]->posY;
      } else {
	projs[i]->posX = defaultPosX;
	projs[i]->posY = defaultPosY;
	projs[i]->mBox.x = projs[i]->posX;
	projs[i]->mBox.y = projs[i]->posY;
	projs[i]->dx = 0.0; projs[i]->dy = 0.0;
	projs[i]->shotBullet = 0; projs[i]->moveGravityBullet = 0;
      }
      if(projs[i]->dx != 0.0 || projs[i]->dy != 0.0) {
	gTexture->render(projs[i]->mBox.x - projs[i]->mBox.w/3, projs[i]->mBox.y - projs[i]->mBox.h/3, NULL, angle);
	//		showBox[i] = projs[i]->getBox();
	projs[i]->checkDiePlus(hildegarde);
      } 
      //printf("%i/%i/%b/%i/%i/%i/%i\n", projs[i]->targetX, projs[i]->targetY);
    }
    projectileTicks++;
    //SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
    //	for(int i = 0; i < NUM_PROJECTILES; i++)
    //	SDL_RenderFillRect(gRenderer, &showBox[i]);
    break;
  }
}

void Projectile::shootEnemy4(double x, double y, Chara* hildegarde, enemyIDEnum enemyID) {
  defaultPosX = x; defaultPosY = y;

  if(clearBullets)
    destroyProjs(NUM_PROJECTILES);
  createProjs(NUM_PROJECTILES);
  
  switch(enemyID) {
  case conradID:
	 if(!rolledShootAttack4Rand) {
	   shootAttack4Rand = rand()%2;
	   rolledShootAttack4Rand = 1;
	 }
	 if(shootLaser) {
	   if(difficulty == 1)
	     projectile5.shootEnemy0(x, y, hildegarde, enemyID, 5);
	   else if(difficulty == 2)
	     projectile5.shootEnemy0(x, y, hildegarde, enemyID, 10);
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
	   projs[0]->posX = defaultPosX; projs[0]->posY = defaultPosY;
	   projs[0]->defaultPosX = defaultPosX; projs[0]->defaultPosY = defaultPosY;
	   projs[0]->mBox.x = posX; projs[0]->mBox.y = posY;
	   projs[0]->speed = speed;
	   projs[0]->mBox.w = mBox.w;
	   projs[0]->mBox.h = mBox.h;
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
	       projs[i]->posX = defaultPosX; projs[i]->posY = defaultPosY;
	       projs[i]->defaultPosX = defaultPosX; projs[i]->defaultPosY = defaultPosY;
	       projs[i]->mBox.x = posX; projs[i]->mBox.y = posY;
	       projs[i]->speed = speed;
	       projs[i]->mBox.w = mBox.w;
	       projs[i]->mBox.h = mBox.h;
	       if(shootAttack4Rand == 0) {
		 projs[i]->targetX = SCREEN_WIDTH/2 - 100; 
		 projs[i]->targetY = SCREEN_HEIGHT/6;
	       } else {
		 projs[i]->targetX = SCREEN_WIDTH/2 + 100; 
		 projs[i]->targetY = SCREEN_HEIGHT/6;
	       }
	     }
	     initialiseStimulant = 0; 
	   }
	   if(checkCollision(projs[2]->mBox, camera)) {
	     for(int i = 0; i < 3; i++) {
	       if(projs[i]->dx == 0.0 && projs[i]->dy == 0.0) {
		 projs[i]->posX = defaultPosX; projs[i]->posY = defaultPosY;
	       }
	     }
	     projs[0]->moveGravity(projs[0]->targetX, projs[0]->targetY, 0.1);
	     projs[0]->posX += projs[0]->dx;
	     projs[0]->posY += projs[0]->dy;
	     projs[0]->mBox.x = projs[0]->posX;
	     projs[0]->mBox.y = projs[0]->posY;
	     if(stimulantTicks >= 30) {
	       projs[1]->moveGravity(projs[1]->targetX, projs[1]->targetY, 0.1);
	       projs[1]->posX += projs[1]->dx;
	       projs[1]->posY += projs[1]->dy;
	       projs[1]->mBox.x = projs[1]->posX;
	       projs[1]->mBox.y = projs[1]->posY;
	     }
	     if(stimulantTicks >= 60) {
	       projs[2]->moveGravity(projs[2]->targetX, projs[2]->targetY, 0.1);
	       projs[2]->posX += projs[2]->dx;
	       projs[2]->posY += projs[2]->dy;
	       projs[2]->mBox.x = projs[2]->posX;
	       projs[2]->mBox.y = projs[2]->posY;
	     }
	     for(int i = 0; i < 2; i++) {
	       if(checkCollision(projs[i]->mBox, hildegarde->getBox()))
		 hildegarde->death = 1;
	     }
	   } else {
	     for(int i = 0; i < 3; i++) {
	       renewProj(i);
	     }
	     initialiseLaser = 1; 
	     shootStimulant = 0; gravityTicks = 0;
	   }
			
	 }
	 if(shootLaser) {
	   if(checkCollision(projs[0]->mBox, camera)) {
	     if(shootAttack4Rand == 0)
	       projs[0]->targetX = shootTicks + 100;
	     else
	       projs[0]->targetX = SCREEN_WIDTH - shootTicks - 100;
	     projs[0]->targetY = SCREEN_HEIGHT;
	     projs[0]->shotBullet = 0;
	     projs[0]->moveToXY(projs[0]->targetX, projs[0]->targetY);
	     int j;
	     for(int i = 0; i < 120; i++) {
	       projs[0]->posX += projs[0]->dx;
	       projs[0]->posY += projs[0]->dy;
	       projs[0]->mBox.x = projs[0]->posX;
	       projs[0]->mBox.y = projs[0]->posY;
	       laserBoxes[i].x = projs[0]->mBox.x;
	       laserBoxes[i].y = projs[0]->mBox.y;
	       if(checkCollision(laserBoxes[i], hildegarde->getBox()))
		 hildegarde->death = 1;
	     }
	   } else {
	     renewProj(0);
	   }
	   SDL_SetRenderDrawColor(gRenderer, 255, 50, 0, 255);
	   for(int i = 0; i < 120; i++)
	     SDL_RenderFillRect(gRenderer, &laserBoxes[i]);
	 }
	 for(int i = 0; i < 3; i++) {
	   if((projs[i]->dx != 0.0 || projs[i]->dy != 0.0) && shootStimulant) {
	     gTexture->render(projs[i]->mBox.x - projs[i]->mBox.w/3, projs[i]->mBox.y - projs[i]->mBox.h/3, NULL);
	   } 
	 }
	 //printf("%i/%i/%b/%i/%i/%i/%i\n", projs[i]->dx, projs[i]->dy, checkCollision(projs[i]->mBox, camera), hildegarde->getBox()->x, hildegarde->getBox()->y, projs[i]->targetX, projs[i]->targetY);
	 projectileTicks++;
	 //printf("%i/%i/%i\n", shootAttack4Rand, projs[0]->targetX, shootTicks);
	 break;
  case saucerID: projs[0]->mBox.x = x;
    projs[0]->mBox.y = y;
    if(projectileTicks > 60) {
	   if(projectileTicks >= 70) {
	     projectileTicks = 0;
	   }
	   defaultPosX = x; defaultPosY = y;
	   if(checkCollision(projs[0]->mBox, camera)) {
	     projs[0]->mBox.w = mBox.w;
	     projs[0]->mBox.h = mBox.h;
	     projs[0]->targetX = defaultPosX;
	     projs[0]->targetY = SCREEN_HEIGHT;
	     projs[0]->shotBullet = 0;
	     projs[0]->moveToXY(projs[0]->targetX, projs[0]->targetY);
	     for(int i = 1; i < 120; i++) {
	       projs[0]->mBox.x += 0;
	       projs[0]->mBox.y += 23;
	       projs[i]->mBox = projs[0]->mBox;
	     }
	   } else {
	     renewProj(0);
	   }
	   //SDL_SetRenderDrawColor(gRenderer, 255, 50, 0, 255);
	   for(int i = 1; i < 120; i++) {
	     gTexture->render(projs[i]->mBox.x - mBox.w/2, projs[i]->mBox.y, NULL, angle);
	     //SDL_RenderFillRect(gRenderer, &projs[i]->mBox);
	     if(checkCollision(projs[i]->mBox, hildegarde->getBox()))
	       hildegarde->death = 1;
	     projs[i]->mBox.x = x;
	     projs[i]->mBox.y = y;
	     //printf("%i, %i, %i, %i\n", projs[i]->mBox->x, projs[i]->mBox->y, projs[i]->mBox->w, projs[i]->mBox->h);
	   }
	 }
    projectileTicks++;
    break;
  }
}


void Projectile::shootEnemy5(double x, double y, Chara* hildegarde, enemyIDEnum enemyID, int number, double sectionAngle, int batch, double spd) {
  defaultPosX = x; defaultPosY = y;

  if(clearBullets)
    destroyProjs(NUM_PROJECTILES);
  createProjs(NUM_PROJECTILES);
  
  switch(enemyID) {
  case conradID: //Conrad
    break;
  case saucerID:  //Saucer enemy ID
    //difficulty = 2; // delete
    actualIntv = number;
    if(difficulty == 0)
      actualIntv = number;
    else if(difficulty == 1)
      actualIntv = number/1.25;
    else if(difficulty == 2)
    actualIntv = number/1.5;

    if(projectileTicks % actualIntv == 0) {
      for(int i = 0; i < batch; i++) {
	//printf("enemyshot %i\n", projectilesShot);
	projs[projectilesShot]->posX = defaultPosX;
	projs[projectilesShot]->posY = defaultPosY;
	projs[projectilesShot]->defaultPosX = defaultPosX;
	projs[projectilesShot]->defaultPosY = defaultPosY;
	projs[projectilesShot]->mBox.w = mBox.w;
	projs[projectilesShot]->mBox.h = mBox.h;
	projs[projectilesShot]->mBox.x = projs[projectilesShot]->posX;
	projs[projectilesShot]->mBox.y = projs[projectilesShot]->posY;
	projs[projectilesShot]->speed = spd;
	projs[projectilesShot]->moveAngle(projectileAngle);
	//printf("%f, %i, %f, %f\n", projectileAngle, projectilesShot, projs[projectilesShot]->dx, projs[projectilesShot]->dy);
	
	if(sectionAngle == 360.0) {
	  projectileAngle += sectionAngle/batch;
	  if(projectileAngle > sectionAngle)
	    projectileAngle = sectionAngle/batch;
	} else {
	  projectileAngle += sectionAngle/(batch-1);
	  if(projectileAngle > sectionAngle)
	    projectileAngle = 0;
	}
	
	projectilesShot++;
	if(projectilesShot >= NUM_PROJECTILES)
	  projectilesShot = 0;
      }
    }
    for(int i = 0; i < NUM_PROJECTILES; i++) {
      if(checkCollision(projs[i]->mBox, camera)) {
	projs[i]->posX += projs[i]->dx;
	projs[i]->posY += projs[i]->dy;
	projs[i]->mBox.x = projs[i]->posX;
	projs[i]->mBox.y = projs[i]->posY;
      } else {
	//renewProj(i);
	projs[i]->clearProjectilesPlus();
      }
      if(projs[i]->dx != 0 || projs[i]->dy != 0) {
	gTexture->render(projs[i]->mBox.x - projs[i]->mBox.w/3, projs[i]->mBox.y - projs[i]->mBox.h/3, NULL, projs[i]->angle);
        projs[i]->checkDiePlus(hildegarde);
      }
      /*SDL_SetRenderDrawColor(gRenderer, 255, 50, 0, 255);
      SDL_Rect box = projs[i]->mBox;
      SDL_RenderFillRect(gRenderer, &box);*/
    }
    projectileTicks++;
    break;
  }
}

int deaths;
void Projectile::checkDiePlus(Chara* hildegarde) {
  if(checkCollision(hildegarde->getBox(), mBox) && !hildegarde->death) {
    hildegarde->death = 1;
    deaths++;
    //printf("Bullet collides with Hildegarde %f, %f, %f, %f #%i\n", posX, posY, dx, dy, deaths);
    /*SDL_SetRenderDrawColor(gRenderer, 255, 50, 0, 255);
    SDL_Rect box = mBox; box.w *= 10; box.h*= 10;
    SDL_RenderFillRect(gRenderer, &box);*/
    clearProjectilesPlus();
  }
}

void Projectile::checkDie(Chara* hildegarde) {
  for(int i = 0; i < NUM_PROJECTILES; i++) {
    if(checkCollision(hildegarde->getBox(), projs[i]->mBox)) {
      hildegarde->death = 1;
    }
  }
}

void Projectile::checkDie1(Chara* hildegarde) {
  for(int i = 0; i < NUM_PROJECTILES; i++) {
    if(checkCollision(hildegarde->getBox(), projs[i]->mBox)) {
      hildegarde->death = 1;
    }
  }
}

void Projectile::clearProjectilesPlus() {
  posX = defaultPosX;
  posY = defaultPosY;
  angle = 0.0;
  mBox.x = posX;
  mBox.y = posY;
  dx = 0.0; dy = 0.0;
  shotBullet = 0;
  moveGravityBullet = 0;
  shootTicks = 0; shootReturn = 0;
  gravityTicks = 1; initialiseLaser = 0;
  shootLaser = 0; initialiseStimulant = 1;
  shootStimulant = 1; rolledShootAttack4Rand = 0;
  stimulantTicks = 0; projectileAngle = 0;
  projectilesShot = 0; projectileTicks = 0;
  shotBatch = 0;  disabled = 0;
}

void Projectile::createProjs(int num) {
  if(!createdProjs) {
    for(int i = 0; i < num; i++) {
      projs[i] = new Projectile();
      projs[i]->setProj(mBox, posX, posY, speed);
    }
    //printf("created bullets #%i, %i, %i\n", num, mBox.w, mBox.h);
    createdProjs = 1;
  }
}

void Projectile::destroyProjs(int num) {
  if(createdProjs) {
    for(int i = 0; i < num; i++) {
      projs[i]->clearProjectilesPlus();
      delete projs[i];
    }
    createdProjs = 0;
  }
  //printf("deleted bullet #%i, %i, %i, %b\n", num, mBox.w, mBox.h, createdProjs);
}

void Projectile::renewProj(int num) {
  delete projs[num];
  projs[num] = new Projectile();
  projs[num]->setProj(mBox, posX, posY, speed);
}
