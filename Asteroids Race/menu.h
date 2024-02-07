#include <SFML/Graphics.hpp>
#include "game.h"

class Menu {
public:

    //add menu attributes here
    Menu()
    {
        
        //constructors body
    }
    void display_gamescreen(RenderWindow& window) {
        Font font;
        if (!font.loadFromFile("RubikBubbles-Regular.ttf"))  // Replace with the path to your font file
        {
            cout << "Error loading font" << std::endl;
            return;
        }
        Text title("Dodge 'Em", font, 100);
        title.setPosition(150, 50);
        window.draw(title);
        Text sub("By Ahyan Ali Khan", font, 30);
        sub.setPosition(270, 300);
        window.draw(sub);
        Text sub2("Press Enter To Continue:", font, 30);
        sub2.setPosition(200, 400);
        window.draw(sub2);
        window.display();
        Event event;
        while (window.waitEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
                break;
            }

            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Enter)
                {
                    
                    
                    display_menu(window);
                    break;
                }
            }
        }
    }
    void instructions(RenderWindow &window) {
        window.clear();
        Font font;
        if (!font.loadFromFile("RubikBubbles-Regular.ttf"))  // Replace with the path to your font file
        {
            cout << "Error loading font" << std::endl;
            return;
        }
        Text title("Dodge 'Em", font, 100);
        title.setPosition(150, 50);
        window.draw(title);
        Text sub("Welcome to Dodge 'Em! Use arrow keys or swipe gestures to navigate\n your car through the maze, dodging other cars and obstacles.\n Earn points for each successful dodge, but watch out � collisions\n end the game.\n The faster and more strategic you are, the higher your score. \nGet ready for the Dodge 'Em Challenge and see how many cars you\n can dodge!", font, 20);
        sub.setPosition(50, 230);
        window.draw(sub);
        Text sub2("Press Enter To Continue:", font, 30);
        sub2.setPosition(200, 450);
        window.draw(sub2);
        window.display();
        Event event;
        while (window.waitEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
                break;
            }

            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Enter)
                {


                    display_menu(window);
                    break;
                }
            }
        }
        window.display();

    }
    void highscore(RenderWindow& window) {
        window.clear();
        const int maxScores = 10;
        int scores[maxScores];

        std::ifstream inFile("score.txt");
        if (inFile.is_open()) {
            // Read scores from the file
            int count = 0;
            std::string line;
            while (getline(inFile, line) && count < maxScores) {
                // Extract the numeric value from the line
                size_t pos = line.find(':');
                if (pos != std::string::npos) {
                    scores[count++] = std::stoi(line.substr(pos + 1));
                }
            }

            // Close the file stream
            inFile.close();

            // Sort the scores in descending order (you can use any sorting algorithm)
            for (int i = 0; i < count - 1; ++i) {
                for (int j = i + 1; j < count; ++j) {
                    if (scores[i] < scores[j]) {
                        // Swap scores[i] and scores[j]
                        int temp = scores[i];
                        scores[i] = scores[j];
                        scores[j] = temp;
                    }
                }
            }

            // Display high scores on the SFML window
            
            Font font;
            if (!font.loadFromFile("RubikBubbles-Regular.ttf")) {
                std::cerr << "Error loading font" << std::endl;
                return;
            }

            Text title("High Scores", font, 40);
            title.setPosition(250, 20);

            for (int i = 0; i < count; ++i) {
                Text scoreText("Score: " + std::to_string(scores[i]), font, 30);
                scoreText.setPosition(50, 80 + i * 25);
                window.draw(scoreText);
            }

            window.draw(title);
            

            Text sub2("Press Enter To Continue:", font, 30);
            sub2.setPosition(200, 450);
            window.draw(sub2);
            window.display();
            Event event;
            while (window.waitEvent(event))
            {
                if (event.type == Event::Closed)
                {
                    window.close();
                    break;
                }

                if (event.type == Event::KeyPressed)
                {
                    if (event.key.code == Keyboard::Enter)
                    {


                        display_menu(window);
                        break;
                    }
                }
            }
            window.display();
        }
        else {
            std::cerr << "Unable to open the score.txt file for reading!" << std::endl;
        }
    }

    void display_menu(RenderWindow& window)

    {
        Game g;
        Font font;
        if (!font.loadFromFile("RubikBubbles-Regular.ttf"))  // Replace with the path to your font file
        {
            std::cerr << "Error loading font" << std::endl;
            return;
        }

        Text title("Menu", font, 50);
        title.setPosition(300, 50);
        window.draw(title);

        Text option1("1. Start Game", font, 30);
        option1.setPosition(300, 250);
        window.draw(option1);

         Text option2("2. Instructions", font, 30);
        option2.setPosition(300, 300);
        window.draw(option2);

        Text option3("4. Exit", font, 30);
        option3.setPosition(300, 400);
        window.draw(option3);

        Text option4("3. HighScores", font, 30);
        option4.setPosition(300, 350);
        window.draw(option4);

        window.display();

        // Wait for user input
        Event event;
        while (window.waitEvent(event))
        {
            if (event.type ==  Event::Closed)
            {
                window.close();
                break;
            }

            if (event.type ==  Event::KeyPressed)
            {
                if (event.key.code ==  Keyboard::Num1)
                {
                    // Handle option 1 (Start Game)
                    std::cout << "Starting the game..." << std::endl;
                    g.start_game();
                    break;
                }
                else if (event.key.code ==  Keyboard::Num2)
                {
                    // Handle option 2 (Options)
                    std::cout << "Opening options..." << std::endl;
                    instructions(window);
                    break;
                }
                else if (event.key.code == Keyboard::Num3)
                {
                    // Handle option 3 (Exit)
                    highscore(window);
                    break;
                }
                else if (event.key.code ==  Keyboard::Num4)
                {
                    // Handle option 3 (Exit)
                    std::cout << "Exiting the game..." << std::endl;
                    window.close();
                    break;
                }
            }
        }
        
        //display menu screen here

        // add functionality of all the menu options here

        //if Start game option is chosen 

        



    }


};
