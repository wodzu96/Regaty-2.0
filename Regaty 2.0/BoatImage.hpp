//
//  BoatImage.hpp
//  Test SFML
//
//  Created by Piotr Wodzynski on 15.05.2018.
//  Copyright © 2018 Piotr Wodzynski. All rights reserved.
//

#ifndef BoatImage_hpp
#define BoatImage_hpp

#include "SFML/Graphics.hpp"

#include <stdio.h>
using namespace sf;
class BoatImage : public Drawable{
public:
    BoatImage(float X, float Y, float rotate, float sailRotation);
    BoatImage() = delete;
    ~BoatImage() = default;
private:
    ConvexShape polygon;
    ConvexShape sail;
    void draw(RenderTarget& target, RenderStates state) const override;
};
#endif /* BoatImage_hpp */
