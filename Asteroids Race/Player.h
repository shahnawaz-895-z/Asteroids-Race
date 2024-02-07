#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include"Movement.h"
#include"Car.h"
using namespace std;
using namespace sf;

class Player : public movement
{
private:
    string name;
    int lives;
    Car car;
public:
    FloatRect getbounds() {
        return car.carBody.getGlobalBounds();
    }

    Player() {
        lives = 3;
    }

    Player(float x, float y)
    {
        lives = 3;
        car = Car(x, y);
    }
    void respawn(float x, float y) {
        car = Car(x, y);
    }
    Vector2f getPosition() const {
        return car.carBody.getPosition();
    }
    void move(float speedX, float speedY)
    {
        car.move(speedX, speedY);
    }
    int getlives() {
        return lives;
    }
    void draw(RenderWindow& window)
    {
        window.draw(car.carBody);
    }

    void decrementlives() {
        lives--;
    }

    void incrementlives() {
        lives++;
    }
};