#include "collision.cpp"
#include "cutscenes.cpp"
#include "battle.cpp"
#include "louis.cpp"
#include "background.cpp"

const int LEVEL_WIDTH = 1290;
const int LEVEL_HEIGHT = 960;

//Tile constants
const int TOTAL_TILES = 1376;

bool setTiles( Tile* tiles[] );
void readTileMap(Tile* tiles[]);
void freeTileSet(Tile* tiles[]);

bool loadMedia(Tile* tiles[]) {
	//Loading success flag
	bool success = true;

	//Load tile texture
	if( !gTileTexture.loadFromFile( "resources/floor_tiles/tiles1.png" ) )
	{
		printf( "Failed to load tile set texture!\n" );
		success = false;
	}
	if(!gLevel1Floor.loadFromFile("resources/floor_tiles/level1.png"))
		success = false;
	if(!gLevel1Background.loadFromFile("resources/floor_tiles/level1background.png"))
		success = false;
	//Load tile map
	if( !setTiles( tiles ) )
	{
		printf( "Failed to load tile set!\n" );
		success = false;
	}
	if( !gYeniseiTexture.loadFromFile( "resources/yenisei/yeniseisprites.png" ) )	{
		printf( "Failed to load texture!\n" );
		success = false;
	}
	if(!gHGArrow1Texture.loadFromFile("resources/projectiles/HGArrow1.png"))
		success = false;
	if(!gHildegardeTexture.loadFromFile("resources/hildegarde/hildegardesprites.png"))
		success = false;
	//Load sprite sheet texture
	if( !gArmourmanSpriteSheetTexture.loadFromFile( "resources/NPCs/armourman.png" ) )
	{
		printf( "Failed to load walking animation texture!\n" );
		success = false;
	}	
	if(!gTuvaMap.loadFromFile("resources/floor_tiles/tuvamap.png")) {
	       printf("Failed to load map\n");
	       success = false; 
	}       
	if( !gTextbox.loadFromFile( "resources/objects/textbox.png" ) )
	{
		printf("Failed to load object!\n");
		success = false;
	}
	if( !gArrow.loadFromFile("resources/objects/arrow.png") ) {
		printf("Failed to load object!\n");
		success = false;
	}
	TTF_Font* gFont = TTF_OpenFont("resources/fonts/font1.ttf", 20);
	if(gFont == NULL) {
		printf("Failed to load gFont! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
	TTF_Font* gBattleFont= TTF_OpenFont("resources/fonts/battlefont.ttf", 20);
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

		gHGSpriteClips[ 2 ].x =  120; //gHGSpriteClips[ 6 ].x =  ;  gHGSpriteClips[ 10 ].x =  1500; //gHGSpriteClips[ 14 ].x =  54; 
		gHGSpriteClips[ 2 ].y =   0;  //gHGSpriteClips[ 6 ].y =  0;    gHGSpriteClips[ 10 ].y = 0; //gHGSpriteClips[ 14 ].y = 150; 
		gHGSpriteClips[ 2 ].w =  60; //gHGSpriteClips[ 6 ].w =  150;  gHGSpriteClips[ 10 ].w =  150; //gHGSpriteClips[ 14 ].w =  27;
		gHGSpriteClips[ 2 ].h =  72; //gHGSpriteClips[ 6 ].h =  103;  gHGSpriteClips[ 10 ].h =  103; //gHGSpriteClips[ 14 ].h =  50;

		gHGSpriteClips[ 3 ].x =  180; 
		gHGSpriteClips[ 3 ].y =   0;  
		gHGSpriteClips[ 3 ].w =  60; 
		gHGSpriteClips[ 3 ].h =  72;

		gArrowClip[0].x = 0;
		gArrowClip[0].y = 0;
		gArrowClip[0].w = 20;
		gArrowClip[0].h = 20;
	}


	return success;
}

Tile* tileSet[ TOTAL_TILES ];

bool setTiles( Tile* tiles[] )
{
    //Success flag
    bool tilesLoaded = true;

    //Open the map
    std::ifstream map1("resources/floor_tiles/level1.map");
    std::ifstream map2("resources/floor_tiles/level2.map");

    //If the map couldn't be loaded
    if( map1.fail() || map2.fail() )
    {
		printf( "Unable to load map file!\n" );
		tilesLoaded = false;
    }
	else
	{
		readTileMap(tileSet);
		
		//Clip the sprite sheet
		if( tilesLoaded )
		{
			gTileClips[ TILE_FLOOR ].x = 0;
			gTileClips[ TILE_FLOOR ].y = 0;
			gTileClips[ TILE_FLOOR ].w = TILE_WIDTH;
			gTileClips[ TILE_FLOOR ].h = TILE_HEIGHT;

			gTileClips[ TILE_WALLUP ].x = 0;
			gTileClips[ TILE_WALLUP ].y = 30;
			gTileClips[ TILE_WALLUP ].w = TILE_WIDTH;
			gTileClips[ TILE_WALLUP ].h = TILE_HEIGHT;

			gTileClips[ TILE_WALLDOWN ].x = 0;
			gTileClips[ TILE_WALLDOWN ].y = 60;
			gTileClips[ TILE_WALLDOWN ].w = TILE_WIDTH;
			gTileClips[ TILE_WALLDOWN ].h = TILE_HEIGHT;

			gTileClips[ TILE_WALLLEFT ].x = 0;
			gTileClips[ TILE_WALLLEFT ].y = 90;
			gTileClips[ TILE_WALLLEFT ].w = TILE_WIDTH;
			gTileClips[ TILE_WALLLEFT ].h = TILE_HEIGHT;

			gTileClips[ TILE_WALLRIGHT ].x = 0;
			gTileClips[ TILE_WALLRIGHT ].y = 120;
			gTileClips[ TILE_WALLRIGHT ].w = TILE_WIDTH;
			gTileClips[ TILE_WALLRIGHT ].h = TILE_HEIGHT;

			gTileClips[ TILE_VOID ].x = 0;
			gTileClips[ TILE_VOID ].y = 150;
			gTileClips[ TILE_VOID ].w = TILE_WIDTH;
			gTileClips[ TILE_VOID ].h = TILE_HEIGHT;

			gTileClips[ TILE_DOOR1 ].x = 30;
			gTileClips[ TILE_DOOR1 ].y = 0;
			gTileClips[ TILE_DOOR1 ].w = TILE_WIDTH;
			gTileClips[ TILE_DOOR1 ].h = TILE_HEIGHT;

			gTileClips[ TILE_DOOR2 ].x = 30;
			gTileClips[ TILE_DOOR2 ].y = 30;
			gTileClips[ TILE_DOOR2 ].w = TILE_WIDTH;
			gTileClips[ TILE_DOOR2 ].h = TILE_HEIGHT;

			gTileClips[ TILE_VOID2 ].x = 30;
			gTileClips[ TILE_VOID2 ].y = 60;
			gTileClips[ TILE_VOID2 ].w = TILE_WIDTH;
			gTileClips[ TILE_VOID2 ].h = TILE_HEIGHT;
		}
	}

    //Close the file
    map1.close(); map2.close();

    //If the map was loaded fine
    return tilesLoaded;
}

void readTileMap(Tile* tiles[]) {
	freeTileSet(tileSet);

	//The tile offsets
	int x = 0, y = 0;

	std::ifstream map1("resources/floor_tiles/level1.map");
    	std::ifstream map2("resources/floor_tiles/level2.map");
    	std::ifstream map3("resources/floor_tiles/level3.map");
    	std::ifstream map4("resources/floor_tiles/level4.map");
    	std::ifstream map5("resources/floor_tiles/level5.map");
    	std::ifstream map6("resources/floor_tiles/level6.map");
   	std::ifstream map7("resources/floor_tiles/level7.map");
    	std::ifstream map8("resources/floor_tiles/level8.map");
	std::ifstream map9("resources/floor_tiles/level9.map");
    	std::ifstream map10("resources/floor_tiles/level10.map");
	std::ifstream map11("resources/floor_tiles/level11.map");
    	std::ifstream map12("resources/floor_tiles/level12.map");
	
	//Initialize the tiles
	for( int i = 0; i < TOTAL_TILES; i++ )
	{
		//Determines what kind of tile will be made
		int tileType = -1;

		switch(levelID) {
			case 1: map1 >> tileType; break;
			case 2: map2 >> tileType; break;
			case 3: map3 >> tileType; break;
			case 4: map4 >> tileType; break;
			case 5: map5 >> tileType; break;
			case 6: map6 >> tileType; break;
			case 7: map7 >> tileType; break;
			case 8: map8 >> tileType; break;
			case 9: map9 >> tileType; break;
			case 10: map10 >> tileType; break;
			case 11: map11 >> tileType; break;
			case 12: map12 >> tileType; break;
		}

		//If the number is a valid tile number
		if( ( tileType >= 0 ) && ( tileType < TOTAL_TILE_SPRITES ) ) {
			tiles[ i ] = new Tile( x, y, tileType );
		}
		//If we don't recognize the tile type
		else {
			//Stop loading map
			printf( "Error loading map: Invalid tile type at %d!\n", i );
			break;
		}

		//Move to next tile spot
		x += TILE_WIDTH;
			//If we've gone too far
			if( x >= LEVEL_WIDTH ) {
			//Move back
			x = 0;

			//Move to the next row
			y += TILE_HEIGHT;
		}
	}

	map1.close(); map6.close(); map11.close();// map2.close();
	map2.close(); map7.close(); map12.close();// map2.close();
	map3.close(); map8.close(); //map8.close(); map2.close();
	map4.close(); map9.close(); //map9.close(); map2.close();
	map5.close(); map10.close(); //map10.close(); map2.close();
}

void freeTileSet(Tile* tiles[]) {
	for( int i = 0; i < TOTAL_TILES; ++i )
	{
		 if( tiles[ i ] != NULL )
		 {
			delete tiles[ i ];
			tiles[ i ] = NULL;
		 }
	}
}

bool touchesWall(SDL_Rect box, Tile* tiles[])
{
    //Go through the tiles
    for(int i = 0; i < TOTAL_TILES; ++i)
    {
        //If the tile is a wall type tile
        if( (tiles[i]->getType() >= TILE_VOID2 && tiles[i]->getType() <= LAST_TILE) && tiles[i]->getType() != TILE_FLOOR  )
        {
            //If the collision box touches the wall tile
            if( checkCollision(box, tiles[ i ]->getBox()) )
            {
                return true;
            }
        }
    }

    //If no wall tiles were touched
    return false;
}

void Tile::render( SDL_Rect& camera )
{
    //If the tile is on screen
    if( checkCollision( camera, mBox ) )
    {
        //Show the tile
        gTileTexture.render( mBox.x - camera.x, mBox.y - camera.y, &gTileClips[ mType ] );
    }
}

int Tile::getType()
{
    return mType;
}

SDL_Rect Tile::getBox()
{
    return mBox;
}

void Textbox::render(SDL_Rect& camera, std::string string) {
	gTextbox.render( camera.x - camera.x, camera.y - camera.y + mBox.y );
}

void Enemy::doThings(Projectile* projectile, Chara* hildegarde) {
	moveToXY(SCREEN_WIDTH, SCREEN_HEIGHT, 3);
	SDL_RenderFillRect(gRenderer, &mBox);
	projectile->shootEnemy(mBox.x, mBox.y, hildegarde);
}
