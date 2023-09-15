#include "louis.h"
#include "renderer.cpp"
#include "button.cpp"

Chara::Chara() {
  defaultPosX = DOT_WIDTH;
  posX = defaultPosX;
  defaultPosY = SCREEN_HEIGHT - 80.0;
  posY = defaultPosY;
  mBox.x = posX; mBox.y = posY;
  mBox.w = 9;
  mBox.h = 9;
	
  mVelX = 0; mVelXNP = 0;
  mVelY = 0; mVelYNP = 0;

  resetAnim = 0; 
}
bool hasPushedKey;
//Handles movement & attack
void Chara::handleEvent( SDL_Event& e ) {
  if(e.type == SDL_KEYDOWN && e.key.repeat == 0) {
    //if(!hildegarde.death) {
      switch(e.key.keysym.sym) {
      case SDLK_UP: rotateDown = 1; break;
      case SDLK_DOWN: rotateUp = 1; break;
      case SDLK_LEFT: moveLeft = true;
	resetAnim = 1; break;
      case SDLK_RIGHT: moveRight = true;
	resetAnim = 1; break;
      case SDLK_z: if(attackDirection != 0)
	  HGAttacking = 1; break;
      }
      //} else {
      if(hildegarde.death && e.key.keysym.sym == SDLK_x) {
	reset = 1; mVelX = 0; HGAttacking = 0;
      } else if(e.key.keysym.sym == SDLK_c && unlockedCredits) {
	reset = 1; 		
	isCreditsScene = 1;
      }
      //}
  }
  //If a key was released
  if(e.type == SDL_KEYUP && e.key.repeat == 0) {
    //if(!hildegarde.death) {
      switch(e.key.keysym.sym) {
      case SDLK_UP: attackDirectionTicks = 0; rotateDown = 0; break;
      case SDLK_DOWN: attackDirectionTicks = 0; rotateUp = 0; break;
      case SDLK_LEFT: moveLeft = false; break;
      case SDLK_RIGHT: moveRight = false; break;
      case SDLK_z: HGAttacking = 0; break;
      }
      //}
  }
}


SDL_Rect Chara::getBox() {
	return mBox;
}

int Chara::getVelX() {
	return mVelX;
}

int Chara::getVelY() {
	return mVelY;
}

void Chara::setPos(int x, int y) {
	posX = x;
	posY = y;
	mBox.x = posX; 
	mBox.y = posY;
}

void Chara::setVel(double dx, double dy) {
	mVelX = dx; mVelY = dy;
	accTicks = 0;
}

int frame;
void Chara::render(SDL_Rect& camera, LTexture* gSpriteSheetTexture) {
	if(resetAnim) {
		count = 0; frame = 0; resetAnim = 0;
	}
	if(mVelX == 0.0) {
		currentClip = &gSpriteClips[ frame ]; 
		gSpriteSheetTexture->render( mBox.x - camera.x - DOT_WIDTH/2, mBox.y - camera.y - DOT_HEIGHT/2, currentClip ); 
		if (count % 5 == 0 && count != 0) 
			++frame; 
		//Cycle animation 
		if( count >= 55 ) { 
			frame = 0; 
			count = 0; 
		} 
		count++;
	} else {
		if(mVelX < 0.0) {
			currentClip = &gSpriteClips[ frame * 2 ]; 
			gSpriteSheetTexture->render( mBox.x - camera.x - DOT_WIDTH/2, mBox.y - camera.y - DOT_HEIGHT/2, currentClip ); 
			if (count % 10 == 0 && count != 0) 
				++frame; 
			//Cycle animation 
			if( count >= 55 ) { 
				frame = 0; 
				count = 0; 
			} 
			count++;
		} else if(mVelX > 0.0) {
			currentClip = &gSpriteClips[ frame * 2 ]; 
			gSpriteSheetTexture->render( mBox.x - camera.x - DOT_WIDTH / 2, mBox.y -  camera.y - DOT_HEIGHT/2, currentClip ); 
			if (count % 5 == 0 && count != 0) 
				++frame; 
			//Cycle animation 
			if( count >= 25 ) { 
				frame = 0; 
				count = 0; 
			} 
			count++;
		}
	}
}

// 0 is N/A, 1 is right, 2 is diag. right, 3 is up, 4 is diag. left, 5 is left
void Chara::renderHG(SDL_Rect& camera, LTexture* gSpriteSheetTexture) {
	if(death)
		attackDirection = 9;
	if(rotateDown && attackDirection != 1 && attackDirection != 0) {
		attackDirectionTicks++;
		if(attackDirectionTicks % 5 == 0)
			attackDirection--;
	}
	else if(rotateUp && attackDirection != 5) {
		attackDirectionTicks++;
		if(attackDirectionTicks % 5 == 0)
			attackDirection++;
	}
	switch(attackDirection) {
		case 0: currentClip = &gHGSpriteClips[0]; break;
		case 1: currentClip = &gHGSpriteClips[1]; break;
		case 2: currentClip = &gHGSpriteClips[2]; break;
		case 3: currentClip = &gHGSpriteClips[3]; break;
		case 4: currentClip = &gHGSpriteClips[4]; break;
		case 5: currentClip = &gHGSpriteClips[5]; break;
		case 9: currentClip = &gHGSpriteClips[6]; break;
	}
	if(frame % 11 == 0)
		animWobble = 1;
	else
		animWobble = 0;
	gSpriteSheetTexture->render(mBox.x - camera.x - HGDOT_WIDTH/2 + 3, mBox.y - camera.y - HGDOT_HEIGHT/2 - 20 - animWobble + 28, currentClip);
	SDL_SetRenderDrawColor(gRenderer, 255, 50, 0, 255);
	SDL_RenderFillRect(gRenderer, &mBox);

}

void Chara::move() {
  if(!hildegarde.death) {
    mVelX = DOT_VEL;
    if(moveRight) {
      posX += mVelX;
      if(posX > SCREEN_WIDTH) {
	posX -= mVelX;
      }
      mBox.x = posX;
    }
    if(moveLeft) {
      posX -= mVelX;
      if(posX - 20 < 0) {
	posX += mVelX;
      }
      mBox.x = posX;
    }
  }
}

void Chara::moveHG() {
  posX = yenisei.posX - 15.0;
  posY = yenisei.posY - 28.0;
  mBox.x = posX;
  mBox.y = posY;
}

double Chara::getX(double x) {
	return posX + mBox.w/2;
}
double Chara::getY(double y) {
	return posY + mBox.h/2;
}

void Chara::moveToXY(double x, double y, double speed) {
	if(!moved) {
		double side1 = y - posY;
		double side2 = posX - x;
		double r = sqrt(side1 * side1 + side2 * side2);
		double sinAngle = (side1/r);
		double cosAngle = (side2/r);
		distance = r;
		if(posX > x)
			mVelX = -speed*cosAngle;
		else {
			cosAngle = -cosAngle;
			mVelX = speed*cosAngle;
		}
		if(posY < y)
			mVelY = speed*sinAngle;
		else {
			sinAngle = -sinAngle;
			mVelY = -speed*sinAngle;	
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
		mVelX *= speedMod;	
		mVelY *= speedMod;
		posX += mVelX; posY += mVelY;
		mBox.x = posX; mBox.y = posY;
		mVelX /= speedMod;
		mVelY /= speedMod;
		//printf("%g/%g/%g/%g/%g/%g/%g/%g\n", distanceX, distanceY, distance, speedMod, dx, dy, x, y);
	} else {
		posX = x; posY = y;
		mVelX = 0; mVelY = 0;
	}
}

void Chara::moveToAcc(double x, double y, double speed, double acc) {
	if(!moved) {
		double side1 = y - posY;
		double side2 = posX - x;
		double r = sqrt(side1 * side1 + side2 * side2);
		double sinAngle = (side1/r);
		double cosAngle = (side2/r);
		distance = r;
		if(posX > x)
			mVelX = -speed*cosAngle;
		else {
			cosAngle = -cosAngle;
			mVelX = speed*cosAngle;
		}
		if(posY < y)
			mVelY = speed*sinAngle;
		else {
			sinAngle = -sinAngle;
			mVelY = -speed*sinAngle;	
		}
		moved = 1;
	}
	mVelX += acc*accTicks;
	posX += mVelX; posY += mVelY;
	mBox.x = posX; mBox.y = posY;
}

void Chara::die() {
	if(!didResetAnim) {
		Mix_HaltMusic();
		gKhayan = Mix_LoadMUS("resources/music/khayan.ogg");
		Mix_PlayMusic(gKhayan, -1);
		resetAnim = 1; didResetAnim = 1;
		rotateDown = 0; rotateUp = 0;
		HGAttacking = 0;
	}
	deathTicks++;
	accTicks++;
	//printf("%g\n", posX);
	if(deathTicks < 60)
		moveToAcc(posX - 100, posY, 6.0, 0.005);
	else {
		if(!changeMove) {
			changeMove = 1;
			moved = 0; accTicks = 0;
		}
		if(!(mBox.x > SCREEN_WIDTH + 100))
			moveToAcc(posX + SCREEN_WIDTH + 200, posY, mVelX, 0.005);
		else {
			//deathTicks = 0;
			if(!reset)	
				isGameOverScreen = 1;			
		}
	}					
}

