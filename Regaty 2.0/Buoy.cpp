#include <iostream>
#include "Buoy.h"
#include <cstdlib>
int Buoy::counter = 0;
Buoy::Buoy(){
	id = counter++;
	X_position = rand()%2400;
	Y_position = rand()%1600;
}
