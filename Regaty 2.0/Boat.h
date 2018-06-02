#include "Weather.h"
#include "Buoy.h"
#include <iostream>
#include <sstream>
using namespace std;
class Boat{
	private:
		int weight, length, c_skill;
		int s_size;
    int checkColisions(Weather* weather, Boat *boat);
    float luffing(float course, float correction, Weather* weather);
    int windDistance(Weather* weather, Boat boat);
		static int counter;
    bool checkPriority(Weather* weather, Boat boat);
    int calulateDistance(Boat boat);
	public:
		Boat();
    int lastCorrection;
		void refresh(Weather *weather, Buoy *buoy, Boat *boat);
    void setStartPosition(int boatsAmount);
		int id, id_buoy;
        float course;
    int boatsAmount;
		int X_position, Y_position;
		int distance;
		float speed;
        string getBoatRaport();
		bool ruin;
};
