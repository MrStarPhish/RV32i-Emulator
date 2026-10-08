#pragma once

#include <iostream>
#include "ConsoleBufferEssentials.h" // import BUFFER and other essential functions

using namespace std;

struct Region { // A rectangular region on the console screen. i.e Register DIsplay, Memory Display
	uint16_t x, y;
	uint16_t width, height;
};

struct Dashboard {
	Region registerRegion;


};