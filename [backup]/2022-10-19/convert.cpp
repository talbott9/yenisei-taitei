#include <fstream>
#include <cstdlib>

int TOTAL_TILES = 1376;
int row = 43;
int line = 32;
int linecount = 1;

int main() {
	//Open the map
    	std::ofstream newmap( "resources/floor_tiles/newlevel.map" );
	for( int i = 1; i < TOTAL_TILES + 1; i++ )
	{
		newmap << "00 ";
		if( i % 43 == 0) {
			newmap << "\n";
			linecount++;
		}
		if( i == row / 2 ) {
			newmap << "æ";
			printf("%i ", row / 2);
		}
		if( linecount == line / 2 ) {
			newmap << "ø";
			printf("%i ", line / 2);
			linecount = -999;
		}
	}
}

