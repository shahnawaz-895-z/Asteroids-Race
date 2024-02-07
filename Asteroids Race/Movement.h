#pragma once
#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>

class movement {
public:
    movement() {

    }
    virtual void move(float speedx, float speedy) = 0;

};
