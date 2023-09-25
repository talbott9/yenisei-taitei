#include "projectiles.h"
#include <cmath>

#define PI 3.14159265

bool clearBullets;

Projectile projectile2, projectile3, projectile4, projectile5, saucerProjectile, starProjectile1, snowflakeProjectile, shardProjectile, soundProjectile, daggerProjectile, projectileHG;

SDL_Rect laserBoxes[NUM_PROJECTILES];

Projectile::Projectile() {
  clearProjectilesPlus();
	
  projectileHG.setVariables(9, 9, 15.0, 10, &gHGArrow1Texture, 0, 9, 32);
  projectile2.setVariables(5, 5, 7.0, 30, &gBullet2, 0, 10, 10);
  projectile3.setVariables(15, 15, 6.0, 10, &gBullet1, 0, 25, 25);
  projectile4.setVariables(5, 5, 7.0, 5, &gBullet2);
  projectile5.setVariables(15, 15, 9.0, 2, &gBullet1, 0, 25, 25);
  saucerProjectile.setVariables(10, 23, 9.0, 2, &gSaucerBullet, 0, 23, 23);
  starProjectile1.setVariables(7, 7, 6.0, 10, &gStarBullet1, 0, 25, 25);
  snowflakeProjectile.setVariables(8, 8, 6.0, 10, &gSnowflakeBullet, 0, 15, 15);
  shardProjectile.setVariables(7, 7, 6.0, 10, &gShardBullet, 0, 25, 25, false);
  soundProjectile.setVariables(15, 15, 6.0, 10, &gSoundBullet, 0, 25, 25);
  daggerProjectile.setVariables(5, 5, 6.0, 10, &gDaggerBullet, 0, 25, 25, true);
}

void Projectile::setProj(SDL_Rect box, double x, double y, double spd, bool isLong) {
  posX = x;
  posY = y;
  mBox.x = posX;
  mBox.y = posY;
  mBox.w = box.w;
  mBox.h = box.h;
  defaultPosX = posX;
  defaultPosY = posY;
  speed = spd;
  projectileIsLong = isLong;
}


void Projectile::setVariables(int w, int h, double spd, int interval, LTexture* gSetTexture, int orient, int spriteW, int spriteH, bool isLong) {
  gTexture = gSetTexture;
  mBox.w = w; mBox.h = h;
  speed = spd;
  intv = interval;
  orientation = orient;
  spriteWidth = spriteW;
  spriteHeight = spriteH;
  projectileIsLong = isLong;
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

  double projSlow = 1.0;
  if(slowDown)
    projSlow = 0.25;
  
  int actualIntv = intv/projSlow;

  double spd = speed;
  
  if(projectileTicks / actualIntv == actualIntv)
    projectileTicks = 0;
  
  if(HGAttacking && projectileTicks % actualIntv == 0) {
    projs[projectilesShot]->setProj(mBox, x, y, spd, projectileIsLong);
    switch(attackDirection) {
    case 0:
      break;
    case 1: projs[projectilesShot]->dx = spd;
      projs[projectilesShot]->dy = 0;
      projs[projectilesShot]->angle = 0.0;
      break;
    case 2: projs[projectilesShot]->dx = 10.6;
      projs[projectilesShot]->dy = -10.6;
      projs[projectilesShot]->angle = 315.0;
      if(slowDown)
	projs[projectilesShot]->dx += 0.35/projSlow;
      break;
    case 3: projs[projectilesShot]->dx = 0;
      projs[projectilesShot]->dy = -spd;
      projs[projectilesShot]->angle = 270.0;
      break;
    case 4: projs[projectilesShot]->dx = -10.6;
      projs[projectilesShot]->dy = -10.6;
      projs[projectilesShot]->angle = 225.0;
      if(slowDown)
	projs[projectilesShot]->dx -= 0.35/projSlow;
      break;
    case 5: projs[projectilesShot]->dx = -spd;
      projs[projectilesShot]->dy = 0;
      projs[projectilesShot]->angle = 180.0;
      break;
    }

    //printf("%f, %f\n", projs[projectilesShot]->dx, projs[projectilesShot]->dy) ;

    projectilesShot++;
    if(projectilesShot >= NUM_PROJECTILES)
      projectilesShot = 0;
  }

  //printf("%i\n", attackDirection);
  
  for(int i = 0; i < NUM_PROJECTILES; i++) {
    if(checkCollision(enemy->getBox(), projs[i]->mBox) && (projs[i]->dx != 0 || projs[i]->dy != 0)) {
      enemy->takeDamage();
      projs[i]->clearProjectilesPlus();
    }
    if(checkCollision(projs[i]->mBox, camera)) {
      projs[i]->mBox.x += projs[i]->dx*projSlow;
      projs[i]->mBox.y += projs[i]->dy*projSlow;
    } else {
      projs[i]->clearProjectilesPlus();
    }
    if(projs[i]->dx != 0 || projs[i]->dy != 0) {
      int renderX = projs[i]->mBox.x;
      int renderY = projs[i]->mBox.y;
      int angleInt = projs[i]->angle;
      switch(angleInt) {
      case 0: renderX += -spriteWidth/2 - 7; break;
      case 180: renderX -= -spriteWidth/2 - 7; break;
      case 270: renderX += -spriteWidth - 3; 
	renderY -= -spriteHeight + spriteHeight/2; break;
      case 315: renderX += -spriteWidth - spriteWidth - 3; 
	renderY -= -spriteHeight + spriteHeight/2 + 5; break;
      case 225: renderX += -spriteWidth - spriteWidth + 15; 
	renderY -= -spriteHeight + spriteHeight/2 + 5; break;
      } 
      //printf("%i\n", angleInt);
      gTexture->render(renderX - camera.x, renderY - camera.y, NULL, projs[i]->angle);

      //SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
      //SDL_RenderFillRect(gRenderer, &projs[i]->mBox);
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

void Projectile::moveOscillate(double x, double y, bool startRight) {
  double spdMod = 2;
  if(!shotBullet) {
    double side1 = y - posY;
    double side2 = posX - x;
    double r = sqrt(side1 * side1 + side2 * side2);
    double sinAngle = (side1/r);
    double cosAngle = (side2/r);
    if(posX > x)
      dx += -speed*cosAngle;
    else {
      cosAngle = -cosAngle;
      dx += speed*cosAngle;
    }
    if(posY < y)
      dy += speed*sinAngle;
    else {
      sinAngle = -sinAngle;
      dy += -speed*sinAngle;
    }
    shotBullet = 1;
    if(!horizontalOsc) {
      dy = 2.5;
      dx = 0;
    } else {
      dy = 0;
      dx = 2.5;
    }
  }

  //if(firstOsc)
  //  osc = 65;
  int osc = 30;
    
  
  if(startRight) {
    if(oscillationTicks < osc) {
      if(switchOsc) {
	if(!horizontalOsc)
	  dx -= speed;
	else
	  dy -= speed;
      } else {
	if(!horizontalOsc)
	  dx += speed;
	else
	  dy += speed;
      }
    } else {
      if(switchOsc) {
	if(!horizontalOsc)
	  dx+= speed;
	else
	  dy += speed;
      } else {
	if(!horizontalOsc)
	  dx -= speed;
	else
	  dy -= speed;
      }
    }
  } else {
    if(oscillationTicks < osc) {
      if(switchOsc) {
	if(!horizontalOsc)
	  dx += speed;
	else
	  dy += speed;
      } else {
	if(!horizontalOsc)
	  dx -= speed + 0.005;
	else
	  dy -= speed + 0.005;
      }
    } else {
      if(switchOsc) {
	if(!horizontalOsc)
	  dx -= speed + 0.005;
	else
	  dy -= speed + 0.005;
      } else {
	if(!horizontalOsc)
	  dx += speed;
	else
	  dy += speed;
      }
    }
  }
  
  oscillationTicks++;
  if(oscillationTicks >= osc*2) {
    oscillationTicks = 0;
    if(switchOsc)
      switchOsc = 0;
    else
      switchOsc = 1;
    //if(firstOsc) {
    // dx = 0.01; dy = 0.01;
    // firstOsc = 0;
    //}
  }
  //printf("%f, %f\n", dx, mBox.x);
}

void Projectile::moveAngle(double angle) {
  if(!shotBullet) {
    double sinAngle = std::sin(angle*PI/180.0);
    double cosAngle = std::cos(angle*PI/180.0);

    dx = speed*cosAngle;
    dy = speed*sinAngle;
    shotBullet = 1;
    targetX = posX+dx*10;
    targetY = posY+dy*10;
  }
}


double Projectile::getAngle(double x, double y) {
  double angle;
  double side1 = y - posY;
  double side2 = posX - x;
  double r = sqrt(side1 * side1 + side2 * side2);
  double cosAngle = (side2/r);
  if(r == 0)
    angle = 90.0;
  else
    angle = ((std::acos(cosAngle)/PI*180.0) - 180.0) * -1.0;
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

void Projectile::shootEnemy0(double x, double y, Chara* hildegarde, enemyIDEnum enemyID, int number, double sectionAngle, double startingAngle, int batch, double spd, bool rotate, bool angleTarget, double slow, bool shootBool) {
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
	gTexture->render(projs[i]->mBox.x - projs[i]->mBox.w/3 - camera.x, projs[i]->mBox.y - projs[i]->mBox.h/3 - camera.y, NULL);
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
	gTexture->render(projs[i]->mBox.x - projs[i]->mBox.w/3 - camera.x, projs[i]->mBox.y - projs[i]->mBox.h/3 - camera.y, NULL, projs[i]->angle);
        projs[i]->checkDiePlus(hildegarde);
      }
      /*SDL_SetRenderDrawColor(gRenderer, 255, 50, 0, 255);
      SDL_Rect box = projs[i]->mBox;
      SDL_RenderFillRect(gRenderer, &box);*/
    }
    projectileTicks++;
    break;
  case hyacintheID:  //Saucer enemy ID
    //difficulty = 2; // delete
    actualIntv = number;
    if(difficulty == 0)
      actualIntv = number;
    else if(difficulty == 1)
      actualIntv = number/1.5;
    else if(difficulty == 2)
      actualIntv = number/2;

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
	if(angleTarget) {
	  double thing1 = i;
	  double thing2 = batch;
	  double thing = (thing1/thing2);
	  projs[projectilesShot]->speed = spd-(thing*10);
	}
	projs[projectilesShot]->targetX = hildegarde->getX();
	projs[projectilesShot]->targetY = hildegarde->getY();
	if(angleTarget) {
	  if(counter == 0)
	    projs[projectilesShot]->moveToXY(projs[projectilesShot]->targetX, projs[projectilesShot]->targetY);
	  else if(counter == 1)
	    projs[projectilesShot]->moveAngle(+projs[projectilesShot]->getAngle(projs[projectilesShot]->targetX, projs[projectilesShot]->targetY) - sectionAngle/2);
	  else if(counter == 2) 
	    projs[projectilesShot]->moveAngle(+projs[projectilesShot]->getAngle(projs[projectilesShot]->targetX, projs[projectilesShot]->targetY) + sectionAngle/2);
	  if(counter != 2)
	    counter++;
	  else
	    counter = 0;
	} else {
	  projs[projectilesShot]->moveAngle(projectileAngle+startingAngle);
	  if(!rotate)
	    projs[projectilesShot]->angle = projs[projectilesShot]->getAngle(projs[projectilesShot]->targetX, projs[projectilesShot]->targetY);
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
	projs[i]->posX += projs[i]->dx*slow;
	projs[i]->posY += projs[i]->dy*slow;
	//printf("%f, %f, %f\n", projs[i]->dx*slow, projs[i]->dy*slow, slow);
	
	projs[i]->mBox.x = projs[i]->posX;
	projs[i]->mBox.y = projs[i]->posY;
	if(rotate) {
	  projs[i]->angle += 5.0*slow;
	  if(projs[i]->angle == 360)
	    projs[i]->angle = 0.0;
	}
      } else {
	renewProj(i);
	//projs[i]->clearProjectilesPlus();
      }
      if(projs[i]->dx != 0 || projs[i]->dy != 0) {
	gTexture->render(projs[i]->mBox.x - projs[i]->mBox.w/3 - camera.x, projs[i]->mBox.y - projs[i]->mBox.h/3 - camera.y, NULL, projs[i]->angle);
        projs[i]->checkDiePlus(hildegarde);
      }
      /*SDL_SetRenderDrawColor(gRenderer, 255, 50, 0, 255);
      SDL_Rect box = projs[i]->mBox;
      SDL_RenderFillRect(gRenderer, &box);*/
    }
    projectileTicks++;
    break;
   case troubadourID:  //Saucer enemy ID
    //difficulty = 2; // delete
    actualIntv = number;
    if(difficulty == 0)
      actualIntv = number;
    else if(difficulty == 1)
      actualIntv = number/1.5;
    else if(difficulty == 2)
      actualIntv = number/2;

    if(projectileTicks % actualIntv == 0 || shootBool) {
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
	if(angleTarget) {
	  double thing1 = i;
	  double thing2 = batch;
	  double thing = (thing1/thing2);
	  projs[projectilesShot]->speed = spd+(thing*10);
	}
	projs[projectilesShot]->targetX = hildegarde->getX();
	projs[projectilesShot]->targetY = hildegarde->getY();
	
	if(angleTarget) {
	  if(counter == 0)
	    projs[projectilesShot]->moveToXY(projs[projectilesShot]->targetX, projs[projectilesShot]->targetY);
	  else if(counter == 1)
	    projs[projectilesShot]->moveAngle(projs[projectilesShot]->getAngle(projs[projectilesShot]->targetX, projs[projectilesShot]->targetY) - sectionAngle/2);
	  else if(counter == 2) 
	    projs[projectilesShot]->moveAngle(projs[projectilesShot]->getAngle(projs[projectilesShot]->targetX, projs[projectilesShot]->targetY) + sectionAngle/2);
	  if(counter != 2)
	    counter++;
	  else
	    counter = 0;
	  projs[projectilesShot]->angle = projs[projectilesShot]->getAngle(projs[projectilesShot]->targetX, projs[projectilesShot]->targetY);
	} else {
	  projs[projectilesShot]->moveAngle(projectileAngle+startingAngle);
	  if(!rotate)
	    projs[projectilesShot]->angle = projs[projectilesShot]->getAngle(projs[projectilesShot]->targetX, projs[projectilesShot]->targetY);
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
	projs[i]->posX += projs[i]->dx*slow;
	projs[i]->posY += projs[i]->dy*slow;
	//printf("%f, %f, %f\n", projs[i]->dx*slow, projs[i]->dy*slow, slow);
	
	projs[i]->mBox.x = projs[i]->posX;
	projs[i]->mBox.y = projs[i]->posY;
	if(rotate) {
	  projs[i]->angle += 5.0*slow;
	  if(projs[i]->angle == 360)
	    projs[i]->angle = 0.0;
	}
      } else {
	renewProj(i);
	//projs[i]->clearProjectilesPlus();
      }
      if(projs[i]->dx != 0.0 || projs[i]->dy != 0.0) {
	gTexture->render(projs[i]->mBox.x - projs[i]->mBox.w - camera.x, projs[i]->mBox.y - projs[i]->mBox.h/2 - camera.y, NULL, projs[i]->angle);
        projs[i]->checkDiePlus(hildegarde);
	SDL_SetRenderDrawColor(gRenderer, 255, 50, 0, 255);
	SDL_RenderFillRect(gRenderer, &projs[i]->mBox);
      }
    }
    projectileTicks++;
    break;
  case bohemondID:  //Saucer enemy ID
    //difficulty = 2; // delete
    actualIntv = number;
    if(difficulty == 0)
      actualIntv = number*2;
    else if(difficulty == 1)
      actualIntv = number*1.5;
    else if(difficulty == 2)
      actualIntv = number;

    if(projectileTicks % actualIntv == 0 || shootBool) {
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
	if(angleTarget) {
	  double thing1 = i;
	  double thing2 = batch;
	  double thing = (thing1/thing2);
	  projs[projectilesShot]->speed = spd+(thing*10);
	}
	projs[projectilesShot]->targetX = hildegarde->getX();
	projs[projectilesShot]->targetY = hildegarde->getY();
	
	if(angleTarget) {
	  if(counter == 0)
	    projs[projectilesShot]->moveToXY(projs[projectilesShot]->targetX, projs[projectilesShot]->targetY);
	  else if(counter == 1)
	    projs[projectilesShot]->moveAngle(projs[projectilesShot]->getAngle(projs[projectilesShot]->targetX, projs[projectilesShot]->targetY) - projectileAngle);
	  else if(counter == 2) 
	    projs[projectilesShot]->moveAngle(projs[projectilesShot]->getAngle(projs[projectilesShot]->targetX, projs[projectilesShot]->targetY) + projectileAngle);
	  if(counter != 2)
	    counter++;
	  else
	    counter = 0;
	  projs[projectilesShot]->angle = projs[projectilesShot]->getAngle(projs[projectilesShot]->targetX, projs[projectilesShot]->targetY);
	} else {
	  projs[projectilesShot]->moveAngle(projectileAngle+startingAngle);
	  if(!rotate)
	    projs[projectilesShot]->angle = projs[projectilesShot]->getAngle(projs[projectilesShot]->targetX, projs[projectilesShot]->targetY);
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
      if(checkCollision(projs[i]->mBox, camera) && (projs[i]->dx != 0.0 || projs[i]->dy != 0.0)) {
	projs[i]->posX += projs[i]->dx*slow;
	projs[i]->posY += projs[i]->dy*slow;
	//printf("%f, %f, %f\n", projs[i]->dx*slow, projs[i]->dy*slow, slow);
	
	projs[i]->mBox.x = projs[i]->posX;
	projs[i]->mBox.y = projs[i]->posY;
	if(rotate) {
	  projs[i]->angle += 5.0*slow;
	  if(projs[i]->angle == 360)
	    projs[i]->angle = 0.0;
	}
	if(projectileIsLong) {
	  projs[i]->setLongProjBox();
	}
      } else {
	renewProj(i);
	//projs[i]->clearProjectilesPlus();
      }
      if(projs[i]->dx != 0.0 || projs[i]->dy != 0.0) {
	gTexture->render(projs[i]->mBox.x - spriteWidth/2 + 2 - camera.x, projs[i]->mBox.y - spriteHeight/2 - camera.y, NULL, projs[i]->angle);
        projs[i]->checkDiePlus(hildegarde);
	SDL_SetRenderDrawColor(gRenderer, 255, 50, 0, 255);
	SDL_RenderFillRect(gRenderer, &projs[i]->mBox);
	if(projs[i]->projectileIsLong)
	  SDL_RenderFillRect(gRenderer, &projs[i]->mBox1);
      }
    }
    projectileTicks++;
    break;
  }
}

void Projectile::shootEnemy1(double x, double y, Chara* hildegarde, enemyIDEnum enemyID, int number, double sectionAngle, int batch, double spd, bool rotate, bool shootBool) {
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
	gTexture->render(projs[i]->mBox.x - projs[i]->mBox.w/3 - camera.x, projs[i]->mBox.y - projs[i]->mBox.h/3 - camera.y, NULL);
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
	projs[projectilesShot]->speed = 5.0+(i/5.0)*spd;
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
	gTexture->render(projs[i]->mBox.x - projs[i]->mBox.w/3 - camera.x, projs[i]->mBox.y - projs[i]->mBox.h/3 - camera.y, NULL, projs[i]->angle);
        projs[i]->checkDiePlus(hildegarde);
      }
    }
    projectileTicks++;
    break;
  case hyacintheID:
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
	projs[projectilesShot]->targetX = hildegarde->getX();
	projs[projectilesShot]->targetY = hildegarde->getY();
	double thing1 = i;
	double thing2 = batch;
	double thing = (thing1/thing2);
	projs[projectilesShot]->speed = spd-(thing*10);
	//printf("%f\n", thing);
	projs[projectilesShot]->angle = projs[projectilesShot]->getAngle(projs[projectilesShot]->targetX, projs[projectilesShot]->targetY);
	projs[projectilesShot]->moveToXY(projs[projectilesShot]->targetX, projs[projectilesShot]->targetY);
	//printf("%f, %i, %f, %f\n", projectileAngle, projectilesShot, projs[projectilesShot]->dx, projs[projectilesShot]->dy);
	
	projectilesShot++;
	if(projectilesShot >= NUM_PROJECTILES)
	  projectilesShot = 0;
      }
    }

    for(int i = 0; i < NUM_PROJECTILES; i++) {
      if(checkCollision(projs[i]->mBox, camera) && projs[i]->dx != 0 && projs[i]->dy != 0) {
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
	gTexture->render(projs[i]->mBox.x - projs[i]->mBox.w/3 - camera.x, projs[i]->mBox.y - projs[i]->mBox.h/3 - camera.y, NULL, projs[i]->angle);
        projs[i]->checkDiePlus(hildegarde);
      }
    }
    projectileTicks++;
    break;
  case troubadourID:  //Saucer enemy ID
    //difficulty = 2; // delete
    actualIntv = number;

      if(difficulty == 0)
	actualIntv = number;
      else if(difficulty == 1)
	actualIntv = number/1.5;
      else if(difficulty == 2)
	actualIntv = number/2;

    if(projectileTicks % actualIntv == 0) {
        projs[projectilesShot]->horizontalOsc = horizontalOsc;
        projs[projectilesShot]->posX = defaultPosX;
	projs[projectilesShot]->posY = defaultPosY;
	projs[projectilesShot]->defaultPosX = defaultPosX;
	projs[projectilesShot]->defaultPosY = defaultPosY;
	projs[projectilesShot]->mBox.w = mBox.w;
	projs[projectilesShot]->mBox.h = mBox.h;
	projs[projectilesShot]->mBox.x = projs[projectilesShot]->posX;
	projs[projectilesShot]->mBox.y = projs[projectilesShot]->posY;
	if(projectileTicks >= 120)
	  projs[projectilesShot]->speed = 0.25;
	else
	  projs[projectilesShot]->speed = 0.5;
	if(horizontalOsc)
	  projs[projectilesShot]->speed = 0.25;
	projs[projectilesShot]->targetX = defaultPosX;
	projs[projectilesShot]->targetY = hildegarde->getY();
	projs[projectilesShot]->originalTargetX = projs[projectilesShot]->targetX;
	projs[projectilesShot]->originalTargetY = projs[projectilesShot]->targetY;
	projs[projectilesShot]->moveOscillate(projs[projectilesShot]->targetX, projs[projectilesShot]->targetY);
	
	projectilesShot++;
	if(projectilesShot >= NUM_PROJECTILES)
	  projectilesShot = 0;
    }
    for(int i = 0; i < NUM_PROJECTILES; i++) {
      bool bulletInBounds;
      if(!horizontalOsc)
	bulletInBounds = projs[i]->mBox.y < SCREEN_HEIGHT;
      else
	bulletInBounds = projs[i]->mBox.x < SCREEN_WIDTH;
      if(bulletInBounds && (projs[i]->dx != 0 || projs[i]->dy != 0)) {
	if(i % 2 == 0)
	  projs[i]->moveOscillate(projs[i]->targetX, projs[i]->targetY, true);
	else
	  projs[i]->moveOscillate(projs[i]->targetX, projs[i]->targetY, false);
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
	gTexture->render(projs[i]->mBox.x - projs[i]->mBox.w/3 - camera.x, projs[i]->mBox.y - projs[i]->mBox.h/3 - camera.y, NULL, projs[i]->angle);
        projs[i]->checkDiePlus(hildegarde);
      }
      //SDL_SetRenderDrawColor(gRenderer, 255, 50, 0, 255);
      //SDL_Rect box = projs[i]->mBox;
      //SDL_RenderFillRect(gRenderer, &box);
    }
    projectileTicks++;
    break;
  case bohemondID:
    actualIntv = number;
    //difficulty = 2;
    
    if(difficulty == 0)
      actualIntv = number*1.5;
    else if(difficulty == 1)
      actualIntv = number*1.25;
    else if(difficulty == 2)
      actualIntv = number;

    if(projectileTicks / actualIntv >= NUM_PROJECTILES)
      projectileTicks = 0;

    if(projectileTicks % actualIntv == 0 || shootBool) {
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
	projs[projectilesShot]->targetX = rand()%(projs[projectilesShot]->mBox.x*2) - projs[projectilesShot]->mBox.x;
	projs[projectilesShot]->targetY = rand()%(SCREEN_HEIGHT/2);
	projs[projectilesShot]->speed = 5.0+(i/5.0)*spd;
	projs[projectilesShot]->moveGravityBullet = 1;	

	projectilesShot++;
	if(projectilesShot >= NUM_PROJECTILES)
	  projectilesShot = 0;
      }
    }

    for(int i = 0; i < NUM_PROJECTILES; i++) {
      if(checkCollision(projs[i]->mBox, camera)) {
	if(projs[i]->moveGravityBullet) 
	  projs[i]->moveGravity(projs[i]->targetX, projs[i]->targetY, 0.1);
	projs[i]->posX += projs[i]->dx;
	projs[i]->posY += projs[i]->dy;
	projs[i]->mBox.x = projs[i]->posX;
	projs[i]->mBox.y = projs[i]->posY;
	projs[i]->angle = projs[i]->getAngle(projs[i]->posX + projs[i]->dx, projs[i]->posY + projs[i]->dy);
	//projs[i]->gravityTicks++;
	
	if(rotate) {
	  projs[i]->angle += 5.0;
	  if(projs[i]->angle == 360)
	    projs[i]->angle = 0.0;
	}

	if(projectileIsLong) {
	  projs[i]->setLongProjBox();
	}
	
      } else {
	renewProj(i);
      }
      if(projs[i]->dx != 0.0 || projs[i]->dy != 0.0) {
        gTexture->render(projs[i]->mBox.x - spriteWidth/2 + 2 - camera.x, projs[i]->mBox.y - spriteHeight/2 - camera.y, NULL, projs[i]->angle);
        projs[i]->checkDiePlus(hildegarde);
	SDL_SetRenderDrawColor(gRenderer, 255, 50, 0, 255);
	SDL_RenderFillRect(gRenderer, &projs[i]->mBox);
	SDL_RenderFillRect(gRenderer, &projs[i]->mBox1);
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
      gTexture->render(projs[i]->mBox.x - projs[i]->mBox.w/3 - camera.x, projs[i]->mBox.y - projs[i]->mBox.h/3 - camera.y, NULL, angle);
      //		showBox[i] = projs[i]->getBox();
    } 
    //printf("%i/%i/%b/%i/%i/%i/%i\n", projs[i]->dx, projs[i]->dy, checkCollision(projs[i]->mBox, camera), hildegarde->getBox()->x, hildegarde->getBox()->y, projs[i]->targetX, projs[i]->targetY);
  }
  projectileTicks++;
  //SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
  //	for(int i = 0; i < NUM_PROJECTILES; i++)
  //	SDL_RenderFillRect(gRenderer, &showBox[i]);
}

void Projectile::shootEnemy3(double x, double y, Chara* hildegarde, enemyIDEnum enemyID, double velX, double spd, double gravityForce, bool rotate, int number) {
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
      projs[projectileTicks/actualIntv]->speed = spd;
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
	gTexture->render(projs[i]->mBox.x - projs[i]->mBox.w/3 - camera.x, projs[i]->mBox.y - projs[i]->mBox.h/3 - camera.y, NULL, angle);
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
	gTexture->render(projs[i]->mBox.x - projs[i]->mBox.w/3 - camera.x, projs[i]->mBox.y - projs[i]->mBox.h/3 - camera.y, NULL, angle);
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
  case hyacintheID:
    if(difficulty == 0)
      actualIntv = 8;
    else if(difficulty == 1)
      actualIntv = 4;
    else if(difficulty == 2)
      actualIntv = 2;
    if(projectileTicks / actualIntv >= NUM_PROJECTILES)
      projectileTicks = 0;

    gravityTicks++;

    if(projectileTicks % actualIntv == 0 && (projs[projectileTicks/actualIntv]->dx == 0.0 && projs[projectileTicks/actualIntv]->dy == 0.0)) {
      projs[projectileTicks/actualIntv]->posX = defaultPosX; projs[projectileTicks/actualIntv]->posY = defaultPosY;
      projs[projectileTicks/actualIntv]->defaultPosX = defaultPosX; projs[projectileTicks/actualIntv]->defaultPosY = defaultPosY;
      projs[projectileTicks/actualIntv]->mBox.x = posX; projs[projectileTicks/actualIntv]->mBox.y = posY;
      projs[projectileTicks/actualIntv]->targetX = rand()%SCREEN_WIDTH; projs[projectileTicks/actualIntv]->targetY = SCREEN_HEIGHT;
      projs[projectileTicks/actualIntv]->speed = speed;
      projs[projectileTicks/actualIntv]->mBox.w = mBox.w;
      projs[projectileTicks/actualIntv]->mBox.h = mBox.h;
      projs[projectileTicks/actualIntv]->moveGravityBullet = 1;
    }
    for(int i = 0; i < NUM_PROJECTILES; i++) {
      if(checkCollision(projs[i]->mBox, camera)) {
	if(projs[i]->moveGravityBullet)
	  projs[i]->moveGravity(projs[i]->targetX, projs[i]->targetY, gravityForce);
	projs[i]->posX += velX;
	projs[i]->posY += projs[i]->dy - 1;
	projs[i]->mBox.x = projs[i]->posX;
	projs[i]->mBox.y = projs[i]->posY;

	if(rotate) {
	  projs[i]->angle += 5.0;
	  if(projs[i]->angle == 360)
	    projs[i]->angle = 0.0;
	}
		
      } else {
	projs[i]->posX = defaultPosX;
	projs[i]->posY = defaultPosY;
	projs[i]->mBox.x = projs[i]->posX;
	projs[i]->mBox.y = projs[i]->posY;
	projs[i]->dx = 0.0; projs[i]->dy = 0.0;
	projs[i]->shotBullet = 0; projs[i]->moveGravityBullet = 0;
      }
      if(projs[i]->dx != 0.0 || projs[i]->dy != 0.0) {
	gTexture->render(projs[i]->mBox.x - projs[i]->mBox.w/3 - camera.x, projs[i]->mBox.y - projs[i]->mBox.h/3 - camera.y, NULL, projs[i]->angle);
	projs[i]->checkDiePlus(hildegarde);
      } 
    }
    projectileTicks++;
    break;
  case troubadourID:
    if(difficulty == 0)
      actualIntv = number;
    else if(difficulty == 1)
      actualIntv = number-2;
    else if(difficulty == 2)
      actualIntv = number-4;
    if(projectileTicks / actualIntv >= NUM_PROJECTILES)
      projectileTicks = 0;
    //printf("%i/%i/%g/%g/%b\n", projectileTicks/actualIntv, projectileTicks%actualIntv, projs[projectileTicks/actualIntv]->dx, projs[projectileTicks/actualIntv]->dy, projs[projectileTicks/actualIntv]->shotBullet);
    gravityTicks++;

    if(projectileTicks % actualIntv == 0 && (projs[projectileTicks/actualIntv]->dx == 0.0 && projs[projectileTicks/actualIntv]->dy == 0.0)) {
      projs[projectileTicks/actualIntv]->bouncesOffScreen = 0;
      projs[projectileTicks/actualIntv]->posX = defaultPosX; projs[projectileTicks/actualIntv]->posY = defaultPosY;
      projs[projectileTicks/actualIntv]->defaultPosX = defaultPosX; projs[projectileTicks/actualIntv]->defaultPosY = defaultPosY;
      projs[projectileTicks/actualIntv]->mBox.x = posX; projs[projectileTicks/actualIntv]->mBox.y = posY;
      projs[projectileTicks/actualIntv]->targetX = rand()%SCREEN_WIDTH; projs[projectileTicks/actualIntv]->targetY = rand()%(SCREEN_HEIGHT/4);
      projs[projectileTicks/actualIntv]->speed = spd;
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
	if(rotate) {
	  projs[i]->angle += 5.0;
	  if(projs[i]->angle == 360)
	    projs[i]->angle = 0.0;
	}
	if(projs[i]->bouncesOffScreen < 2) {
	  if(projs[i]->mBox.x - spriteWidth/2 <= camera.x || projs[i]->mBox.x + spriteWidth >= camera.w) {
	    projs[i]->dx = -(projs[i]->dx);
	    projs[i]->posX += projs[i]->dx;
	    projs[i]->mBox.x = projs[i]->posX;
	    projs[i]->bouncesOffScreen++;
	  }
	  if(projs[i]->mBox.y - spriteWidth/2 <= camera.y || projs[i]->mBox.y + spriteHeight >= camera.h) {
	    projs[i]->dy = -(projs[i]->dy);
	    projs[i]->posY += projs[i]->dy;
	    projs[i]->mBox.y = projs[i]->posY;
	    projs[i]->bouncesOffScreen++;
	  }
	}
      } else {
	renewProj(i);
      }
      if(projs[i]->dx != 0.0 || projs[i]->dy != 0.0) {
	gTexture->render(projs[i]->mBox.x - projs[i]->mBox.w/3 - camera.x, projs[i]->mBox.y - projs[i]->mBox.h/3 - camera.y, NULL, angle);
	projs[i]->checkDiePlus(hildegarde);
	//		showBox[i] = projs[i]->getBox();
      } 
      //printf("%i/%i/%b/%i/%i/%i/%i\n", projs[i]->targetX, projs[i]->targetY);
    }
    projectileTicks++;
    //SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
    //	for(int i = 0; i < NUM_PROJECTILES; i++)
    //	SDL_RenderFillRect(gRenderer, &showBox[i]);
    break;
  case bohemondID:
    actualIntv = 3;
    if(projectileTicks / actualIntv >= NUM_PROJECTILES)
      projectileTicks = 0;
    //printf("%i/%i/%g/%g/%b\n", projectileTicks/actualIntv, projectileTicks%actualIntv, projs[projectileTicks/actualIntv]->dx, projs[projectileTicks/actualIntv]->dy, projs[projectileTicks/actualIntv]->shotBullet);
    gravityTicks++;

    if(projectileTicks % actualIntv == 0 && (projs[projectileTicks/actualIntv]->dx == 0.0 && projs[projectileTicks/actualIntv]->dy == 0.0)) {
      projs[projectileTicks/actualIntv]->posX = defaultPosX; projs[projectileTicks/actualIntv]->posY = defaultPosY;
      projs[projectileTicks/actualIntv]->defaultPosX = defaultPosX; projs[projectileTicks/actualIntv]->defaultPosY = defaultPosY;
      projs[projectileTicks/actualIntv]->mBox.x = posX; projs[projectileTicks/actualIntv]->mBox.y = posY;
      projs[projectileTicks/actualIntv]->targetX = rand()%SCREEN_WIDTH; projs[projectileTicks/actualIntv]->targetY = rand()%(SCREEN_HEIGHT/4);
      projs[projectileTicks/actualIntv]->speed = spd*1.1;
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
	projs[i]->angle = projs[i]->getAngle(projs[i]->posX + projs[i]->dx, projs[i]->posY + projs[i]->dy);
	
	if(projectileIsLong)
	  projs[i]->setLongProjBox();
	
      } else {
	renewProj(i);
      }
      if(projs[i]->dx != 0.0 || projs[i]->dy != 0.0) {
	gTexture->render(projs[i]->mBox.x - spriteWidth/2 + 2 - camera.x, projs[i]->mBox.y - spriteHeight/2 - camera.y, NULL, projs[i]->angle);
	SDL_SetRenderDrawColor(gRenderer, 255, 50, 0, 255);
	SDL_RenderFillRect(gRenderer, &projs[i]->mBox);
	SDL_RenderFillRect(gRenderer, &projs[i]->mBox1);
      } 
      //printf("%i/%i/%b/%i/%i/%i/%i\n", projs[i]->targetX, projs[i]->targetY);
    }
    projectileTicks++;
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
	     gTexture->render(projs[i]->mBox.x - projs[i]->mBox.w/3 - camera.x, projs[i]->mBox.y - projs[i]->mBox.h/3 - camera.y, NULL);
	   } 
	 }
	 //printf("%i/%i/%b/%i/%i/%i/%i\n", projs[i]->dx, projs[i]->dy, checkCollision(projs[i]->mBox, camera), hildegarde->getBox()->x, hildegarde->getBox()->y, projs[i]->targetX, projs[i]->targetY);
	 projectileTicks++;
	 //printf("%i/%i/%i\n", shootAttack4Rand, projs[0]->targetX, shootTicks);
	 break;
  case saucerID:
    projs[0]->mBox.x = x;
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
	     gTexture->render(projs[i]->mBox.x - mBox.w/2 - camera.x, projs[i]->mBox.y - camera.y, NULL, angle);
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
  case troubadourID:
    if(projectileTicks > 60) {
      if(projectileTicks >= 70) {
	projectileTicks = 0;
      }
      defaultPosX = x; defaultPosY = y;
      projs[0]->posX = defaultPosX;
      projs[0]->posY = defaultPosY;
      projs[0]->defaultPosX = defaultPosX;
      projs[0]->defaultPosY = defaultPosY;
      projs[0]->mBox.w = mBox.w;
      projs[0]->mBox.h = mBox.h;
      projs[0]->mBox.x = projs[0]->posX;
      projs[0]->mBox.y = projs[0]->posY;
      projs[0]->targetX = hildegarde->getX();
      projs[0]->targetY = hildegarde->getY();
      projs[0]->angle = projs[0]->getAngle(projs[0]->targetX, projs[0]->targetY);
      printf("%f %f %i %i\n", projs[0]->dx, projs[0]->dy, projs[0]->targetX, projs[0]->targetY);
	     
      for(int i = 0; i < NUM_PROJECTILES; i++) {
	projs[0]->moveToXY(projs[0]->targetX, projs[0]->targetY);
	projs[0]->mBox.x += projs[0]->dx;
	projs[0]->mBox.y += projs[0]->dy;
	projs[i]->mBox = projs[0]->mBox;
	projs[i]->angle = projs[0]->angle;
      }
      //SDL_SetRenderDrawColor(gRenderer, 255, 50, 0, 255);
      for(int i = 0; i < NUM_PROJECTILES; i++) {
	gTexture->render(projs[i]->mBox.x - mBox.w/2 - camera.x, projs[i]->mBox.y - camera.y, NULL, projs[i]->angle);
	//SDL_RenderFillRect(gRenderer, &projs[i]->mBox);
	if(checkCollision(projs[i]->mBox, hildegarde->getBox()))
	  hildegarde->death = 1;
	//printf("%i, %i, %i, %i\n", projs[i]->mBox->x, projs[i]->mBox->y, projs[i]->mBox->w, projs[i]->mBox->h);
      }
    } else {
      for(int i = 0; i < NUM_PROJECTILES; i++) {
	projs[i]->clearProjectilesPlus();
      }
    }
    projectileTicks++;
    break;
  }
}


void Projectile::shootEnemy5(double x, double y, Chara* hildegarde, enemyIDEnum enemyID, int number, double sectionAngle, double startingAngle, int batch, double spd, bool rotate) {
  defaultPosX = x; defaultPosY = y;

  if(clearBullets)
    destroyProjs(NUM_PROJECTILES);
  createProjs(NUM_PROJECTILES);
  
  switch(enemyID) {
  case conradID: //Conrad
    break;
  case saucerID:
    break;
  case hyacintheID:
    actualIntv = number;

    if(screenShake) {
      disableScreenShakeTicks++;
      if(disableScreenShakeTicks >= 30) {
	screenShake = 0;
	disableScreenShakeTicks = 0;
      }
    }

    if(projectileTicks % actualIntv == 0) {
      projectileTicks = 1;
      int squareRoot = sqrt(batch);
      for(int i = 0; i < batch; i++) {
	if(i % squareRoot == 0) {
	  projs[projectilesShot]->mBox.w = mBox.w;
	  projs[projectilesShot]->mBox.h = mBox.h;
	  projs[projectilesShot]->posX = x;
	  projs[projectilesShot]->posY = y + spriteHeight*(i/squareRoot);
	  projs[projectilesShot]->defaultPosX = defaultPosX;
	  projs[projectilesShot]->defaultPosY = defaultPosY;
	  projs[projectilesShot]->mBox.x = projs[projectilesShot]->posX;
	  projs[projectilesShot]->mBox.y = projs[projectilesShot]->posY;
	  projs[projectilesShot]->targetX = hildegarde->getX() - spriteWidth*squareRoot/2;
	  projs[projectilesShot]->targetY = hildegarde->getY() - spriteHeight*squareRoot/2;
	  projs[projectilesShot]->speed = spd;
	  projs[projectilesShot]->moveToXY(projs[projectilesShot]->targetX, projs[projectilesShot]->targetY);
	  projs[projectilesShot]->shotBullet = 0;
	  for(int j = 0; j < squareRoot; j++) {
	    if(projectilesShot+j <= batch) {
	      projs[projectilesShot+j]->defaultPosX = projs[projectilesShot]->defaultPosX;
	      projs[projectilesShot+j]->defaultPosY = projs[projectilesShot]->defaultPosY;
	      projs[projectilesShot+j]->posX = projs[projectilesShot]->posX + spriteWidth*j;
	      projs[projectilesShot+j]->posY = projs[projectilesShot]->posY;
	      projs[projectilesShot+j]->mBox.x = projs[projectilesShot+j]->posX;
	      projs[projectilesShot+j]->mBox.y = projs[projectilesShot+j]->posY;
	      projs[projectilesShot+j]->dx = projs[0]->dx;
	      projs[projectilesShot+j]->dy = projs[0]->dy;
	    }
	  }
	}
	
	projectilesShot++;
	if(projectilesShot >= batch)
	  projectilesShot = 0;
      }
    }
    
    for(int i = 0; i < batch; i++) {
      if(checkCollision(projs[i]->mBox, camera) && projs[i]->dx != 0 && projs[i]->dy != 0) {
	projs[i]->posX += projs[i]->dx;
	projs[i]->posY += projs[i]->dy;
	projs[i]->mBox.x = projs[i]->posX;
	projs[i]->mBox.y = projs[i]->posY;

	if((projs[i]->mBox.x + spriteWidth > SCREEN_WIDTH || projs[i]->mBox.x - spriteWidth/2 < camera.x || projs[i]->mBox.y + spriteHeight > SCREEN_HEIGHT || projs[i]->mBox.y - spriteHeight/2 < camera.y) && !projs[i]->explode) {
	  for(int j = 0; j < batch; j++) {
	    projs[j]->explode = 1;
	  }
	  screenShake = 1;
	}
	
	if(projs[i]->explode) {
	  projs[i]->moveGravity(rand()%SCREEN_WIDTH, rand()%(SCREEN_HEIGHT - 500), 0.05, true);
	}
	
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
	gTexture->render(projs[i]->mBox.x - projs[i]->mBox.w/3 - camera.x, projs[i]->mBox.y - projs[i]->mBox.h/3 - camera.y, NULL, projs[i]->angle);
	projs[i]->checkDiePlus(hildegarde);
      }
    }
    projectileTicks++;
    break;
  case troubadourID: //Saucer enemy ID
    actualIntv = number;
    //difficulty = 2;
    
    if(difficulty == 0)
      actualIntv = number*1.5;
    else if(difficulty == 1)
      actualIntv = number*1.25;
    else if(difficulty == 2)
      actualIntv = number;

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
	  projs[projectilesShot]->targetX = projs[projectilesShot]->posX - 100;
	  if(i == batch-1)
	    shotBatch = 1;
	}
	else {
	  projs[projectilesShot]->targetX = projs[projectilesShot]->posX + 100;
	  if(i == batch-1)
	    shotBatch = 0;
	}
	//projs[projectilesShot]->targetX = projs[projectilesShot]->posX - 200;
	projs[projectilesShot]->targetY = projs[projectilesShot]->posY - 100;
	projs[projectilesShot]->speed = 5.0+(i/5.0)*spd;
	projs[projectilesShot]->moveToXY(projs[projectilesShot]->targetX, projs[projectilesShot]->targetY);
	//printf("%f, %i, %f, %f\n", projectileAngle, projectilesShot, projs[projectilesShot]->dx, projs[projectilesShot]->dy);
	
	projectilesShot++;
	if(projectilesShot >= NUM_PROJECTILES)
	  projectilesShot = 0;
      }
    }

    for(int i = 0; i < NUM_PROJECTILES; i++) {
      if(checkCollision(projs[i]->mBox, camera) && projs[i]->dx != 0 && projs[i]->dy != 0) {
	projs[i]->posX += projs[i]->dx;
	projs[i]->posY += projs[i]->dy;
	projs[i]->mBox.x = projs[i]->posX;
	projs[i]->mBox.y = projs[i]->posY;
	
	if(rotate) {
	  projs[i]->angle += 5.0;
	  if(projs[i]->angle == 360)
	    projs[i]->angle = 0.0;
	}

	if(projs[i]->bouncesOffScreen < 5) {
	  if(projs[i]->mBox.x - spriteWidth/2 <= camera.x || projs[i]->mBox.x + spriteWidth >= camera.w) {
	    projs[i]->dx = -(projs[i]->dx);
	    projs[i]->posX += projs[i]->dx;
	    projs[i]->mBox.x = projs[i]->posX;
	    projs[i]->bouncesOffScreen++;
	  }
	  if(projs[i]->mBox.y - spriteWidth/2 <= camera.y || projs[i]->mBox.y + spriteHeight >= camera.h) {
	    projs[i]->dy = -(projs[i]->dy);
	    projs[i]->posY += projs[i]->dy;
	    projs[i]->mBox.y = projs[i]->posY;
	    projs[i]->bouncesOffScreen++;
	  }
	}
	
      } else {
	renewProj(i);
	//projs[i]->clearProjectilesPlus();
      }
      if(projs[i]->dx != 0 || projs[i]->dy != 0) {
	gTexture->render(projs[i]->mBox.x - projs[i]->mBox.w/3 - camera.x, projs[i]->mBox.y - projs[i]->mBox.h/3 - camera.y, NULL, projs[i]->angle);
        projs[i]->checkDiePlus(hildegarde);
      }
    }
    projectileTicks++;
    break;
  }
}

int deaths;
void Projectile::checkDiePlus(Chara* hildegarde) {
  if(checkCollision(hildegarde->getBox(), mBox) ||
     (checkCollision(hildegarde->getBox(), mBox1) && projectileIsLong)
     && !hildegarde->death) {
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
  mBox1 = mBox;
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
  explode = 0; disableScreenShakeTicks = 0;
  counter = 0; oscillationTicks = 0;
  switchOsc = 0; firstOsc = 1;
  bouncesOffScreen = 0; horizontalOsc = 0;
}

void Projectile::createProjs(int num) {
  if(!createdProjs) {
    for(int i = 0; i < num; i++) {
      projs[i] = new Projectile();
      projs[i]->setProj(mBox, posX, posY, speed, projectileIsLong);
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
  projs[num]->setProj(mBox, posX, posY, speed, projectileIsLong);
}

void Projectile::setLongProjBox() {
  double otherPosX, otherPosY;
  otherPosX = posX;
  otherPosY = posY;
  mBox1 = mBox;
  if(dx >= 1 || dx <= -1) {
    if(!(angle > 75 && angle < 105)) {
      while(abs(otherPosX - posX) < mBox.w) 
	otherPosX += dx;
    }
  } else if(!(angle > 75 && angle < 105)) {
        otherPosX += mBox.w*dx;
  }
  
  if(dy >= 1 || dy <= -1) {
    if(!(angle < 45) && !(angle > 135)) {
      while(abs(otherPosY - posY) < mBox.h) 
	otherPosY += dy;
    }
  } else if(!(angle < 45) && !(angle > 135)) {
    otherPosY += mBox.h*dy;
  }
	  
  mBox1.x = otherPosX;
  mBox1.y = otherPosY;
}
