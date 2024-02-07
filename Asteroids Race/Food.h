#pragma once
#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
class Food
{
public:
    Food() {

    }
    ~Food() {

    }

private:

};

class redfood
{
public:
	RectangleShape redf;
	redfood() {

	}
	redfood(float x, float y) {
		redf.setSize(Vector2f(20.f, 15.f));
		redf.setPosition(x, y);
		redf.setFillColor(Color::Red);
	}
	~redfood() {

	}

private:

};

class greenfood
{
public:
	CircleShape greenf;
	greenfood() {

	}
	greenfood(float x, float y, float radius) {
		greenf.setPosition(x, y);
		greenf.setRadius(radius);
		greenf.setFillColor(sf::Color::Green);
	}
	~greenfood() {

	}

private:

};
