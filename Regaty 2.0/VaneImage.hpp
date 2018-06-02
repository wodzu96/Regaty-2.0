//
//  VaneImage.hpp
//  Regaty 2.0
//
//  Created by Piotr Wodzynski on 16.05.2018.
//  Copyright © 2018 Piotr Wodzynski. All rights reserved.
//


#include <stdio.h>
#ifndef VaneImage_hpp
#define VaneImage_hpp

#include "SFML/Graphics.hpp"

#include <stdio.h>
using namespace sf;
class VaneImage : public Drawable{
public:
    VaneImage(float X, float Y, float direction);
    VaneImage() = delete;
    ~VaneImage() = default;
    void update(float direction);
private:
    ConvexShape rectangle;
    ConvexShape triangle;
    void draw(RenderTarget& target, RenderStates state) const override;
};

#endif /* VaneImage_hpp */
