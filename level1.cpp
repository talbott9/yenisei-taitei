#include "collision.cpp"
#include "louis.cpp"
#include "background.cpp"
#include "enemy.cpp"
#include "projectiles.cpp"

// This file only exists because when I started programming this game
// I didn't know how includes work. Might clean up later, but it works for now

const int LEVEL_WIDTH = 1290;
const int LEVEL_HEIGHT = 960;

void clearAllProjectiles(bool clearPlayerProjectiles = false);

bool loadMedia() {
	bool success = true;

	if(!gEnemy1Texture.loadFromFile("resources/enemies/enemy1.png"))
		success = false;
	if(!gSaucerTexture.loadFromFile("resources/enemies/saucer.png"))
		success = false;
	if(!gLevel1Floor.loadFromFile("resources/floor_tiles/level1.png"))
		success = false;
	if(!gLevel1Background.loadFromFile("resources/floor_tiles/level1background.png"))
		success = false;
	if(!gBullet1.loadFromFile("resources/projectiles/bullet1.png"))
		success = false;
	if(!gBullet2.loadFromFile("resources/projectiles/bullet2.png"))
		success = false;
	if(!gSaucerBullet.loadFromFile("resources/projectiles/saucerbullet.png"))
		success = false;
	if(!gStarBullet1.loadFromFile("resources/projectiles/starbullet1.png"))
		success = false;
	if(!gYeniseiTexture.loadFromFile("resources/yenisei/yeniseisprites.png"))	{
		printf( "Failed to load texture!\n" );
		success = false;
	}
	if(!gHGArrow1Texture.loadFromFile("resources/projectiles/HGArrow1.png"))
		success = false;
	if(!gHildegardeTexture.loadFromFile("resources/hildegarde/hildegardesprites.png"))
		success = false;
	if(!gTuvaMap.loadFromFile("resources/floor_tiles/tuvamap.png")) {
	       printf("Failed to load map\n");
	       success = false; 
	}      
	if(!gGameOverScreen.loadFromFile("resources/floor_tiles/gameoverscreen.png"))
		success = false;
	if(!gGameOverScreen2.loadFromFile("resources/floor_tiles/gameoverscreen2.png"))
		success = false;
	TTF_Font* gFont = TTF_OpenFont("resources/fonts/font1.ttf", 20);
	if(gFont == NULL) {
		printf("Failed to load gFont! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
	TTF_Font* gBattleFont= TTF_OpenFont("resources/fonts/battlefont.ttf", 20);
	TTF_Font* gBattleFontSmall = gBattleFont;
	if(gBattleFont == NULL) {
		printf("Failed to load gBattleFont! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}


	else
	{
		gSpriteClips[ 0 ].x =   0;  gSpriteClips[ 4 ].x =   600; gSpriteClips[ 8 ].x =  1200; //gSpriteClips[ 12 ].x =   0;
		gSpriteClips[ 0 ].y =   0;  gSpriteClips[ 4 ].y =  0;    gSpriteClips[ 8 ].y = 0; //gSpriteClips[ 12 ].y = 150;
		gSpriteClips[ 0 ].w =  150; gSpriteClips[ 4 ].w =  150;  gSpriteClips[ 8 ].w =  150; //gSpriteClips[ 12 ].w =  27;
		gSpriteClips[ 0 ].h =  103; gSpriteClips[ 4 ].h =  103;  gSpriteClips[ 8 ].h =  103; //gSpriteClips[ 12 ].h =  50;

		gSpriteClips[ 1 ].x =  150; gSpriteClips[ 5 ].x =  750;  gSpriteClips[ 9 ].x =  1350; //gSpriteClips[ 13 ].x =  27;
		gSpriteClips[ 1 ].y =   0;  gSpriteClips[ 5 ].y =  0;    gSpriteClips[ 9 ].y = 0; //gSpriteClips[ 13 ].y = 150;
		gSpriteClips[ 1 ].w =  150; gSpriteClips[ 5 ].w =  150;  gSpriteClips[ 9 ].w =  150; //gSpriteClips[ 13 ].w =  27;
		gSpriteClips[ 1 ].h =  103; gSpriteClips[ 5 ].h =  103;  gSpriteClips[ 9 ].h =  103; //gSpriteClips[ 13 ].h =  50;

		gSpriteClips[ 2 ].x =  300; gSpriteClips[ 6 ].x =  900;  gSpriteClips[ 10 ].x =  1500; //gSpriteClips[ 14 ].x =  54; 
		gSpriteClips[ 2 ].y =   0;  gSpriteClips[ 6 ].y =  0;    gSpriteClips[ 10 ].y = 0; //gSpriteClips[ 14 ].y = 150; 
		gSpriteClips[ 2 ].w =  150; gSpriteClips[ 6 ].w =  150;  gSpriteClips[ 10 ].w =  150; //gSpriteClips[ 14 ].w =  27;
		gSpriteClips[ 2 ].h =  103; gSpriteClips[ 6 ].h =  103;  gSpriteClips[ 10 ].h =  103; //gSpriteClips[ 14 ].h =  50;

		gSpriteClips[ 3 ].x =  450; gSpriteClips[ 7 ].x =  1050;// gSpriteClips[ 8 ].x =  81; gSpriteClips[ 15 ].x =  81;
		gSpriteClips[ 3 ].y =   0;  gSpriteClips[ 7 ].y =  0; //gSpriteClips[ 8 ].y = 100; gSpriteClips[ 15 ].y = 150;
		gSpriteClips[ 3 ].w =  150; gSpriteClips[ 7 ].w =  150; //gSpriteClips[ 8 ].w =  27; gSpriteClips[ 15 ].w =  27;
		gSpriteClips[ 3 ].h =  103; gSpriteClips[ 7 ].h =  103; //gSpriteClips[ 8 ].h =  50; gSpriteClips[ 15 ].h =  50;

		//Hildegarde
		gHGSpriteClips[ 0 ].x =   0;  gHGSpriteClips[ 4 ].x =  240; //gHGSpriteClips[ 8 ].x =  1200; //gHGSpriteClips[ 12 ].x =   0;
		gHGSpriteClips[ 0 ].y =   0;  gHGSpriteClips[ 4 ].y =  0;    //gHGSpriteClips[ 8 ].y = 0; //gHGSpriteClips[ 12 ].y = 150;
		gHGSpriteClips[ 0 ].w =  60;  gHGSpriteClips[ 4 ].w =  60;  //gHGSpriteClips[ 8 ].w =  150; //gHGSpriteClips[ 12 ].w =  27;
		gHGSpriteClips[ 0 ].h =  72;  gHGSpriteClips[ 4 ].h =  72; // gHGSpriteClips[ 8 ].h =  103; //gHGSpriteClips[ 12 ].h =  50;

		gHGSpriteClips[ 1 ].x =  60; gHGSpriteClips[ 5 ].x =  300;  //gHGSpriteClips[ 9 ].x =  1350; //gHGSpriteClips[ 13 ].x =  27;
		gHGSpriteClips[ 1 ].y =   0;  gHGSpriteClips[ 5 ].y =  0;   // gHGSpriteClips[ 9 ].y = 0; //gHGSpriteClips[ 13 ].y = 150;
		gHGSpriteClips[ 1 ].w =  60;  gHGSpriteClips[ 5 ].w =  60;  //gHGSpriteClips[ 9 ].w =  150; //gHGSpriteClips[ 13 ].w =  27;
		gHGSpriteClips[ 1 ].h =  72;  gHGSpriteClips[ 5 ].h =  72;  //gHGSpriteClips[ 9 ].h =  103; //gHGSpriteClips[ 13 ].h =  50;

		gHGSpriteClips[ 2 ].x =  120; gHGSpriteClips[ 6 ].x =  360;  //gHGSpriteClips[ 10 ].x =  1500; //gHGSpriteClips[ 14 ].x =  54; 
		gHGSpriteClips[ 2 ].y =   0;  gHGSpriteClips[ 6 ].y =  0;    //gHGSpriteClips[ 10 ].y = 0; //gHGSpriteClips[ 14 ].y = 150; 
		gHGSpriteClips[ 2 ].w =  60;  gHGSpriteClips[ 6 ].w =  60;  //gHGSpriteClips[ 10 ].w =  150; //gHGSpriteClips[ 14 ].w =  27;
		gHGSpriteClips[ 2 ].h =  72;  gHGSpriteClips[ 6 ].h =  72;  //gHGSpriteClips[ 10 ].h =  103; //gHGSpriteClips[ 14 ].h =  50;

		gHGSpriteClips[ 3 ].x =  180; 
		gHGSpriteClips[ 3 ].y =   0;  
		gHGSpriteClips[ 3 ].w =  60; 
		gHGSpriteClips[ 3 ].h =  72;
	}
	return success;
}

void Enemy::reset() {
  lastPattern = pattern;
  enemyDead = 0;
  randX = rand()%(SCREEN_WIDTH - mBox.w) + mBox.w;
  randY = rand()%(SCREEN_HEIGHT - 300);
  while(pattern == lastPattern)
    pattern = rand()%4;
  changeMove = 1; actionTicks = 0;
  renderAngle = 0;
  actualScore += 1000;
  if(actualScore == 3000)
    difficulty++;
  else if(actualScore == 6000)
    difficulty++;
  mCurrentHitPoints = mMaxHitPoints;
  clearAllProjectiles();
}

void Enemy::doThings(Projectile* projectile1, Projectile* projectile2, Projectile* projectile3, Chara* hildegarde, Projectile* projectile4) {
  enemyIDGlobal = enemyID;
  gEnemyTexture->render(mBox.x, mBox.y, NULL, renderAngle);
  actionTicks++;
  pattern = 0;
  switch(enemyID) { // 0 - conrad, 1 - saucer
  case 0:
    switch(pattern) {
    case 0:
      if(!enemyDead) {
	if(difficulty == 0)
	  moveThreshold = 180;
	else if(difficulty == 1)
	  moveThreshold = 120;
	else
	  moveThreshold = 60;
	if(actionTicks % moveThreshold == 0) {
	  changeMove = 1;
	  randX = rand()%(SCREEN_WIDTH - mBox.w) + mBox.w;
	  randY = rand()%(SCREEN_HEIGHT - 300);
	}
	moveToXY(randX, randY, 6.0);
	projectile1->shootEnemy1(mBox.x, mBox.y + mBox.h/2, hildegarde);
	projectile1->checkDie(hildegarde);
      } else {
	dx = 0; dy = 0;
	renderAngle += 30.0;
	if(renderAngle >= 720) {
	  reset();
	  projectile1->destroyProjs(NUM_PROJECTILES);
	}
      }
      break;
    case 1:
      if(!enemyDead) {
	moveToXY(SCREEN_WIDTH/2 - mBox.w/2, 50, 6.0);
	projectile2->shootEnemy2(mBox.x, mBox.y + mBox.h/2, hildegarde); 
	projectile2->checkDie(hildegarde);
	projectile2->checkDie1(hildegarde);
      } else {
	dx = 0; dy = 0;
	renderAngle += 30.0;
	if(renderAngle >= 720) {
	  reset();
	  projectile2->destroyProjs(NUM_PROJECTILES);
	}
      }
      break;
    case 2:
      if(!enemyDead) {
	moveToXY(SCREEN_WIDTH/2 - mBox.w/2, SCREEN_HEIGHT/2, 6.0);
	projectile3->shootEnemy3(mBox.x, mBox.y + mBox.h/2, hildegarde);
	projectile3->checkDie(hildegarde);
      } else {
	dx = 0; dy = 0;
	renderAngle += 30.0;
	if(renderAngle >= 720) {
	  reset();
	  projectile3->destroyProjs(NUM_PROJECTILES);
	}
      } 
      break;
    default:
      if(!enemyDead) {
	moveToXY(SCREEN_WIDTH/2 - mBox.w/2, 50, 6.0);
	if(fabs(mBox.x - (SCREEN_WIDTH/2 - mBox.w/2)) < 100) {
	  projectile2->shootEnemy4(mBox.x, mBox.y + mBox.h/2, hildegarde);
	  projectile2->checkDie(hildegarde);
	  projectile2->checkDie(hildegarde);
	}
      } else {
	dx = 0; dy = 0;
	renderAngle += 30.0;
	if(renderAngle >= 720) {
	  reset();
	  projectile2->destroyProjs(NUM_PROJECTILES);
	}
      }
      break;
    }
  case 1: // Saucer
    switch(pattern) {
    case 0: // Rain and thunder
      if(!enemyDead) {
	moveThreshold = 60;
	if(actionTicks % moveThreshold == 0) {
	  changeMove = 1;
	  randY = rand()%(SCREEN_HEIGHT - 300);
	  randX = hildegarde->getBox().x - mBox.w/2;
	}
	moveToXY(randX, randY, 8.0);
	projectile1->shootEnemy4(mBox.x + 50, mBox.y + 20 + mBox.h/2, hildegarde);
	projectile2->shootEnemy3(rand()%SCREEN_WIDTH, 0, hildegarde);
      } else {
	dx = 0; dy = 0;
	renderAngle += 30.0;
	if(renderAngle >= 720) {
	  reset();
	  projectile1->destroyProjs(NUM_PROJECTILES);
	  projectile2->destroyProjs(NUM_PROJECTILES);
	}
      }
      break;
    case 1: // Sun and moon
      if(!enemyDead) {
	//useful pattern that I will probably use later
	/*moveThreshold = 90;
	if(actionTicks % moveThreshold == 0) {
	  changeMove = 1;
	  randY = rand()%(SCREEN_HEIGHT/5);
	  randX = hildegarde->getBox().x - mBox.w/2 - rand()%200 + rand()%200;
	  if(randX < 0)
	    randX = 0;
	  else if(randX > SCREEN_WIDTH - mBox.w)
	    randX = SCREEN_WIDTH - mBox.w;
	}*/
	moveToXY(SCREEN_WIDTH - mBox.w - 10, 10, 8.0);
        projectile2->shootEnemy0(0, 0, hildegarde, 12, 90.0, 9, 10.0);
	projectile3->shootEnemy0(mBox.x + mBox.w/2, mBox.y + mBox.h/2, hildegarde, 40, 360.0, 20);
	projectile4->shootEnemy0(rand()%SCREEN_WIDTH, rand()%200 + 50, hildegarde, 20, 360.0, 4, 8.0, true);
      } else {
	dx = 0; dy = 0;
	renderAngle += 30.0;
	if(renderAngle >= 720) {
	  reset();
	  projectile2->destroyProjs(NUM_PROJECTILES);
	  projectile3->destroyProjs(NUM_PROJECTILES);
	  projectile4->destroyProjs(NUM_PROJECTILES);
	}
      }
      break;
    }
    break;
  }
  //printf("%i/%i\n", randX, randY);
}

void Chara::shoot(Projectile* projectile, Enemy* enemy) {
  projectile->shootHG(mBox.x, mBox.y, enemy);
}

void clearAllProjectiles(bool clearPlayerProjectiles) {
  projectile2.clearProjectilesPlus();
  projectile3.clearProjectilesPlus();
  projectile4.clearProjectilesPlus();
  projectile5.clearProjectilesPlus();
  saucerProjectile.clearProjectilesPlus();
  if(clearPlayerProjectiles)
    projectileHG.clearProjectilesPlus();
}

void resetGame(Enemy* enemy, Chara* yenisei) {
  clearAllProjectiles(true);
  enemy->setPosXY(enemy->defaultPosX, enemy->defaultPosY);
  yenisei->setPos(yenisei->defaultPosX, yenisei->defaultPosY);
  yenisei->setVel(0, 0);
  enemy->setVel(0,0);
  enemy->restoreHP();
  enemy->pattern = rand()%3;
  enemy->changeMove = 1; enemy->actionTicks = 0;
  yenisei->accTicks = 0; yenisei->deathTicks = 0;
  yenisei->moved = 0; yenisei->didResetAnim = 0;
  yenisei->resetAnim = 0; HGAttacking = 0;
  actualScore = 0; score = 0;
  difficulty = 0; clearBullets = 1;
}
