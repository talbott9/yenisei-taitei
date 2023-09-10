//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <cstdlib>
#include <cmath>
#include "level1.cpp"


//Starts up SDL and creates window
bool init();

//Frees media and shuts down SDL
void close( Tile* tiles[] );

bool init()
{
	//Initialization flag
	bool success = true;

	srand(time(NULL));

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

				//Initialize SDL_ttf
                		if( TTF_Init() == -1 )
                		{
                			printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                    			success = false;
                		}
			}
		}
	}

	return success;
}

void freeAll(Tile* tiles[]) {
	freeTileSet(tileSet);
	//Free loaded images
	gArmourmanSpriteSheetTexture.free();
	gTextbox.free();
	gArrow.free();
	gText.free();
}

void close()
{
	freeAll(tileSet);
	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
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
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		loadFont(20);
		if( !loadMedia( tileSet ) )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			hildegarde.setPos(yenisei.getBox().x - 15, yenisei.getBox().y - 25);

			//While application is running
			while(!quit) {
				SDL_Rect backgroundColor; backgroundColor.x = 0; backgroundColor.y = 0; backgroundColor.w = SCREEN_WIDTH; backgroundColor.h = SCREEN_HEIGHT;
				SDL_SetRenderDrawColor(gRenderer, 88, 99, 100, 255);
				SDL_RenderFillRect(gRenderer, &backgroundColor);

				background.render(camera);
				
				if(!hildegarde.death) {
					yenisei.move();
					hildegarde.shoot(&projectile1, &enemy1);
				}
				else
					yenisei.die();
				hildegarde.moveHG();

				yenisei.render(camera, &gYeniseiTexture);
				hildegarde.renderHG(camera, &gHildegardeTexture);
				
				//SDL_Rect hitboxHG; hitboxHG.x = hildegarde.getBox().x; hitboxHG.y = hildegarde.getBox().y; hitboxHG.w = hildegarde.getBox().w; hitboxHG.h = hildegarde.getBox().h;
				//SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
				//SDL_RenderFillRect(gRenderer, &hitboxHG);

				enemy1.doThings(&projectile2, &projectile3, &projectile4, &hildegarde);
				
				//Handle events on queue
				while(SDL_PollEvent( &e ) != 0) {
					//User requests quit
					if(e.type == SDL_QUIT) {
						quit = true;
					}

					if(e.type == SDL_KEYDOWN && e.key.repeat == 0) {
						if(e.key.keysym.sym == SDLK_q)
							quit = true;
						if(e.key.keysym.sym == SDLK_a) {
							background.addXY(-100, 0);
						}
					}
					button.handleEvent(e);
					if(!hildegarde.death)
						yenisei.handleEvent(e);
					if(!doNotAdvance && activeDialogue)
						cutscene.handleEvent(e);
				}

								
				SDL_RenderPresent( gRenderer );

			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}

