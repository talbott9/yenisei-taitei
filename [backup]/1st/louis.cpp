#include "louis.h"
#include "projectiles.cpp"

Chara::Chara() {
	mBox.x = 0 + DOT_WIDTH;
    	mBox.y = SCREEN_HEIGHT - 80;
	mBox.w = 10;
	mBox.h = 10;
	
	mVelX = 0; mVelXNP = 0;
	mVelY = 0; mVelYNP = 0;

	resetAnim = 0; 
}

//Handles movement & attack
void Chara::handleEvent( SDL_Event& e ) {
	if(e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		switch(e.key.keysym.sym) {
	    		case SDLK_UP: rotateDown = 1; break;
	    		case SDLK_DOWN: rotateUp = 1; break;
            		case SDLK_LEFT: mVelX -= DOT_VEL; resetAnim = 1; break;
	    		case SDLK_RIGHT: mVelX += DOT_VEL; resetAnim = 1; break;
			case SDLK_z: HGAttacking = 1; break;
		}
	}
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: attackDirectionTicks = 0; rotateDown = 0; break;
            case SDLK_DOWN: attackDirectionTicks = 0; rotateUp = 0; break;
            case SDLK_LEFT: mVelX += DOT_VEL; break;
            case SDLK_RIGHT: mVelX -= DOT_VEL; break;
	    case SDLK_z: HGAttacking = 0; break;
        }
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

void Chara::setState(int x) {
	cutsceneTurnState = x;
	turnState = x;
	moveState = x;
}

void Chara::setPos(int x, int y) {
	mBox.x = x; 
	mBox.y = y;
}

void Chara::moveToXY(int x, int y, int speed) {
	if(mBox.x != x && mBox.x < x) {
		mVelXNP = speed;
		if(mBox.x > x)
			mBox.x -= mBox.x - x;
	} else if(mBox.x != x && mBox.x > x) {
		mVelXNP = -speed;
		if(mBox.x < x)
			mBox.x += mBox.x - x;
	} else if(mBox.y != y && mBox.y < y) {
		mVelYNP = speed;
		if(mBox.y > y)
			mBox.y -= mBox.y - y;
	} else if(mBox.y != y && mBox.y > y) {
		mVelYNP = -speed;
		if(mBox.y < y)
			mBox.y += mBox.y - y;
	}
	if(mBox.x == x && mBox.y == y) {
		louisMove = 0;
		mVelXNP = 0; mVelYNP = 0;
	}
}

int frame;
void Chara::render(SDL_Rect& camera, LTexture* gSpriteSheetTexture) {
	if(resetAnim) {
		count = 0; frame = 0; resetAnim = 0;
	}
	if(mVelX == 0) {
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
		if(mVelX <= 1) {
			currentClip = &gSpriteClips[ frame * 2 ]; 
			gSpriteSheetTexture->render( mBox.x - camera.x - DOT_WIDTH/2, mBox.y - camera.y - DOT_HEIGHT/2, currentClip ); 
			if (count % 10 == 0 && count != 0) 
				++frame; 
			//Cycle animation 
			if( count >= 50 ) { 
				frame = 0; 
				count = 0; 
			} 
			count++;
		} else if(mVelX >= 1) {
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
	}
	if(frame % 11 == 0)
		animWobble = 1;
	else
		animWobble = 0;
	gSpriteSheetTexture->render(mBox.x - camera.x - HGDOT_WIDTH/2 + 5, mBox.y - camera.y - HGDOT_HEIGHT/2 - 20 - animWobble + 25, currentClip);

}

void Chara::move() {
    //Move the dot left or right
    mBox.x += mVelX;
    //If the dot went too far to the left or right
    if((mBox.x < 0) || (mBox.x > SCREEN_WIDTH)) {
        //Move back
        mBox.x -= mVelX;
    }

    //Move the dot up or down
    //mBox.y += mVelY;

    //If the dot went too far up or down
    //if((mBox.y < 0) || (mBox.y > SCREEN_HEIGHT)) {
        //Move back
     //   mBox.y -= mVelY;
    //}
}

void Chara::moveHG() {
	mBox.x = yenisei.getBox().x - 15;
	//if((yenisei.getBox().x <= 0) || (yenisei.getBox().x >= SCREEN_WIDTH)) {
        //	mBox.x -= yenisei.getVelX();
	//}
	//mBox.y += mVelY;
    	//if((louis.getBox().y < 0) || (mBox.y > SCREEN_HEIGHT)) {
	//	mBox.y -= mVelY;
	//}
}

void Chara::shoot(Projectile* projectile) {
	//if(HGAttacking && projectile->getActiveProjectiles() < NUM_PROJECTILES)
	//	projectile->addProjectiles();
	//else
	//	//projectile->resetProjectiles();
	projectile->render(mBox.x, mBox.y);
}

