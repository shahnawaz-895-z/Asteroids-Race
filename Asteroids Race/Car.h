#pragma once
#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
using namespace std;
using namespace sf;

class Car
{
public:
    Car() {

    }
    RectangleShape carBody;

    Car(float x, float y)
    {
        carBody.setSize(Vector2f(30.f, 15.f));
        carBody.setPosition(x, y);
        carBody.setFillColor(Color::Blue);
    }

    void move(float speedX, float speedY)
    {
        carBody.move(speedX, speedY);
    }
};