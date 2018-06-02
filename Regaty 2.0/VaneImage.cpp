//
//  BoatImage.cpp
//  Test SFML
//
//  Created by Piotr Wodzynski on 15.05.2018.
//  Copyright © 2018 Piotr Wodzynski. All rights reserved.
//

#include "VaneImage.hpp"

VaneImage::VaneImage(float X, float Y, float direction){
    rectangle.setPointCount(4);
    rectangle.setPoint(0, Vector2f(-5, 30));
    rectangle.setPoint(1, Vector2f(5, 30));
    rectangle.setPoint(2, Vector2f(5, -30));
    rectangle.setPoint(3, Vector2f(-5, -30));
    rectangle.setOutlineColor(sf::Color::Red);
    rectangle.setOutlineThickness(3);
    rectangle.setFillColor(Color::White);
    rectangle.setRotation(direction);
    rectangle.setPosition(X, Y);
    
    triangle.setPointCount(3);
    triangle.setPoint(0, Vector2f(0, -40));
    triangle.setPoint(1, Vector2f(20, -10));
    triangle.setPoint(2, Vector2f(-20, -10));
    triangle.setOutlineColor(sf::Color::Red);
    triangle.setOutlineThickness(3);
    triangle.setFillColor(Color::White);
    triangle.setRotation(direction);
    triangle.setPosition(X, Y);
}
void VaneImage::draw(RenderTarget& target, RenderStates state) const{
    target.draw(this->rectangle, state);
    target.draw(this->triangle, state);
}
void VaneImage::update(float direction){
    rectangle.setRotation(direction);
    triangle.setRotation(direction);
   
}
