#include "Boat.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "limits.h"
using namespace std;
int Boat::counter = 0;
Boat::Boat(){
	id = counter++;
	length = rand()%250+450; 
	weight = length * (float)((float)(rand()%70+30)/100);
	s_size = length * (float)((float)(rand()%40+40)/(float)1000);
	c_skill = rand()%4+1;
	id_buoy = 0;
    lastCorrection = -1;
	ruin = false;
}
void Boat::setStartPosition(int boatsAmount){
    this->boatsAmount = boatsAmount;
    X_position = 1200;
    Y_position = 800-(boatsAmount*90/2)+id*90;
}
string Boat::getBoatRaport(){
    ostringstream ss;
   ss <<"Boat number: "<<id
    <<" length: "<<length<<"cm"
    <<" weight: "<<weight<<"kg"
    <<" sail size: "<<s_size<<"m2"
    <<" crew skill mark: "<<c_skill<<endl;
    return ss.str();
}

int Boat::windDistance(Weather* weather, Boat boat){
    int Y_wind_position=-sin(weather->alfa_now*M_PI/180)*10000;
    int X_wind_position=+cos(weather->alfa_now*M_PI/180)*10000;
    int X_length = boat.X_position-X_wind_position;
    int Y_length = Y_wind_position-boat.Y_position;
    return sqrt((X_length*X_length)+(Y_length*Y_length));
}

int Boat::checkColisions(Weather* weather, Boat *boat){
    int closest_id  = -1;
    int closest_distance = INT_MAX;
    for(int i = 0; i<boatsAmount; ++i){
      //  cout<<"From boat: "<<id<<" to boat: "<<boat[i].id<<" distance: "<<calulateDistance(boat[i])<<endl;
        if(boat[i].id!=id && !boat[i].ruin &&  calulateDistance(boat[i])<120 && windDistance(weather, boat[i])>windDistance(weather, *this)){
            course = weather->alfa_now;
        }
    }
    
}
bool Boat::checkPriority(Weather* weather, Boat boat){
    return abs(abs(boat.course-weather->alfa_now)-180)<abs(abs(course-weather->alfa_now)-180);
}
int Boat::calulateDistance(Boat boat){
    int X_length = boat.X_position-X_position;
    int Y_length = Y_position-boat.Y_position;
    return sqrt((X_length*X_length)+(Y_length*Y_length));
}
float Boat::luffing(float course, float correction, Weather* weather){
//    cout<<"Odpadam o "<<correction<<" stopni - lodz nr: "<<id<<endl;
//    cout<<"Kurs wiatru: "<<weather->alfa_now<<" kurs lodzi: "<<course<<endl;
    float after_correction = course + correction;
    float after_correction1 = course - correction;
    if(abs(abs(after_correction-weather->alfa_now)-180)<abs(abs(after_correction1-weather->alfa_now)-180)){
      //  cout<<"Odpadam z korekta o "<<correction<<" stopni - lodz nr: "<<id;
        after_correction = after_correction1;
    }
    
    course = after_correction;
    if(after_correction<0)
        after_correction+= 360;
    if(after_correction>360)
        after_correction-=360;
    return after_correction;
}
void Boat::refresh(Weather* weather, Buoy* buoy, Boat *boat){
	int X_length = buoy->X_position-X_position;
    int Y_length = Y_position-buoy->Y_position;
	course = atan((float)Y_length/(float)X_length)*(float)180/(float)M_PI;
	if(X_length<0)
		course+=180;
	if(Y_length<0&&X_length>0)
		course+=360;	
	//Obliczony optymalny kurs na bojê - teraz sprawdzam czy mogê p³yn¹æ, poniewa¿ idealnie pod wiatr nie da siê p³yn¹æ
    if(abs(abs(course-weather->alfa_now)-180)<30){
        float correction = 30 - abs(abs(course-weather->alfa_now)-180);
        if(correction>0)
            course = luffing(course, correction, weather);
         //   cout<<"Kurs po korekcji: "<<course;
        
    }
    checkColisions(weather, boat);
		speed = abs(abs(course-weather->alfa_now)-180)/100;
		speed*=weather->Wind_now;
		speed=((float)((float)s_size*3/(float)weight)*0.2*(float)speed)+speed*0.8; //wp³yw stosunku wielkoœci ¿agla do ciê¿aru ³ódki
		speed=(0.9*speed)+(0.1*speed*c_skill/5); //wp³yw umiejêtnoœci za³ogi
		if(weather->Sea_now+c_skill-5>7){	//wywrócenie siê ³ódki
			ruin = true;
			id_buoy = 0;
			distance = 0;
			return;}
		speed=(0.9*speed)+(speed*0.5/(abs((weight/10)-weather->alfa_now)+1)); //wp³yw stosunku si³y wiatru do masy ³ódki 
		/*jak ³atwo zauwa¿yæ prêdkoœæ ³ódki w ekstremalnym przypadku mo¿e byæ wiêksza od prêdkoœci wiatru, jednak zdarzaj¹ siê 
		takie sytuacje na regatach) */
		int last_X = X_position;
		int last_Y = Y_position;
		Y_position-=sin(course*M_PI/180)*speed;
		X_position+=cos(course*M_PI/180)*speed;
		X_length = buoy->X_position-X_position;
		Y_length = Y_position-buoy->Y_position;
		distance=sqrt((X_length*X_length)+(Y_length*Y_length));
		distance/=50;
        if(distance<0.2)
            id_buoy++;
}
