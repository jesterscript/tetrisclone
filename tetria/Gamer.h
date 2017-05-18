#ifndef GAMER_H
#define GAMER_H
//#include "Shaper.h"
#include "Scoreboard.h"
#include "PiecePusher.h"


class Game
{
public:
	sf::Texture frameTexture;//Texture for the frame sprite
	sf::Sprite  frameSprite;//Blue frame sprite that covers the game area
	Scoreboard* sb; //Scoreboard
    std::vector<Shape*> allParts; //Newly created parts pushed into a vector.
	bool isCanvasDrawn;
    Shape* createPiece() // Function to create new piece.
    {

     //int type = rand() % 6 + 1; //Randoming 1 to 6.
     //return new Shape(type); //Creating shape with type parameter.
     return PiecePusher::getInstance()->getShape();

    }
     Game()
    {
	isCanvasDrawn = false;
	sb = new Scoreboard();
	frameTexture.loadFromFile("frame1.png");
	frameSprite.setTexture(frameTexture);
	frameSprite.setPosition(sf::Vector2f(0, 0));
    sf::RenderWindow _renderWindow(sf::VideoMode(560, 665), "*Tetris Clone*"); //Creating window with a title.
    sf::Event event; // SFML component Event which represents any event occured.
    sf::Clock clock; // SFML component "Clock" which is used for time measurement.
    srand(time(NULL));// Reseting random seed.
    TetrisBoard* tb = TetrisBoard::getInstance(); // Tetrisboard class which is singleton.
    allParts.push_back(createPiece()); //Invoking createPiece() method and pushing it to the vector.
    Shape* sq1 = allParts[allParts.size()-1]; // Current elemenet is the last element of the vector.
    for(int i = 0 ; i < 20 ; ++i) // Printing array to the console.
    {
        for(int j = 0 ; j < 10 ; ++j)
        {
            std::cout << tb->tableAsNumbers[j][i] << " ";
        }
        std::cout << std::endl;

    }
    std::cout << '\n' << '\n' <<std::endl;
    while (_renderWindow.isOpen()) { //Main loop of the game.Checks whether window is open or not.
            if(clock.getElapsedTime().asSeconds() > 1 ) //Each one second passed , the current part moves down.
            {
                sq1->movePartDown();
                clock.restart();
            }
            if(!sq1->pathIsClear()) // pathIsClear() method checks whether way of current part is clear.
            {
                

				int riisCounter = 0; //ris counter to calculate the score according how many rows destroyed.
                for(int i = 0 ; i < 20 ; ++i) //Check if there any full row on the table.
                {
                     int rowC = 0;//row counter
                     for(int k = 0 ; k < 10 ; ++k)
                    {
                      
						 if(tb->tableAsNumbers[k][i] != 0)
                            {
                                ++rowC;
								std::cout << rowC;
								
                            }
						if (rowC == 10)
						{
							riisCounter += tb->riis(i); // Makes that row disappear and add scores to scoreboard.
							rowC = 0;
							
						}

                    }

                }
				//If there is no where to go , then the current piece stops and new piece is sent.
				std::cout << "lines destroyed : " << riisCounter;
				sb->addToValue(calculateScore(riisCounter));
                sq1->parts.clear();
                allParts.push_back(createPiece());
                sq1 = allParts[allParts.size()-1];
                clock.restart();
            }

        while (_renderWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                _renderWindow.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Down && sq1->pathIsClear()) {

                    sq1->movePartDown();
                    for(int i = 0 ; i < 20 ; i++)
                    {
                        for(int j = 0 ; j < 10 ; j++)
                        {
                            std::cout << tb->tableAsNumbers[j][i] << " ";
                        }
                        std::cout << std::endl;

                    }
                     std::cout << "-------------------------" << std::endl;
                    clock.restart();
                }
                if(event.key.code == sf::Keyboard::Right && sq1->pathIsClear())
                {
                    sq1->movePartRight();
                    for(int i = 0 ; i < 20 ; i++)
                    {
                        for(int j = 0 ; j < 10 ; j++)
                        {
                            std::cout << tb->tableAsNumbers[j][i] << " ";
                        }
                        std::cout << std::endl;

                    }
                     std::cout << "-------------------------" << std::endl;

                }
                if(event.key.code == sf::Keyboard::Left && sq1->pathIsClear())
                {
                    sq1->movePartLeft();
                    for(int i = 0 ; i < 20 ; i++)
                    {
                        for(int j = 0 ; j < 10 ; j++)
                        {
                            std::cout << tb->tableAsNumbers[j][i] << " ";
                        }
                        std::cout << std::endl;

                    }
                     std::cout << "-------------------------" << std::endl;

                }
                if(event.key.code == sf::Keyboard::Left && !sq1->pathIsClear() && sq1->atHorizontalBordersLeft())
                {
                    sq1->movePartLeft();
                    for(int i = 0 ; i < 20 ; i++)
                    {
                        for(int j = 0 ; j < 10 ; j++)
                        {
                            std::cout << tb->tableAsNumbers[j][i] << " ";
                        }
                        std::cout << std::endl;

                    }
                     std::cout << "-------------------------" << std::endl;

                }
                if(event.key.code == sf::Keyboard::A && sq1->pathIsClear())
                {
                    sq1->rotatePartRight();
                    for(int i = 0 ; i < 20 ; i++)
                    {
                        for(int j = 0 ; j < 10 ; j++)
                        {
                            std::cout << tb->tableAsNumbers[j][i] << " ";
                        }
                        std::cout << std::endl;

                    }
                     std::cout << "-------------------------" << std::endl;
                }
                if(event.key.code == sf::Keyboard::S && sq1->pathIsClear())
                {
                    sq1->rotatePartLeft();
                    for(int i = 0 ; i < 20 ; i++)
                    {
                        for(int j = 0 ; j < 10 ; j++)
                        {
                            std::cout << tb->tableAsNumbers[j][i] << " ";
                        }
                        std::cout << std::endl;

                    }
                    std::cout << "-------------------------" << std::endl;
                }

            }


        }
              _renderWindow.clear(); // Starting point of drawing functions.
                    
            for (int i = 0; i < 20; i++) {

                for(int k = 0 ; k < 10 ; k++){

                sf::RectangleShape cs(sf::Vector2f(_size, _size));
                sf::Color typeColor ;

                switch(tb->tableAsNumbers[k][i])
                {


                    case 1:{typeColor = sf::Color::Yellow;break;}
                    case 2:{typeColor = sf::Color::Magenta;break;}
                    case 3:{typeColor = sf::Color::Cyan;break;}
                    case 4:{typeColor = sf::Color::Blue;break;}
                    case 5:{typeColor = sf::Color::Green;break;}
                    case 6:{typeColor = sf::Color::Red;break;}



                }
                cs.setFillColor(typeColor);
                cs.setPosition(sf::Vector2f(k*32 + 32, i*32));
                _renderWindow.draw(cs);
                }

            }
			_renderWindow.draw(*sb->scoreText);
			_renderWindow.draw(*sb->scoreValue);
			_renderWindow.draw(frameSprite);
				
			
            _renderWindow.display(); // Ending of drawing functions.
    }
    }
private:
    const int _size = 32;
    sf::RectangleShape drawPieces(Shape* shp)
    {
        sf::RectangleShape _unit(sf::Vector2f(_size,_size));
        sf::Color typeColor;
        switch(shp->getType())
        {

            case 1:{typeColor = sf::Color::Yellow;break;}
            case 2:{typeColor = sf::Color::Magenta;break;}
            case 3:{typeColor = sf::Color::Cyan;break;}
            case 4:{typeColor = sf::Color::Blue;break;}
            case 5:{typeColor = sf::Color::Green;break;}
            case 6:{typeColor = sf::Color::Red;break;}


        }
        _unit.setFillColor(typeColor);
        return _unit;
    }

	int calculateScore(int lineNumber) // calculate score method to determine the upcoming score according to level and lines destroyed.
	{
		int calculatedScore;
		calculatedScore = 0;
		switch (lineNumber)
		{
			case 1:
			{
				calculatedScore = 40;
				break;
			}
			case 2:
			{
				calculatedScore = 100;
				break;
			}
			case 3:
			{
				calculatedScore = 400;
				break;
			}
			case 4:
			{
				calculatedScore = 1200;
				break;
			}
		}
		return calculatedScore;
	}

};

#endif // GAMER_H
