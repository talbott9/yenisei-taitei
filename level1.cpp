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
	if(!gHyacintheTexture.loadFromFile("resources/enemies/hyacinthe.png"))
		success = false;
	if(!gTroubadourTexture.loadFromFile("resources/enemies/troubadour.png"))
		success = false;
	
	if(!gLevel1Floor.loadFromFile("resources/floor_tiles/level1.png"))
		success = false;
	if(!gForestFloor.loadFromFile("resources/floor_tiles/forestfloor.png"))
		success = false;
	if(!gLevel1Background.loadFromFile("resources/floor_tiles/level1background.png"))
		success = false;
	if(!gForestBackground.loadFromFile("resources/floor_tiles/forestbackground.png"))
		success = false;
	if(!gBullet1.loadFromFile("resources/projectiles/bullet1.png"))
		success = false;
	if(!gBullet2.loadFromFile("resources/projectiles/bullet2.png"))
		success = false;
	if(!gSaucerBullet.loadFromFile("resources/projectiles/saucerbullet.png"))
		success = false;
	if(!gStarBullet1.loadFromFile("resources/projectiles/starbullet1.png"))
		success = false;
	if(!gSnowflakeBullet.loadFromFile("resources/projectiles/snowflakebullet.png"))
		success = false;
	if(!gShardBullet.loadFromFile("resources/projectiles/shardbullet.png"))
		success = false;
	if(!gSoundBullet.loadFromFile("resources/projectiles/soundbullet.png"))
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
  deaths++;
  lastPattern = pattern;
  enemyDead = 0;
  randX = SCREEN_WIDTH/2 - mBox.w/2;
  randY = 50;
  while(pattern == lastPattern)
    pattern = rand()%4;
  changeMove = 1; 
  renderAngle = 0;
  actualScore += 10000/actionTicks;
  actionTicks = 0;
  /* if(actualScore == 3000)
    difficulty++;
  else if(actualScore == 6000)
  difficulty++;*/
  mMaxHitPoints = 100;
  mCurrentHitPoints = mMaxHitPoints;
  clearAllProjectiles();
  createdComps = 0; ready = 0;
  clear = 1;
  currentClip = &gEnemyClips[0];
  flipType = SDL_FLIP_NONE;
  screenShake = 0; slowDown = 0;
  slowValue = 1.0;
}

void Enemy::doThings(Projectile* projectile1, Projectile* projectile2, Projectile* projectile3, Projectile* projectile4, Chara* hildegarde, Chara* yenisei) {
  gEnemyTexture->render(mBox.x - camera.x, mBox.y - camera.y, currentClip, renderAngle, NULL, flipType);
  showTime();
  actionTicks++;
  switch(enemyID) { // 0 - conrad, 1 - saucer
  case conradID:
    switch(deaths) {
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
	projectile1->shootEnemy1(mBox.x, mBox.y + mBox.h/2, hildegarde, enemyID);
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
	projectile2->shootEnemy2(mBox.x, mBox.y + mBox.h/2, hildegarde, enemyID); 
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
	projectile3->shootEnemy3(mBox.x, mBox.y + mBox.h/2, hildegarde, enemyID);
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
	  projectile2->shootEnemy4(mBox.x, mBox.y + mBox.h/2, hildegarde, enemyID);
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
    break;
  case saucerID: // Saucer
    switch(deaths) {
      
    case 0:
      if(!enemyDead) {
	moveToXY(SCREEN_WIDTH/2 - mBox.w/2, 10, 8.0);
	
	if(actionTicks > 90)
	  projectile2->shootEnemy0(mBox.x + mBox.w/2, mBox.y + mBox.h/2, hildegarde, enemyID, 20, 30.0, 75.0, 3, 7.0, false, true);

	if(clearBullets) {
	  projectile2->destroyProjs(NUM_PROJECTILES);
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
   
    case 1: // Rain and thunder
      if(!enemyDead) {
	moveThreshold = 60;
	if(actionTicks % moveThreshold == 0) {
	  changeMove = 1;
	  randY = rand()%(SCREEN_HEIGHT - 300);
	  randX = hildegarde->getBox().x - mBox.w/2;
	}
	moveToXY(randX, randY, 8.0);
	projectile1->shootEnemy4(mBox.x + 50, mBox.y + 20 + mBox.h/2, hildegarde, enemyID);
	projectile2->shootEnemy3(rand()%SCREEN_WIDTH, 0, hildegarde, enemyID);

	if(clearBullets) {
	  projectile1->destroyProjs(NUM_PROJECTILES);
	  projectile2->destroyProjs(NUM_PROJECTILES);
	}
	
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
    case 2:
      if(!enemyDead) {
	if(actionTicks > 90) {
	  moveThreshold = 120;
	  if(actionTicks % moveThreshold == 0) {
	    changeMove = 1;
	    randY = rand()%(SCREEN_HEIGHT - 500);
	    randX = hildegarde->getBox().x - mBox.w/2;
	  }
	  moveToXY(randX, randY, 8.0);
	  projectile2->shootEnemy0(mBox.x + mBox.w/2, mBox.y + mBox.h/2, hildegarde, enemyID, 20, 30.0, 75.0, 3, 7.0, false, true);
	} else {
	  moveToXY(SCREEN_WIDTH/2 - mBox.w/2, 10, 8.0);
	}

	if(clearBullets) {
	  projectile2->destroyProjs(NUM_PROJECTILES);
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
    case 3: // Sun and moon
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
	
	if(actionTicks > 30)
	  projectile2->shootEnemy0(0, 0, hildegarde, enemyID, 12, 90.0, 0.0, 9, 10.0);
	if(actionTicks > 90)
	  projectile3->shootEnemy0(mBox.x + mBox.w/2, mBox.y + mBox.h/2, hildegarde, enemyID, 40, 360.0, 0.0, 20);

	if(actionTicks > 150)
	  projectile4->shootEnemy0(rand()%SCREEN_WIDTH, rand()%200 + 50, hildegarde, enemyID, 20, 360.0, 0.0, 4, 8.0, true);

	if(clearBullets) {
	  projectile2->destroyProjs(NUM_PROJECTILES);
	  projectile3->destroyProjs(NUM_PROJECTILES);
	  projectile4->destroyProjs(NUM_PROJECTILES);
	}
	
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
    case 4:
      if(!enemyDead) {
	if(actionTicks > 90) {
	  moveThreshold = 180;
	  if(actionTicks % moveThreshold == 0) {
	    changeMove = 1;
	    randY = 50;
	    if(mBox.x > SCREEN_WIDTH/2)
	      randX = 0;
	    else
	      randX = SCREEN_WIDTH-mBox.w;
	  }
	  moveToXY(randX, randY, 8.0);
	  projectile2->shootEnemy0(mBox.x + mBox.w/2, mBox.y + mBox.h/2, hildegarde, enemyID, 20, 30.0, 75.0, 3, 7.0, false, true);
	} else { 
	  moveToXY(SCREEN_WIDTH/2 - mBox.w/2, 10, 8.0);
	}
	if(clearBullets) {
	  projectile2->destroyProjs(NUM_PROJECTILES);
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
    case 5: //Abduction
      numberOfComps = 2;
      if(clearBullets) {
      }
      else if(!enemyDead) {
	if(clearComps)
	  destroyComps(numberOfComps);
	createComps(numberOfComps);
	
	moveToXY(SCREEN_WIDTH/2 - mBox.w/2, 10, 8.0);

	int goal0 = SCREEN_WIDTH/8;
	int goal1 = SCREEN_WIDTH - SCREEN_WIDTH/4;

	if(actionTicks > 90) {
	  projectile3->shootEnemy1(mBox.x + mBox.w/2, mBox.y + mBox.h/2, hildegarde, enemyID, 40, 360.0, 10, 1.0);
	  projectile4->shootEnemy0(companions[0]->mBox.x + companions[0]->mBox.w/2, companions[0]->mBox.y + companions[0]->mBox.h/2, hildegarde, companions[0]->enemyID, 10, 30.0, 75.0, 10, 10.0);
	  projectile2->shootEnemy0(companions[1]->mBox.x + companions[1]->mBox.w/2, companions[1]->mBox.y + companions[1]->mBox.h/2, hildegarde, companions[1]->enemyID, 10, 30.0, 75.0, 10, 10.0);
	} else {
	  companions[0]->moveToXY(goal0, 10, 15.0);
	  companions[1]->moveToXY(goal1, 10, 15.0);
	}

	if(clearBullets) {
	  projectile2->destroyProjs(NUM_PROJECTILES);
	  projectile3->destroyProjs(NUM_PROJECTILES);
	  projectile4->destroyProjs(NUM_PROJECTILES);
	  //clear = 0;
	}
	    

	for(int i = 0; i < numberOfComps; i++) {
	  gEnemyTexture->render(companions[i]->mBox.x, companions[i]->mBox.y, NULL);
	  //printf("%i, %i\n", companions[i]->mBox.w, companions[i]->mBox.h);
	}
      } else {
	dx = 0; dy = 0;
	renderAngle += 30.0;
	if(renderAngle >= 720) {
	  reset();
	  projectile2->destroyProjs(NUM_PROJECTILES);
	  projectile3->destroyProjs(NUM_PROJECTILES);
	  projectile4->destroyProjs(NUM_PROJECTILES);
	  destroyComps(numberOfComps);
	}
      }
      break;
    }
    break;
    //printf("%i/%i\n", randX, randY);
  case hyacintheID:
    
    if(dx != 0 || dy != 0) {
      currentClip = &gEnemyClips[1];
      if(dx < 0)
	flipType = SDL_FLIP_HORIZONTAL;
      else
	flipType = SDL_FLIP_NONE;
    }
    else {
      currentClip = &gEnemyClips[0];
      flipType = SDL_FLIP_NONE;
    }
    
    switch(deaths) {
    case 0:
      if(!enemyDead) {
	mMaxHitPoints = 50;
	moveThreshold = 60;
	if(actionTicks % moveThreshold == 0) {
	  changeMove = 1;
	  randY = rand()%(SCREEN_HEIGHT - 500);
	  if(hildegarde->getBox().x > SCREEN_WIDTH/2)
	    randX = rand()%(SCREEN_WIDTH/4);
	  else
	    randX = rand()%(SCREEN_WIDTH/4) + 3*SCREEN_WIDTH/4 - mBox.w;
	}
	moveToXY(randX, randY, 8.0);

	if(actionTicks > 60) {
	  projectile3->shootEnemy1(mBox.x + mBox.w/2, mBox.y + mBox.h/2, hildegarde, enemyID, 40, 360.0, 10, 20.0, false);
	  projectile4->shootEnemy0(mBox.x + mBox.w/2, mBox.y + mBox.h/2, hildegarde, enemyID, 40, 360.0, 0, 10, 5.0, true);
	}
	
	if(clearBullets) {
	  projectile3->destroyProjs(NUM_PROJECTILES);
	  projectile4->destroyProjs(NUM_PROJECTILES);
	}


	
      } else {
	dx = 0; dy = 0;
	renderAngle += 30.0;
	if(renderAngle >= 720) {
	  reset();
	  projectile3->destroyProjs(NUM_PROJECTILES);
	  projectile4->destroyProjs(NUM_PROJECTILES);
	}
      }
      break;
    case 1: //Blizzard
      double dxOfProjectile;
      mMaxHitPoints = 50;
      if(!enemyDead) {
	moveThreshold = 180;
	if(actionTicks % moveThreshold == 0) {
	  changeMove = 1;
	  randY = rand()%(100);
	  if(mBox.x > SCREEN_WIDTH/2)
	    randX = 0;
	  else
	    randX = SCREEN_WIDTH-mBox.w;
	}

	moveToXY(randX, randY, 6.0);

	if(actionTicks > 60) {
	  dxOfProjectile = (SCREEN_WIDTH/2 - posX)/(SCREEN_WIDTH/16);
	  projectile2->shootEnemy3(rand()%SCREEN_WIDTH, 0, hildegarde, enemyID, dxOfProjectile);

	  yenisei->speedModX = dxOfProjectile/2;
	}
	
	if(clearBullets) {
	  projectile2->destroyProjs(NUM_PROJECTILES);
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
    case 2:
      if(!enemyDead) {
	mMaxHitPoints = 100;
	moveThreshold = 60;
	if(actionTicks % moveThreshold == 0) {
	  changeMove = 1;
	  randY = rand()%(SCREEN_HEIGHT - 400);
	  randX = hildegarde->getBox().x - mBox.w/2;
	}
	moveToXY(randX, randY, 8.0);

	if(actionTicks > 60) {
	  projectile4->shootEnemy1(mBox.x + mBox.w/2, mBox.y + mBox.h/2, hildegarde, enemyID, 40, 0.0, 10, 10.0, true);
	}
	
	if(clearBullets) {
	  projectile4->destroyProjs(NUM_PROJECTILES);
	}
	
      } else {
	dx = 0; dy = 0;
	renderAngle += 30.0;
	if(renderAngle >= 720) {
	  reset();
	  projectile4->destroyProjs(NUM_PROJECTILES);
	}
      }
      break;
    case 3: //Ice cube
      if(!enemyDead) {
	mMaxHitPoints = 50;
	/*moveThreshold = ;
	if(actionTicks % moveThreshold == 0) {
	  changeMove = 1;
	  randY = rand()%(SCREEN_HEIGHT - 400);
	  randX = hildegarde->getBox().x - mBox.w/2;
	  }*/
	
	moveToXY(SCREEN_WIDTH/2, 50, 8.0);


	
	if(actionTicks > 60) 
	  projectile4->shootEnemy5(mBox.x + mBox.w/2, mBox.y + mBox.h/2, hildegarde, enemyID, 360, 360.0, 0.0, 196, 5.0, true);

	if(actionTicks > 90)
	  projectile3->shootEnemy1(mBox.x + mBox.w/2, mBox.y + mBox.h/2, hildegarde, enemyID, 40, 360.0, 20, 20.0, false);
	
	if(clearBullets) {
	  projectile4->destroyProjs(NUM_PROJECTILES);
	  projectile3->destroyProjs(NUM_PROJECTILES);
	}
	
      } else {
	dx = 0; dy = 0;
	renderAngle += 30.0;
	if(renderAngle >= 720) {
	  reset();
	  projectile4->destroyProjs(NUM_PROJECTILES);
	  projectile3->destroyProjs(NUM_PROJECTILES);
	}
      }
      break;
    case 4:
      if(!enemyDead) {
	mMaxHitPoints = 30;
	moveThreshold = 90;
	if(actionTicks % moveThreshold == 0) {
	  changeMove = 1;
	  randY = rand()%(SCREEN_HEIGHT - 400);
	  randX = hildegarde->getBox().x - mBox.w/2;
	}
	
	moveToXY(randX, randY, 8.0);


	
	if(actionTicks > 60) 
	  projectile4->shootEnemy0(mBox.x + mBox.w/2, mBox.y + mBox.h/2, hildegarde, enemyID, 60, 45.0, 0.0, 20, 15.0, true, true);
	
	if(clearBullets) {
	  projectile4->destroyProjs(NUM_PROJECTILES);
	}
	
      } else {
	dx = 0; dy = 0;
	renderAngle += 30.0;
	if(renderAngle >= 720) {
	  reset();
	  projectile4->destroyProjs(NUM_PROJECTILES);
	}
      }
      break;
    case 5:
      if(!enemyDead) {
	mMaxHitPoints = 50;
	//moveThreshold = 90;
	//if(actionTicks % moveThreshold == 0) {
	//  changeMove = 1;
	//  randY = rand()%(SCREEN_HEIGHT - 400);
	//  randX = hildegarde->getBox().x - mBox.w/2;
	//}
	
	moveToXY(SCREEN_WIDTH/2 - mBox.w/2, 50, 8.0);
       
	if(slowDown) {
	  slowValue = 0.25;
	  yenisei->slow = slowValue;
	}

	if(actionTicks > 180)
	  projectile4->shootEnemy0(rand()%SCREEN_WIDTH, rand()%50 + 1, hildegarde, enemyID, 20/slowValue, 90.0, 45.0, 10, 5.0, true, false, slowValue);
	if(actionTicks > 120)
	  projectile2->shootEnemy0(rand()%SCREEN_WIDTH, rand()%50 + 1, hildegarde, enemyID, 20/slowValue, 90.0, 45.0, 10, 5.0, false, false, slowValue);
	if(actionTicks > 150)
	  projectile3->shootEnemy0(0, 0, hildegarde, enemyID, 20/slowValue, 90.0, 0.0, 10, 5.0, false, false, slowValue);
	if(actionTicks > 180)
	  freezeAnim();
	if(actionTicks > 190)
	  slowDown = 1;
	  
	if(actionTicks < 220)
	  restoreHP();

	//printf("%i\n", mCurrentHitPoints);
	
	if(clearBullets) {
	  projectile2->destroyProjs(NUM_PROJECTILES);
	  projectile3->destroyProjs(NUM_PROJECTILES);
	  projectile4->destroyProjs(NUM_PROJECTILES);
	}
	
      } else {
	dx = 0; dy = 0;
	renderAngle += 30.0;
	if(renderAngle >= 720) {
	  reset();
	  projectile4->destroyProjs(NUM_PROJECTILES);
	  projectile3->destroyProjs(NUM_PROJECTILES);
	  projectile2->destroyProjs(NUM_PROJECTILES);
	}
      }
      break;
    }
    break;
  case troubadourID:
    
    if(dx != 0 || dy != 0) {
      currentClip = &gEnemyClips[1];
      if(dx > 0)
        currentClip = &gEnemyClips[2];
    }
    else {
      if(attackAnim)
	currentClip = &gEnemyClips[3];
      else
	currentClip = &gEnemyClips[0];
      flipType = SDL_FLIP_NONE;
    }
    
    switch(deaths) {
    case 0: //Bounce 1 (gravity)
      if(!enemyDead) {
	mMaxHitPoints = 100;
	/*moveThreshold = 220;
	if(actionTicks % moveThreshold == 0) {
	  attackAnim = 0;
	  changeMove = 1;
	  randY = rand()%(SCREEN_HEIGHT - 500);
	  randX = rand()%(SCREEN_WIDTH - mBox.w*2) + mBox.w*2;
	  if(abs(hildegarde->getBox().x - mBox.x) > 150)
	    randX = hildegarde->getBox().x - mBox.w/2;
	    }*/
	randX = SCREEN_WIDTH/2 - mBox.w/2;
	randY = 50;
	moveToXY(randX, randY, 16.0);

	if(actionTicks > 60) {
	  projectile4->shootEnemy3(mBox.x + mBox.w/2, mBox.y + mBox.h/2, hildegarde, enemyID, 0.0, 5.0, 0.2, true, 10);
	} else {
	  restoreHP();
	}
	
	if(actionTicks < 200 && dx == 0 && dy == 0)
	  attackAnim = 1;
	
	  
	if(clearBullets) {
	  projectile4->destroyProjs(NUM_PROJECTILES);
	}


	
      } else {
	dx = 0; dy = 0;
	renderAngle += 30.0;
	if(renderAngle >= 720) {
	  reset();
	  projectile4->destroyProjs(NUM_PROJECTILES);
	}
      }
      break;
    case 1: //Sound wave: vertical
      if(!enemyDead) {
	mMaxHitPoints = 100;
	moveThreshold = 220;
	if(actionTicks % moveThreshold == 0) {
	  attackAnim = 0;
	  changeMove = 1;
	  randY = rand()%(SCREEN_HEIGHT - 500);
	  randX = rand()%(SCREEN_WIDTH - mBox.w*2) + mBox.w*2;
	  if(abs(hildegarde->getBox().x - mBox.x) > 150)
	    randX = hildegarde->getBox().x - mBox.w/2;
	}
	moveToXY(randX, 50, 8.0);

	if(actionTicks > 60) {
	  projectile4->horizontalOsc = 0;
	  projectile4->shootEnemy1(mBox.x + mBox.w/2, mBox.y + mBox.h/2, hildegarde, enemyID, 20, 360.0, 0,  5.0, true);
	  projectile4->shootEnemy1(mBox.x + mBox.w/2, mBox.y + mBox.h/2, hildegarde, enemyID, 20, 360.0, 0, 5.0, true);
	  projectile2->shootEnemy0(mBox.x + mBox.w/2, mBox.y + mBox.h/2, hildegarde, enemyID, 160, 30.0, 0.0, 20, 15.0, false, true);
	}
	if(actionTicks < 200 && dx == 0 && dy == 0)
	  attackAnim = 1;
	
	  
	if(clearBullets) {
	  projectile4->destroyProjs(NUM_PROJECTILES);
	  projectile2->destroyProjs(NUM_PROJECTILES);
	}


	
      } else {
	dx = 0; dy = 0;
	renderAngle += 30.0;
	if(renderAngle >= 720) {
	  reset();
	  projectile4->destroyProjs(NUM_PROJECTILES);
	  projectile2->destroyProjs(NUM_PROJECTILES);
	}
      }
      break;
    
    case 2: //Bounce 2 (fast)
      if(!enemyDead) {
	mMaxHitPoints = 200;
	moveThreshold = 220;
	if(actionTicks % moveThreshold == 0) {
	  attackAnim = 0;
	  changeMove = 1;
	  randY = rand()%(SCREEN_HEIGHT - 500);
	  randX = rand()%(200) + hildegarde->getBox().x - 100;
	  if(randX > SCREEN_WIDTH - mBox.w)
	    randX = SCREEN_WIDTH - mBox.w;
	  else if(randX < 0)
	    randX = 0 + mBox.w;
	}
	moveToXY(randX, 50, 8.0);

	if(actionTicks > 60) {
	  projectile4->shootEnemy5(mBox.x + mBox.w/2, mBox.y + mBox.h/2, hildegarde, enemyID, 250, 360.0, 0.0, 50, 2.0, false);
	}
	
	if(actionTicks < 200 && dx == 0 && dy == 0)
	  attackAnim = 1;
	
	  
	if(clearBullets) {
	  projectile4->destroyProjs(NUM_PROJECTILES);
	}


	
      } else {
	dx = 0; dy = 0;
	renderAngle += 30.0;
	if(renderAngle >= 720) {
	  reset();
	  projectile4->destroyProjs(NUM_PROJECTILES);
	}
      }
      break;
    case 3: //Sound wave: horizontal
      if(!enemyDead) {
	mMaxHitPoints = 200;
	/*moveThreshold = 220;
	if(actionTicks % moveThreshold == 0) {
	  attackAnim = 0;
	  changeMove = 1;
	  randY = rand()%(SCREEN_HEIGHT - 500);
	  randX = rand()%(SCREEN_WIDTH - mBox.w*2) + mBox.w*2;
	  if(abs(hildegarde->getBox().x - mBox.x) > 150)
	    randX = hildegarde->getBox().x - mBox.w/2;
	    }*/
	moveToXY(0, SCREEN_HEIGHT - mBox.h - 50, 16.0);

	if(actionTicks > 150) {
	  projectile4->horizontalOsc = 1;
	  projectile4->shootEnemy1(mBox.x + mBox.w/2, mBox.y + mBox.h/2, hildegarde, enemyID, 20, 360.0, 0,  5.0, true);
	  projectile4->shootEnemy1(mBox.x + mBox.w/2, mBox.y + mBox.h/2, hildegarde, enemyID, 20, 360.0, 0, 5.0, true);
	} else {
	  restoreHP();
	}

	if(actionTicks > 280) {
	  projectile3->shootEnemy0(rand()%(SCREEN_WIDTH/2) + SCREEN_WIDTH/4, rand()%(SCREEN_HEIGHT/16), hildegarde, enemyID, 60, 0.0, 0.0, 10, 20.0, false, true);
	  //attackAnim = 0;
	}
	
	if(actionTicks < 200 && dx == 0 && dy == 0)
	  attackAnim = 1;
	
	  
	if(clearBullets) {
	  projectile4->destroyProjs(NUM_PROJECTILES);
	  projectile2->destroyProjs(NUM_PROJECTILES);
	  projectile3->destroyProjs(NUM_PROJECTILES);
	}


	
      } else {
	dx = 0; dy = 0;
	renderAngle += 30.0;
	if(renderAngle >= 720) {
	  reset();
	  projectile4->destroyProjs(NUM_PROJECTILES);
	  projectile2->destroyProjs(NUM_PROJECTILES);
	  projectile3->destroyProjs(NUM_PROJECTILES);
	}
      }
      break;
    case 4: //Bounce 3 (shoot)
      if(!enemyDead) {
	mMaxHitPoints = 200;
	moveThreshold = 220;
	if(actionTicks % moveThreshold == 0) {
	  attackAnim = 0;
	  changeMove = 1;
	  randY = rand()%(SCREEN_HEIGHT - 500);
	  randX = rand()%(200) + hildegarde->getBox().x - 100;
	  if(randX > SCREEN_WIDTH - mBox.w)
	    randX = SCREEN_WIDTH - mBox.w;
	  else if(randX < 0)
	    randX = 0 + mBox.w;
	}
	moveToXY(randX, 50, 9.0);

	if(actionTicks > 150) {
	  projectile4->shootEnemy5(mBox.x + mBox.w/2, mBox.y + mBox.h/2, hildegarde, enemyID, 125, 360.0, 0.0, 25, 2.0, false);
	  projectile2->shootEnemy0(mBox.x + mBox.w/2, mBox.y + mBox.h/2, hildegarde, enemyID, 125, 0.0, 0.0, 10, 15.0, false, true);
	}
	
	if(actionTicks < 200 && dx == 0 && dy == 0)
	  attackAnim = 1;
	
	  
	if(clearBullets) {
	  projectile4->destroyProjs(NUM_PROJECTILES);
	  projectile2->destroyProjs(NUM_PROJECTILES);
	}


	
      } else {
	dx = 0; dy = 0;
	renderAngle += 30.0;
	if(renderAngle >= 720) {
	  reset();
	  projectile4->destroyProjs(NUM_PROJECTILES);
	  projectile2->destroyProjs(NUM_PROJECTILES);
	}
      }
      break;
    case 5: //Sound ripples
      if(!enemyDead) {
	mMaxHitPoints = 100;
	moveThreshold = 220;
	if(actionTicks % moveThreshold == 0) {
	  attackAnim = 0;
	  changeMove = 1;
	  /*randY = rand()%(SCREEN_HEIGHT - 500);
	  randX = rand()%(200) + hildegarde->getBox().x - 100;
	  if(randX > SCREEN_WIDTH - mBox.w)
	    randX = SCREEN_WIDTH - mBox.w;
	  else if(randX < 0)
	  randX = 0 + mBox.w;*/
	}
	moveToXY(randX, 100, 8.0);

	double angleProj = actionTicks*10;
	if(actionTicks > 60) 
	  projectile2->shootEnemy0(mBox.x + mBox.w/2, mBox.y + mBox.h/2, hildegarde, enemyID, 3, angleProj, angleProj, 1, 5.0, false, false);
	
	if(actionTicks > 60)
	  projectile4->shootEnemy0(mBox.x + mBox.w/2, mBox.y + mBox.h/2, hildegarde, enemyID, 10, angleProj+5, angleProj+5, 2, 2.5, true, false);

	if(actionTicks > 150)
	  projectile1->shootEnemy1(mBox.x + mBox.w/2, mBox.y + mBox.h/2, hildegarde, saucerID, 160, 360.0, 10, 0.25);
	else
	  restoreHP();

	//printf("%i\n", mCurrentHitPoints);
	
	if(actionTicks < 200 && dx == 0 && dy == 0)
	  attackAnim = 1;
	
	  
	if(clearBullets) {
	  projectile4->destroyProjs(NUM_PROJECTILES);
	  projectile2->destroyProjs(NUM_PROJECTILES);
	  projectile1->destroyProjs(NUM_PROJECTILES);
	}


	
      } else {
	dx = 0; dy = 0;
	renderAngle += 30.0;
	if(renderAngle >= 720) {
	  reset();
	  projectile4->destroyProjs(NUM_PROJECTILES);
	  projectile2->destroyProjs(NUM_PROJECTILES);
	  projectile1->destroyProjs(NUM_PROJECTILES);
	}
      }
      break;
    
    }
    break;
  }
}

void Chara::shoot(Projectile* projectile, Enemy* enemy) {
  projectile->shootHG(mBox.x, mBox.y, enemy);
}


void Enemy::freezeAnim() {
  SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);
  SDL_SetRenderDrawColor(gRenderer, 20, 70, 150, 50);
  SDL_RenderFillRect(gRenderer, &freezeBox);
  if(freezeBox.w < SCREEN_WIDTH + 10) {
    freezeBox.h += 64;
    freezeBox.y = camera.h/2 - freezeBox.h/2;
    freezeBox.w += 64;
    freezeBox.x = camera.w/2 - freezeBox.h/2;
  }
}
