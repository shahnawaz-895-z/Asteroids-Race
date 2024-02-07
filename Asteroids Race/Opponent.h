#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;


class Opponent : public movement{
public:
    RectangleShape shape;
    float speed;
    FloatRect getbounds() {
        return shape.getGlobalBounds();
    }
    Opponent() {

    }
    Opponent(float x, float y, float width, float height, float initialSpeed)
        : speed(initialSpeed)
    {
        shape.setSize(Vector2f(width, height));
        shape.setPosition(x, y);
        shape.setFillColor(Color::Blue);

    }
    Vector2f getPosition() const {
        return shape.getPosition();
    }

    void move(float speedX, float speedY) {
        
        shape.move(speedX, speedY);
        
    }
    
};
