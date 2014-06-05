/*
    Retro Clone Pong Game by Jonathan A Vazquez
    Version 2.0
 
 DONE!
 
 */

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <ResourcePath.hpp> //Helper method resourcepath() for files (Images, Sounds, fonts)
#include <cmath>
#include <string>


//Window Settings
int windowWidth{600};
int windowHeight{400};
std::string windowTitle{"RetroPong"};

//Creating the Left and Right Paddle Position and Size
float leftPaddleSize_X{15};
float leftPaddleSize_Y{75};
float leftPaddlePos_X{5};
float leftPaddlePos_Y{(windowHeight / 2) - (leftPaddleSize_Y / 2)};
float rightPaddleSize_X{leftPaddleSize_X};
float rightPaddleSize_Y{leftPaddleSize_Y};
float rightPaddlePos_X{575};
float rightPaddlePos_Y{(windowHeight / 2) - (rightPaddleSize_Y / 2)};

//Creating the PongBall Properties
float ballPos_X{300};
float ballPos_Y{200};
float ballRadius{10};
float ballSpeed{0.1};
float ballDir_X{1.0};
float ballDir_Y{1.0};

//keeping the scoreboard
int playerScore{0};
int opponentScore{0};

int main()
{
    // Create the main window as well as all the necessary shapes and text
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), windowTitle);
    sf::Font font;
    sf::Text playerTextScore, opponentTextScore;
    sf::RectangleShape bgLeftBox, bgRightBox, leftPaddle, rightPaddle;
    sf::CircleShape pongBall;
    
    //Setting the Right and Left Background Boxes
    bgLeftBox.setSize(sf::Vector2f(windowWidth/2, windowHeight));
    bgLeftBox.setPosition(sf::Vector2f(0, 0));
    bgLeftBox.setFillColor(sf::Color::White);
    bgRightBox.setSize(sf::Vector2f(windowWidth/2, windowHeight));
    bgRightBox.setPosition(sf::Vector2f(windowWidth / 2, 0));
    bgRightBox.setFillColor(sf::Color::Black);
    
    //Import the Font and create a Score Text for the user
    std::string resourcePath(void);
    font.loadFromFile(resourcePath() + "boxfont.ttf");
    playerTextScore.setFont(font);
    opponentTextScore.setFont(font);
    playerTextScore.setCharacterSize(72);
    opponentTextScore.setCharacterSize(72);
    playerTextScore.setColor(sf::Color::Black);
    opponentTextScore.setColor(sf::Color::White);
    opponentTextScore.setPosition(sf::Vector2f(450 ,0));
    playerTextScore.setPosition(sf::Vector2f(125, 0));
    playerTextScore.setString("0");
    opponentTextScore.setString("0");

    //Converting integer to strings
    //std::string s = to_string(playerScore);
    
    //Setting the Right and Left Paddle
    leftPaddle.setSize(sf::Vector2f(leftPaddleSize_X, leftPaddleSize_Y));
    leftPaddle.setPosition(sf::Vector2f(leftPaddlePos_X, leftPaddlePos_Y));
    leftPaddle.setFillColor(sf::Color::Black);
    rightPaddle.setSize(sf::Vector2f(rightPaddleSize_X, rightPaddleSize_Y));
    rightPaddle.setPosition(sf::Vector2f(rightPaddlePos_X, rightPaddlePos_Y)); //total window is 600, size 15, position is 5
    rightPaddle.setFillColor(sf::Color::White);
    
    //Creating the ball and its properties
    pongBall.setRadius(ballRadius);
    pongBall.setPosition(ballPos_X, ballPos_Y);
    pongBall.setFillColor(sf::Color::White);

                             
    // Start the game loop
    while (window.isOpen())
    {
        //Updating the movement of the ball and changing its color in the game loop
        //Moving Ball
        ballPos_X += ballSpeed * ballDir_X;
        ballPos_Y += ballSpeed * ballDir_Y;
        pongBall.setPosition(ballPos_X, ballPos_Y);
        
        ///Changing the Ball Color depending on location
        if(pongBall.getPosition().x < (windowWidth / 2))
        {
            pongBall.setFillColor(sf::Color::Black);
        }else
        {
            pongBall.setFillColor(sf::Color::White);
        }
        
        //Wall Rebounce Both Top and Bottom
        if(pongBall.getPosition().y > windowHeight)
        {
            ballDir_Y = -fabs(ballDir_Y);
        }else if(pongBall.getPosition().y < 0)
        {
            ballDir_Y = fabs(ballDir_Y);
        }
        
        //Collision Detection of the left and Right Paddle
        if(pongBall.getPosition().x < leftPaddle.getSize().x + leftPaddle.getPosition().x &&
           pongBall.getPosition().x > leftPaddle.getPosition().x &&
           pongBall.getPosition().y < leftPaddle.getPosition().y + leftPaddle.getSize().y &&
           pongBall.getPosition().y > leftPaddle.getPosition().y ) //Left Paddle
        {
            ballDir_X = fabs(ballDir_X);
            
        }else if(pongBall.getPosition().x < 0)
        {
            ballPos_X = windowWidth / 2;
            ballPos_Y = windowHeight / 2;
            pongBall.setPosition(ballPos_X, ballPos_Y);
            ballDir_X = fabs(ballDir_X);
            ++opponentScore;
            std::string opponentScoreText = std::to_string(opponentScore);
            opponentTextScore.setString(opponentScoreText);
            if(opponentScore == 7)
            {
                //Print out Opponent Win and stop the ball from moving
                opponentTextScore.setColor(sf::Color::Red);
                opponentTextScore.setCharacterSize(20);
                opponentTextScore.setPosition(sf::Vector2f(0, windowHeight / 2));
                opponentTextScore.setString("Opponent Won the Match, Thanks for playing");
                window.clear();
                window.close();
            }
        }
        if(pongBall.getPosition().x <  rightPaddle.getPosition().x + rightPaddle.getSize().x &&
           pongBall.getPosition().x > rightPaddle.getPosition().x &&
           pongBall.getPosition().y < rightPaddle.getSize().y + rightPaddle.getPosition().y &&
           pongBall.getPosition().y > rightPaddle.getPosition().y) //Right Paddle
        {
            ballDir_X = -fabs(ballDir_X);
        }else if(pongBall.getPosition().x > windowWidth)
        {
            ballPos_X  = windowWidth / 2;
            ballPos_Y = windowHeight / 2;
            pongBall.setPosition(ballPos_X, ballPos_Y);
            ballDir_X = -fabs(ballDir_X);
            ++playerScore;
            std::string playerScoreText = std::to_string(playerScore);
            playerTextScore.setString(playerScoreText);
            if(playerScore == 7)
            {
                //Print out Player Win and stop the ball from moving
                playerTextScore.setColor(sf::Color::Red);
                playerTextScore.setCharacterSize(20);
                playerTextScore.setPosition(sf::Vector2f(0, windowHeight / 2));
                playerTextScore.setString("Player Won the Match, Thanks for playing");
                window.clear();
                window.close();
            }
        }
        
        
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed) {
                // Clear screen
                window.clear(sf::Color::White);
                window.close();
            }
            //To Move the Left Paddle Event
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                leftPaddle.move(sf::Vector2f(0, -12));
            }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                leftPaddle.move(sf::Vector2f(0, 12));
            }
            //To move the right Paddle Event
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::I))
            {
                rightPaddle.move(sf::Vector2f(0, -12));
            }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::K))
            {
                rightPaddle.move(sf::Vector2f(0, 12));
            }
        }

        // Draw the sprite
        window.draw(bgLeftBox);
        window.draw(bgRightBox);
        window.draw(playerTextScore);
        window.draw(opponentTextScore);
        window.draw(leftPaddle);
        window.draw(rightPaddle);
        window.draw(pongBall);

        // Update the window
        window.display();
    }
}