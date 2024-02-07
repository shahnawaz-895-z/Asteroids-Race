#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include"Box.h"
#include"Food.h"
#include"Movement.h"
#include"Player.h"
#include"Opponent.h"
#include<fstream>


using namespace std;
using namespace sf;

const char title[] = "OOP-Project, Spring-2023";
const int numSmallBoxes = 3;


class Game
{
private:
    Sprite background;
    Texture bg_texture;
    Box smallBoxes[numSmallBoxes];
    Player player;
    Font font;
    Text livesText;
    Text pauseText;
    Text unpauseText;
    bool isPaused;
    static const int numOpponents = 4;
    Opponent opponents[numOpponents];
    greenfood green[30];
    redfood red[30];
    int foodcount = 0;
    Text Score;
    int score;
public:
    Game()
    {
        isPaused = false;
        bg_texture.loadFromFile("img/background.jpg");
        background.setTexture(bg_texture);
        background.setScale(2, 1.5);
        initializeSmallBoxes();
        player = Player(400.f, 500.f);
        if (!font.loadFromFile("RubikBubbles-Regular.ttf")) // Change "arial.ttf" to the path of your font file
        {
            cerr << "Error loading font" << endl;
        }
        score = 0;

        // Initialize lives text
        livesText.setFont(font);
        livesText.setCharacterSize(20);
        livesText.setFillColor(Color::White);
        livesText.setPosition(10, 10);
        // Initialize pause text
        pauseText.setFont(font);
        pauseText.setCharacterSize(70);
        pauseText.setFillColor(Color::White);
        pauseText.setPosition(170, 200);
        pauseText.setString("Game Paused!");
        // Initialize unpause text
        unpauseText.setFont(font);
        unpauseText.setCharacterSize(30);
        unpauseText.setFillColor(Color::White);
        unpauseText.setPosition(230, 380);
        unpauseText.setString("Press Esc to resume:");
        //Initialize Score
        Score.setFont(font);
        Score.setCharacterSize(20);
        Score.setFillColor(Color::White);
        Score.setPosition(120, 10);
        opponents[0] = Opponent(300.f, 120.f, 30.f, 30.f, 0.05f);
        opponents[1] = Opponent(500.f, 70.f, 30.f, 30.f, 0.05f);
        opponents[2] = Opponent(620.f, 520.f, 30.f, 30.f, 0.05f);
        opponents[3] = Opponent(110.f, 420.f, 30.f, 30.f, 0.05f);
        //Initialize Foods
        for (int i = 0; i < 30; ++i)
        {
            float randomX = static_cast<float>(rand() % 700 + 50); // Random X position within the window
            float randomY = static_cast<float>(rand() % 500 + 50); // Random Y position within the window

            green[i] = greenfood(randomX, randomY, 5.f); // Adjust the radius as needed
        }

        // Initialize red food array
        for (int i = 0; i < 30; ++i)
        {
            float randomX = static_cast<float>(rand() % 700 + 50); // Random X position within the window
            float randomY = static_cast<float>(rand() % 500 + 50); // Random Y position within the window

            red[i] = redfood(randomX, randomY); // Adjust the radius as needed
        }
    }

    void initializeSmallBoxes()
    {
        smallBoxes[0] = Box(200.f, 300.f, 30.f, 30.f, 1);
        smallBoxes[1] = Box(400.f, 500.f, 30.f, 30.f, -1);
        smallBoxes[2] = Box(500.f, 600.f, 30.f, 30.f, -1);
    }

    void moveOpponents()
    {
        for (int i = 0; i < numOpponents; i++)
        {
            // Move opponent based on its current speed
            opponents[i].move(opponents[i].speed, 0.0f);

            // Check for collisions with boundaries
            if (oppisCollisionWithBoundaries(opponents[i]))
            {
                // Opponent collided with a wall, change direction vertically
                opponents[i].speed = -opponents[i].speed;

                // Move opponent in the new direction
                opponents[i].move(0.0f, opponents[i].speed);
            }

            // Debugging output
            //cout << "Opponent position: " << opponents[i].getPosition().x << ", " << opponents[i].getPosition().y << endl;
        }
    }






    void drawOpponents(RenderWindow& window)
    {
        for (int i = 0; i < numOpponents; ++i)
        {
            window.draw(opponents[i].shape); // Assuming shape is a public member in Opponent
        }
    }

    void drawLine(RenderWindow& window, float x, float y, float width, float height)
    {
        RectangleShape line(Vector2f(width, height));
        line.setPosition(x, y);
        line.setFillColor(Color::Red);
        window.draw(line);
    }

    void drawCar(RenderWindow& window)
    {
        player.draw(window);
    }

    void drawFood(RenderWindow& window)
    {
        // Draw green food within the map boundaries without overlapping with opponents
        for (int i = 0; i < 30; ++i)
        {
            FloatRect greenBounds = green[i].greenf.getGlobalBounds();
            if (isWithinMapBounds(greenBounds) && !collidesWithLines(greenBounds) && !collidesWithOtherFood(greenBounds, i, true) && !collidesWithOpponents(greenBounds))
            {
                window.draw(green[i].greenf);
            }
        }

        // Draw red food within the map boundaries without overlapping with opponents
        for (int i = 0; i < 30; ++i)
        {
            FloatRect redBounds = red[i].redf.getGlobalBounds();
            if (isWithinMapBounds(redBounds) && !collidesWithLines(redBounds) && !collidesWithOtherFood(redBounds, i, false) && !collidesWithOpponents(redBounds))
            {
                window.draw(red[i].redf);
            }
        }
    }

    bool collidesWithOpponents(const FloatRect& bounds)
    {
        // Check for collisions with opponents
        for (int i = 0; i < numOpponents; ++i)
        {
            if (bounds.intersects(opponents[i].getbounds()))
            {
                return true;
            }
        }
        return false;
    }

    bool collidesWithLines(const FloatRect& bounds)
    {
        // Iterate through all the lines and check for collision
        for (int i = 0; i < 24; ++i)
        {
            FloatRect lineBounds = getLineBounds(i);
            if (bounds.intersects(lineBounds))
            {
                return true;
            }
        }

        return false;
    }
    bool collidesWithOtherFood(const FloatRect& bounds, int currentIndex, bool isGreen)
    {
        // Check for collisions with other food items of the same type
        for (int i = 0; i < 30; ++i)
        {
            if (i != currentIndex)
            {
                FloatRect otherBounds = (isGreen) ? green[i].greenf.getGlobalBounds() : red[i].redf.getGlobalBounds();
                if (bounds.intersects(otherBounds))
                {
                    return true;
                }
            }
        }

        return false;
    }

    void saveScoreToFile() {
        // Open a file stream to save the score in append mode
        std::ofstream outFile("score.txt", std::ios::app);

        if (outFile.is_open()) {
            // Write the player's score to the file
            outFile << "Score: " << score << std::endl;

            // Close the file stream
            outFile.close();

            std::cout << "Score appended to score.txt" << std::endl;
        }
        else {
            std::cerr << "Unable to open the score.txt file for writing!" << std::endl;
        }
    }
    void eatFood(RenderWindow& window)
    {
        // Check for collisions with green food
        for (int i = 0; i < 30; ++i)
        {
            if (player.getbounds().intersects(green[i].greenf.getGlobalBounds()))
            {
                // Player collided with green food, remove the green food from the array
                green[i] = greenfood(); // Reset the green food object
                foodcount++;
                player.incrementlives();
                livesText.setString("Lives: " + to_string(player.getlives()));
                window.draw(livesText);
                
                score+=20;
                Score.setString("Score: " + to_string(score));
                window.draw(Score);

                cout << foodcount << endl;
                if (foodcount==44)
                {
                    saveScoreToFile();
                    window.close();
                }
            }
        }

        // Check for collisions with red food
        for (int i = 0; i < 30; ++i)
        {
            if (player.getbounds().intersects(red[i].redf.getGlobalBounds()))
            {
                // Player collided with red food, remove the red food from the array
                red[i] = redfood(); // Reset the red food object
                foodcount++;
                cout << foodcount << endl;
                score += 10;
                Score.setString("Score: " + to_string(score));
                window.draw(Score);
                if (foodcount == 44)
                {
                    saveScoreToFile();
                    window.close();
                }
                
            }
        }
    }

    bool isWithinMapBounds(const FloatRect& bounds)
    {
        FloatRect mapBounds(120.f, 60.f, 580.f, 470.f);  // Adjust the values based on your map boundaries

        return mapBounds.intersects(bounds);
    }

    bool checkCollision(const FloatRect& rect1, const FloatRect& rect2)
    {
        return rect1.intersects(rect2);
    }

    bool isCollisionWithBoundaries()
    {
        FloatRect carBounds = player.getbounds();

        // Iterate through all the lines and check for collision
        // Return true if there is a collision with any line
        for (int i = 0; i < 24; ++i)
        {
            FloatRect lineBounds = getLineBounds(i);
            if (checkCollision(carBounds, lineBounds))
            {
                return true;
            }
        }

        return false;
    }
    bool oppisCollisionWithBoundaries(Opponent o)
    {
        FloatRect oppBounds = o.getbounds();

        // Iterate through all the lines and check for collision
        // Return true if there is a collision with any line
        for (int i = 0; i < 24; ++i)
        {
            FloatRect lineBounds = getLineBounds(i);
            if (checkCollision(oppBounds, lineBounds))
            {
                return true;
            }
        }

        return false;
    }


    FloatRect getLineBounds(int i)
    {
        // Return the bounds of the ith line
        float x, y, width, height;
        switch (i)
        {
            // Top horizontal lines
        case 0:
            x = 100.f;
            y = 60.f;
            width = 250.f;
            height = 5.0f;
            break;
        case 1:
            x = 452.f;
            y = 60.f;
            width = 250.f;
            height = 5.0f;
            break;
        case 2:
            x = 150.f;
            y = 100.f;
            width = 200.f;
            height = 5.0f;
            break;
        case 3:
            x = 452.f;
            y = 100.f;
            width = 200.f;
            height = 5.0f;
            break;
        case 4:
            x = 200.f;
            y = 150.f;
            width = 150.f;
            height = 5.0f;
            break;
        case 5:
            x = 200.f;
            y = 450.f;
            width = 150.f;
            height = 5.0f;
            break;
            // Bottom horizontal lines
        case 6:
            x = 100.f;
            y = 550.f;
            width = 250.f;
            height = 5.0f;
            break;
        case 7:
            x = 452.f;
            y = 550.f;
            width = 250.f;
            height = 5.0f;
            break;
        case 8:
            x = 150.f;
            y = 510.f;
            width = 200.f;
            height = 5.0f;
            break;
        case 9:
            x = 452.f;
            y = 510.f;
            width = 200.f;
            height = 5.0f;
            break;
        case 10:
            x = 450.f;
            y = 150.f;
            width = 150.f;
            height = 5.0f;
            break;
        case 11:
            x = 450.f;
            y = 450.f;
            width = 150.f;
            height = 5.0f;
            break;
            // Left vertical lines
        case 12:
            x = 100.f - 5.0f / 2.f;
            y = 60.f;
            width = 5.0f;
            height = 200.f;
            break;
        case 13:
            x = 100.f - 5.0f / 2.f;
            y = 350.f;
            width = 5.0f;
            height = 200.f;
            break;
        case 14:
            x = 150.f - 5.0f / 2.f;
            y = 106.f;
            width = 5.0f;
            height = 155.f;
            break;
        case 15:
            x = 150.f - 5.0f / 2.f;
            y = 350.f;
            width = 5.0f;
            height = 155.f;
            break;
        case 16:
            x = 200.f - 5.0f / 2.f;
            y = 152.f;
            width = 5.0f;
            height = 110.f;
            break;
        case 17:
            x = 200.f - 5.0f / 2.f;
            y = 350.f;
            width = 5.0f;
            height = 110.f;
            break;
            // Right vertical lines
        case 18:
            x = 700.f + 5.0f / 2.f;
            y = 60.f;
            width = 5.0f;
            height = 200.f;
            break;
        case 19:
            x = 700.f + 5.0f / 2.f;
            y = 350.f;
            width = 5.0f;
            height = 200.f;
            break;
        case 20:
            x = 650.f + 5.0f / 2.f;
            y = 106.f;
            width = 5.0f;
            height = 155.f;
            break;
        case 21:
            x = 650.f + 5.0f / 2.f;
            y = 350.f;
            width = 5.0f;
            height = 155.f;
            break;
        case 22:
            x = 600.f + 5.0f / 2.f;
            y = 152.f;
            width = 5.0f;
            height = 110.f;
            break;
        case 23:
            x = 600.f + 5.0f / 2.f;
            y = 350.f;
            width = 5.0f;
            height = 110.f;
            break;
        default:
            x = y = width = height = 0;
            break;
        }

        return FloatRect(x, y, width, height);
    }

    void movePlayer(float speed, RenderWindow& window)
    {
        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            player.move(-speed, 0);
            handleCollisionWithOpponent(window);
            if (isCollisionWithBoundaries())
                player.move(speed, 0); // Move back if there is a collision
        }
        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            player.move(speed, 0);
            handleCollisionWithOpponent(window);
            if (isCollisionWithBoundaries())
                player.move(-speed, 0); // Move back if there is a collision
        }
        if (Keyboard::isKeyPressed(Keyboard::Up))
        {
            player.move(0, -speed);
            handleCollisionWithOpponent(window);
            if (isCollisionWithBoundaries())
                player.move(0, speed); // Move back if there is a collision
        }
        if (Keyboard::isKeyPressed(Keyboard::Down))
        {
            player.move(0, speed);
            handleCollisionWithOpponent(window);
            if (isCollisionWithBoundaries())
                player.move(0, -speed); // Move back if there is a collision
        }
    }
   
    void handleCollisionWithOpponent(RenderWindow& window)
    {
        // Check for collisions with opponents
        for (int i = 0; i < numOpponents; ++i)
        {
            if (player.getbounds().intersects(opponents[i].getbounds()))
            {
                cout << "Collide" << endl;
                cout << "Lives: " << player.getlives();
                // Player collided with an opponent, decrement lives
                player.decrementlives();
                cout << "Lives: " << player.getlives();
                // Update livesText with the current lives count
                livesText.setString("Lives: " + to_string(player.getlives()));

                // Reset player position if lives are still remaining
                if (player.getlives() > 0)
                {
                    player.respawn(400, 500);
                    drawCar(window);
                }
                else
                {
                    // Game over if lives are exhausted
                    cout << "Game Over! You ran out of lives." << endl;
                    saveScoreToFile();
                    window.close();
                }
            }
        }
    }
    bool checkCollisionWithWalls(const FloatRect& rect, float speedX, float speedY)
    {
        // Iterate through all the lines and check for collision
        for (int i = 0; i < 24; ++i)
        {
            FloatRect lineBounds = getLineBounds(i);
            FloatRect movedRect(rect.left + speedX, rect.top + speedY, rect.width, rect.height);

            if (checkCollision(movedRect, lineBounds))
            {
                return true;
            }
        }

        return false;
    }

    


    void drawGameboard(RenderWindow& window)
    {
        float lineThickness = 5.0f;

        // Draw lines
        for (int i = 0; i < 24; ++i)
        {
            FloatRect lineBounds = getLineBounds(i);
            drawLine(window, lineBounds.left, lineBounds.top, lineBounds.width, lineBounds.height);
        } 

        drawCar(window);
        //cout << player.getlives() << endl;
        livesText.setString("Lives: " + to_string(player.getlives()));
        Score.setString("Score: " + to_string(score));
        window.draw(Score);
        window.draw(livesText);
        drawOpponents(window);
        // Draw food
        drawFood(window);
        window.display();
    }

    void start_game()
    {
        srand(time(0));
        RenderWindow window(VideoMode(800, 600), title);
        Clock clock;
        float timer = 0;

        while (window.isOpen())
        {
            float time = clock.getElapsedTime().asSeconds();
            clock.restart();
            timer += time;

            Event e;
            while (window.pollEvent(e))
            {
                if (e.type == Event::Closed)
                {
                    window.close();
                }
                else if (e.type == Event::KeyPressed)
                {
                    if (e.key.code == Keyboard::Escape)
                    {
                        // Toggle pause when Escape is pressed
                        isPaused = !isPaused;
                    }
                }
            }

            if (!isPaused)
            {
                window.clear(Color::Black);
                window.draw(background);
                movePlayer(0.05f,window);
                moveOpponents(); 
                eatFood(window);
                drawGameboard(window);

                if (player.getlives() <= 0)
                {
                    cout << "Game Over! You ran out of lives." << endl;
                    window.close();
                }
            }
            else
            {
                RectangleShape overlay(Vector2f(800, 600));
                overlay.setFillColor(Color(0, 0, 0, 150));  // Semi-transparent black
                window.draw(overlay);

                // Display the pause text
                window.draw(pauseText);
                window.draw(unpauseText);
                window.display();
                continue;
            }
           
        }
    }
};
