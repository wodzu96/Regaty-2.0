//
//  BoatImage.hpp
//  Test SFML
//
//  Created by Piotr Wodzynski on 15.05.2018.
//  Copyright © 2018 Piotr Wodzynski. All rights reserved.
//

#ifndef BuoyImage_hpp
#define BuoyImage_hpp

#include "SFML/Graphics.hpp"

#include <stdio.h>
using namespace sf;
class BuoyImage : public Drawable{
public:
    BuoyImage(float X, float Y);
    BuoyImage() = delete;
    ~BuoyImage() = default;
private:
    CircleShape shape;
    const float buoyRadious{5.0f};
    void draw(RenderTarget& target, RenderStates state) const override;
};
#endif /* BoatImage_hpp */
