


#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <iomanip>
// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"
#include "BoatImage.hpp"
#include "BuoyImage.hpp"
#include "VaneImage.hpp"
#include "Boat.h"
#include <thread>
#include <string>
#include <sstream>
#include <unistd.h>

static const int boats = 5;
static const int buoys = 40;
thread boats_thread[boats];
thread weather_thread;
pthread_mutex_t    boat_mutexes[boats];
pthread_mutex_t buoy_mutexes[buoys];
pthread_mutex_t weather_mutex = PTHREAD_MUTEX_INITIALIZER;
int last_rank = 0;
Boat *boat;
Weather *weather;
Buoy *buoy;

using namespace std;
void waitForMakeMutexesBoatsFree(){
    for(int i = 0; i<boats; ++i) {
        pthread_mutex_lock(&boat_mutexes[i]);
    }
}

void unlockAllBoatsMutexes(){
    for(int i = 0; i<boats; ++i) {
        pthread_mutex_unlock(&boat_mutexes[i]);
    }
}
void waitForAllMutexesFree(){
    waitForMakeMutexesBoatsFree();
     pthread_mutex_lock(&weather_mutex);
    for(int i = 0; i<buoys; ++i) {
        pthread_mutex_lock(&buoy_mutexes[i]);
    }
}

void unlockAllMutexes(){
    unlockAllBoatsMutexes();
    pthread_mutex_unlock(&weather_mutex);
    for(int i = 0; i<buoys; ++i) {
        pthread_mutex_unlock(&buoy_mutexes[i]);
    }
}

string makeRanking(){

    ostringstream osstream;
    for(int j = 0; j<boats; ++j){
        if(boat[j].id_buoy==buoys){
                        ++boat[j].id_buoy;
                        boat[j].distance=last_rank;
                        ++last_rank;
                    }
                    if(boat[j].id_buoy==buoys+1)
                        osstream<<j+1<<". Boat nr: "<<boat[j].id<<" finished."<<endl;
                    else if(boat[j].ruin)
                        osstream<<"Boat nr: "<<boat[j].id<<" failed."<<endl;
                    else{
                        osstream<<j+1<<". Boat nr: "<<boat[j].id<<".Distance to buoy nr "<<boat[j].id_buoy<<" : "<<boat[j].distance<<" miles with speed: "<<boat[j].speed<<endl;
                        
                    }
                }
   
    return osstream.str();
}

string createRaport(){
    ostringstream osstream;
    for(int i = 0; i<boats; ++i){
        osstream << boat[i].getBoatRaport();
    }
    return osstream.str();
}

bool *visibleBuoys(){
    bool *visibleBuoys = new bool[buoys];
    for(int i = 0; i<buoys; ++i)
        visibleBuoys[i] = false;
    for(int i = 0; i<boats; ++i)
        if(!boat[i].ruin)
            visibleBuoys[boat[i].id_buoy] = true;
    return visibleBuoys;
}

void ranking(Boat *boat){
    for(int i=0;i<boats;i++)
        for(int j=1;j<boats-i;j++) //p�tla wewn�trzna
            if(boat[j].id_buoy>boat[j-1].id_buoy){
                //zamiana miejscami
                Boat swap = *(boat+j);
                *(boat+j)=*(boat+(j-1));
                *(boat+(j-1))=swap;
            }
    for(int i=0;i<boats;i++)
        for(int j=1;j<boats-i;j++) //p�tla wewn�trzna
            if(boat[j-1].distance>boat[j].distance&&boat[j].id_buoy==boat[j-1].id_buoy){
                //zamiana miejscami
                Boat swap = *(boat+j);
                *(boat+j)=*(boat+(j-1));
                *(boat+(j-1))=swap;
            }
}
void renderingThread(sf::RenderWindow* window)
{
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return;
    }
    VaneImage vane(2200, 100, 0);
    
    string raport = createRaport();
    // the rendering loop
    while (window->isOpen())
    {
        waitForAllMutexesFree();
        // Clear screen
        window->clear(Color::Blue);
        

        
                for(int j = 0; j<boats; ++j){
                    if(boat[j].id_buoy<buoys && !boat[j].ruin){
                        window->draw(BoatImage(boat[j].X_position, boat[j].Y_position, -boat[j].course, 0));
                    }
                }
                ranking(boat);
        
        bool *myVisibleBuoys = visibleBuoys();
        for(int i = 0; i<buoys; ++i){
            if(myVisibleBuoys[i])
                window->draw(BuoyImage(buoy[i].X_position, buoy[i].Y_position));
        }
        
        ranking(boat);
        // Create a graphical text to display

        vane.update(90-weather->alfa_now);
        sf::Text text(makeRanking(), font, 30);
        text.setFillColor(sf::Color::White);
        window->draw(vane);
        window->draw(text);
        
        std::ostringstream ss;
        ss <<std::setprecision(3)<< weather->Wind_now << " knots"<< std::endl<< weather->Sea_now <<" beufort";
        std::string s(ss.str());
        text.setString(s);
        text.setPosition(2100, 150);
        window->draw(text);
        
        text.setString(raport);
        text.setFillColor(sf::Color::Black);
        text.setPosition(1340, 1200);
        window->draw(text);
        
        // Update the window
        window->display();
        unlockAllMutexes();
        usleep(30000);
    }
}



void boat_thread(int tid) {
    while(boats_thread[tid].joinable()){
        bool shouldBreak = false;
        waitForMakeMutexesBoatsFree();
            pthread_mutex_lock(&weather_mutex);
            int buoy_id = boat[tid].id_buoy;
            pthread_mutex_lock(&buoy_mutexes[buoy_id]);
            boat[tid].refresh(weather, &buoy[buoy_id], boat);
            pthread_mutex_unlock(&buoy_mutexes[buoy_id]);
            pthread_mutex_unlock(&weather_mutex);
        shouldBreak = boat[tid].id_buoy==buoys+1 || boat[tid].ruin;
        unlockAllBoatsMutexes();
        if(shouldBreak)
            break;
        usleep(30000);
    }
    boats_thread[tid].detach();
}
void weather_thread_initializer(){
    while (weather_thread.joinable()) {
        pthread_mutex_lock(&weather_mutex);
        weather->refresh();
        pthread_mutex_unlock(&weather_mutex);
        usleep(30000);
    }
    weather_thread.detach();
    
}


int main(int, char const**)
{
    srand(time(NULL));
    
    weather = new Weather();
    buoy = new Buoy[buoys];
    boat  = new Boat[boats];
    pthread_mutex_init(&weather_mutex, NULL);
    weather_thread = thread(weather_thread_initializer);
    
    for(int i = 0; i<buoys; ++i){
        buoy_mutexes[i] = PTHREAD_MUTEX_INITIALIZER;
        pthread_mutex_init(&buoy_mutexes[i], NULL);
    }
    
    for(int i = 0; i<boats; ++i){
        boat_mutexes[i] = PTHREAD_MUTEX_INITIALIZER;
        pthread_mutex_init(&boat_mutexes[i],NULL);
        boats_thread[i] = thread(boat_thread, i);
        boat[i].setStartPosition(boats);
    }
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(2400, 1600), "SFML window");


    sf::Thread thread(&renderingThread, &window);
    thread.launch();
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }

    }

    return EXIT_SUCCESS;
}
