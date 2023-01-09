//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
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

	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	} else {
		//Set texture filtering to linear
		if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) 	{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("Yenisei", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
	gYeniseiTexture.free();
	gHildegardeTexture.free();
	gHGArrow1Texture.free();
	gEnemy1Texture.free();
	gBullet1.free(); 
	gBullet2.free();
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

int main( int argc, char* args[] )
{
	srand(time(NULL));
	//Start up SDL and create window
	if(!init()) {
		printf("Failed to initialize!\n");
	} else {
		//Load media
		loadFont(50);
		if(!loadMedia()) {
			printf( "Failed to load media!\n" );
		}
		else {	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			hildegarde.setPos(yenisei.getBox().x - 15, yenisei.getBox().y - 25);

			//While application is running
			while(!quit) {
				if(inMenuScreen) {
					menuBuffer++;
					renderMenuScreen();
				} else {
					SDL_Rect backgroundColor; backgroundColor.x = 0; backgroundColor.y = 0; backgroundColor.w = SCREEN_WIDTH; backgroundColor.h = SCREEN_HEIGHT;
					SDL_SetRenderDrawColor(gRenderer, 88, 99, 100, 255);
					SDL_RenderFillRect(gRenderer, &backgroundColor);

					background.render(camera);

					if(reset) {
						resetGame(&enemy1, &yenisei);
						hildegarde.death = 0;
						attackDirection = 0;
						reset = 0;
					}
				
					if(!hildegarde.death) {
						yenisei.move();
						hildegarde.shoot(&projectile1, &enemy1);
					}
					else
						yenisei.die();
					hildegarde.moveHG();

					yenisei.render(camera, &gYeniseiTexture);
					hildegarde.renderHG(camera, &gHildegardeTexture);
					enemy1.doThings(&projectile2, &projectile3, &projectile4, &hildegarde);
					if(!hildegarde.death)
						showScore();

				}

				
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
					if(!inMenuScreen)
						yenisei.handleEvent(e);
					else
						button.handleEvent(e);

				}

								
				SDL_RenderPresent(gRenderer);

			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}

