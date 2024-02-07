#pragma once
#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>


using namespace std;
using namespace sf;


class Box
{
public:
    RectangleShape shape;
    int direction;

    Box()
        : direction(0)
    {

    }

    Box(float x, float y, float width, float height, int initialDirection)
        : direction(initialDirection)
    {
        shape.setSize(Vector2f(width, height));
        shape.setPosition(x, y);
        shape.setFillColor(Color::Red);
    }

    void move(float speed, float offsetY)
    {
        shape.move(speed * direction, offsetY);
    }
};
