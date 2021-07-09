#include "ssd1309.h"

SSD1309 screen;

int main(int argc, char *argv[1])
{
	screen.init();
	screen.clear();
	screen.print( 0, 0, "Hola mundo!", 11 );
	screen.flip();
	
	return 0;
}
