#include<iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;
#include "menu.h"
int main()
{
    Menu m;
    RenderWindow window(VideoMode(800, 600), title);
    m.display_gamescreen(window);
    return 0;
}
