#include "RayWindow.h"

int main(int argc, char *argv[])
{

	RayWindow* win = new RayWindow(1280, 720);
	
	win->init();
	win->run();

	return 0;
} 