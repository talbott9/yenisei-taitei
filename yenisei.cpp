//Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include "level1.cpp"


//Starts up SDL and creates window
bool init();

//Frees media and shuts down SDL
void close();

bool init()
{
  //Initialization flag
  bool success = true;

  srand(time(NULL));

  if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
    printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    success = false;
  } else {
    //Set texture filtering to linear
    if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) 	{
      printf("Warning: Linear texture filtering not enabled!");
    }

    //Create window
    gWindow = SDL_CreateWindow("Thing", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(gWindow == NULL) {
      printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
      success = false;
    } else {
      //Create vsynced renderer for window
      gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
      if(gRenderer == NULL)	{
	printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
	success = false;
      } else {
	//Initialize renderer color
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if(!(IMG_Init( imgFlags ) & imgFlags)) {
	  printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
	  success = false;
	}

	if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
	  printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
	  success = false;
	}

	//Initialize SDL_ttf
	if(TTF_Init() == -1)  {
	  printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
	  success = false;
	}
      }
    }
  }
  return success;
}

void freeAll() {
  //Free loaded images
  gTextbox.free();
  gTuvaMap.free();
  Mix_FreeMusic(gKozato);
  gKozato = NULL;
  Mix_FreeMusic(gGimn);
  gGimn = NULL;
  Mix_FreeMusic(gBattleSong);
  gBattleSong = NULL;
  Mix_FreeMusic(gKhayan);
  gKhayan = NULL;
  gIllust1.free();
  gIllust2.free();
}

void close() {
  freeAll();
  //Destroy window	
  SDL_DestroyRenderer(gRenderer);
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;
  gRenderer = NULL;

  //Quit SDL subsystems
  IMG_Quit();
  SDL_Quit();
}

//Augmented reset function. I couldn't find a better name for it
void resetGamePlus() {
  freeAll();
  finishedCredits = 0;
  speedUpCredits = 0;
  Mix_HaltMusic();
  isCreditsScene = 0;
  creditsTicks = 0;
  isGameOverScreen = 0;
  gameOverScreenSuccess = 0;
  alphaTicks = 0;
  resetGame(&enemy1, &yenisei);
  hildegarde.death = 0;
  attackDirection = 0;
  reset = 0;
}

void play(int levelID) {
  //Main loop flag
      bool quit = false;

      //Event handler;
      SDL_Event e;

      hildegarde.setPos(yenisei.getBox().x - 15, yenisei.getBox().y - 25);
      Enemy enemy = enemy1;
      Projectile proj1, proj2, proj3, proj4;
      switch(levelID) {
      case 0: enemy = enemy1; proj1 = projectile2; proj2 = projectile3; proj3 = projectile4; break;
      case 1: enemy = saucer; proj1 = saucerProjectile; proj2 = projectile2; proj3 = projectile3; proj4 = starProjectile1; break;
      }

      //While application is running
      while(!quit) {
	if(inMenuScreen) {
	  if(reset) {
	    resetGamePlus();
	    gTuvaMap.loadFromFile("resources/floor_tiles/tuvamap.png");
	  }

	  menuBuffer++;
	  renderMenuScreen();
	} else if(isCreditsScene) {
	  if(reset) {
	    resetGamePlus();
	    gGimn = Mix_LoadMUS("resources/music/gimn.ogg");
	    gIllust1.loadFromFile("resources/floor_tiles/illust1thanks.png");
	    gIllust2.loadFromFile("resources/floor_tiles/illust2.png");				
	  }
					
	  if(Mix_PlayingMusic() == 0) {
	    Mix_PlayMusic(gGimn, -1);
	  }
	  SDL_Rect backgroundColor; backgroundColor.x = 0; backgroundColor.y = 0; backgroundColor.w = SCREEN_WIDTH; backgroundColor.h = SCREEN_HEIGHT;
	  SDL_Rect shadeColor; shadeColor.x = 0; shadeColor.y = 0; shadeColor.w = SCREEN_WIDTH; shadeColor.h = SCREEN_HEIGHT;
	  SDL_SetRenderDrawColor(gRenderer, 255, 198, 104, 255);
	  SDL_RenderFillRect(gRenderer, &backgroundColor);

	  background.render(camera);
	  yenisei.move();
	  hildegarde.moveHG();
	  yenisei.render(camera, &gYeniseiTexture);
	  hildegarde.renderHG(camera, &gHildegardeTexture);
	  SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);
	  SDL_SetRenderDrawColor(gRenderer, 0, 0,  0, 20);
	  SDL_RenderFillRect(gRenderer, &shadeColor);
	  creditsScene();

	} else {
	  if(reset) {
	    switch(levelID) {
	    case 0: enemy = enemy1; break;
	    case 1: enemy = saucer; break;
	    }
	    resetGamePlus();
	    gBattleSong = Mix_LoadMUS("resources/music/battlesong.ogg");
	  }

	  if(Mix_PlayingMusic() == 0)
	    Mix_PlayMusic(gBattleSong, -1);
	  SDL_Rect backgroundColor; backgroundColor.x = 0; backgroundColor.y = 0; backgroundColor.w = SCREEN_WIDTH; backgroundColor.h = SCREEN_HEIGHT;
	  SDL_SetRenderDrawColor(gRenderer, 88, 99, 100, 255);
	  SDL_RenderFillRect(gRenderer, &backgroundColor);

	  background.render(camera);
				
	  if(!hildegarde.death) {
	    yenisei.move();
	    hildegarde.shoot(&projectileHG, &enemy);
	  }
	  else
	    yenisei.die();
	  hildegarde.moveHG();

	  yenisei.render(camera, &gYeniseiTexture);
	  hildegarde.renderHG(camera, &gHildegardeTexture);
	  if(!gameOverScreenSuccess) 
	    enemy.doThings(&proj1, &proj2, &proj3, &hildegarde, &proj4);
	  
	  if(isGameOverScreen)
	    gameOverScreen();	
	  if(!hildegarde.death)
	    showScore();

	}

	clearBullets = 0;

				
	//Handle events on queue
	while(SDL_PollEvent( &e ) != 0) {
	  //User requests quit
	  if(e.type == SDL_QUIT) {
	    quit = true;
	  }

	  if(e.type == SDL_KEYDOWN && e.key.repeat == 0) {
	    if(e.key.keysym.sym == SDLK_q) {
	      if(!inMenuScreen)
		quit = true;
	    }
	    //For testing
	    /*if(e.key.keysym.sym == SDLK_a) {
	      background.addXY(-100, 0);
	      }*/
	  }
	    yenisei.handleEvent(e);
	    if(inMenuScreen || isCreditsScene)
	      button.handleEvent(e);

	}

								
	SDL_RenderPresent(gRenderer);

      }

}

int main( int argc, char* args[] )
{
  srand(time(NULL));
  //Start up SDL and create window
  if(!init()) {
    printf("Failed to initialize!\n");
  } else {
    //Load media
    loadFont(50);
    std::ifstream creditsFile;
    creditsFile.open("credits");
    if(!creditsFile.fail())
      unlockedCredits = 1;

    if(!loadMedia()) {
      printf( "Failed to load media!\n" );
    }
    else {
      play(1);
    }
  }

  //Free resources and close SDL
  close();

  return 0;
}

