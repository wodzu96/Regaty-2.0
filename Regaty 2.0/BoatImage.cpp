//
//  BoatImage.cpp
//  Test SFML
//
//  Created by Piotr Wodzynski on 15.05.2018.
//  Copyright © 2018 Piotr Wodzynski. All rights reserved.
//

#include "BoatImage.hpp"

BoatImage::BoatImage(float X, float Y, float rotate, float sailRotation){
    polygon.setPointCount(5);
    polygon.setPoint(0, Vector2f(-30, -5));
    polygon.setPoint(1, Vector2f(0, -5));
    polygon.setPoint(2, Vector2f(25, 0));
    polygon.setPoint(3, Vector2f(0, 5));
    polygon.setPoint(4, Vector2f(-30, 5));
    polygon.setOutlineColor(sf::Color::Red);
    polygon.setOutlineThickness(3);
    polygon.setFillColor(Color::White);
    polygon.setRotation(rotate);
    polygon.setPosition(X, Y);
    
    sail.setPointCount(4);
    sail.setPoint(0, Vector2f(0, 0.5));
    sail.setPoint(1, Vector2f(0, -0.5));
    sail.setPoint(2, Vector2f(-40, -0.5));
    sail.setPoint(3, Vector2f(-40, 0.5));
    sail.setOutlineColor(sf::Color::Red);
    sail.setOutlineThickness(1);
    sail.setFillColor(Color::Red);
    sail.setRotation(rotate+sailRotation);
    sail.setPosition(X, Y);
}
void BoatImage::draw(RenderTarget& target, RenderStates state) const{
    target.draw(this->polygon, state);
    target.draw(this->sail, state);
}
void BoatImage::update(float X, float Y, float rotate, float sailRotation){
    polygon.setRotation(rotate);
    polygon.setPosition(X, Y);
    
    sail.setRotation(rotate+sailRotation);
    sail.setPosition(X, Y);
}
