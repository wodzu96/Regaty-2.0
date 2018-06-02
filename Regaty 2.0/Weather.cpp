#include <iostream>
#include "Weather.h"
#include <cstdlib>
using namespace std;
Weather::Weather(){
	Wind_start = rand()%42; // in knots
	Wind_end = rand()%42;
	Sea_start = rand()%10+1; // in Beaufort scale
	alfa_start = rand()%360;
	alfa_end = rand()%360;
	alfa_now = alfa_start;
    counter = 0;
	Wind_now = Wind_start;
	Sea_now = Sea_start;
}
void Weather::refresh(){
    if(counter == 1000){
        Wind_start = Wind_now;
        alfa_start = alfa_now;
        Wind_end = rand()%42;
        alfa_end = rand()%360;
        counter = 0;
    }
    ++counter;
	Wind_now = Wind_now + (float)(Wind_end-Wind_start)/(float)1000;
	Sea_now = Sea_now + (float)((Wind_now /6+1)-Sea_now)/(float)100;
	alfa_now = alfa_now + (float)(alfa_end-alfa_start)/(float)1000;
	//cout<<"Wind now: "<<Wind_now<<" knots, position: "<<alfa_now<<" degrees. Beafort scale: "<<Sea_now<<endl;
}
