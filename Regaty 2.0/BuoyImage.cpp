//
//  BuoyImage.cpp
//  Regaty 2.0
//
//  Created by Piotr Wodzynski on 16.05.2018.
//  Copyright © 2018 Piotr Wodzynski. All rights reserved.
//

#include "BuoyImage.hpp"

BuoyImage::BuoyImage(float X, float Y){
    shape.setRadius(buoyRadious);
    shape.setFillColor(Color::White);
    shape.setPosition(X, Y);
}
void BuoyImage::draw(RenderTarget& target, RenderStates state) const{
    target.draw(this->shape, state);
}
