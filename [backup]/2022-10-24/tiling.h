#include <fstream>

const int TILE_WIDTH = 30;
const int TILE_HEIGHT = 30;
const int TOTAL_TILE_SPRITES = 9;

//The different tile sprites
const int TILE_VOID2 = 0;
const int TILE_WALLUP = 1;
const int TILE_WALLDOWN = 2;
const int TILE_WALLLEFT = 3;
const int TILE_WALLRIGHT = 4;
const int TILE_FLOOR = 5;
const int TILE_VOID = 6;
const int TILE_DOOR1 = 7;
const int TILE_DOOR2 = 8;

int LAST_TILE = TILE_DOOR2;

SDL_Rect gTileClips[ TOTAL_TILE_SPRITES ];

std::string mapStr = "resources/floor_tiles/level1.map";

//levelID corresponds to the number of the map in the floor_tiles folder
//1 louisHouse; 2 sirohebi
int levelID = 1;

//The tile
class Tile
{
    public:
		//Initializes position and type
		Tile( int x, int y, int tileType );

		//Shows the tile
		void render( SDL_Rect& camera );

		//Get the tile type
		int getType();

		//Get the collision box
		SDL_Rect getBox();

    private:
		//The attributes of the tile
		SDL_Rect mBox;

		//The tile type
		int mType;
};

Tile::Tile( int x, int y, int tileType )
{
    //Get the offsets
    mBox.x = x;
    mBox.y = y;

    //Set the collision box
    mBox.w = TILE_WIDTH;
    mBox.h = TILE_HEIGHT;

    //Get the tile type
    mType = tileType;
}
