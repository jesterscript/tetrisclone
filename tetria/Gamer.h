/*!
 *\brief This class controls all events,interactions,logic and game mechanics.
 */


#ifndef GAMER_H
#define GAMER_H
#include "Scoreboard.h"
#include "PiecePusher.h"



class Game
{
public:
	sf::Texture frameTexture; //!< Raw frame texture which is the source of the frame sprite.
	sf::Sprite  frameSprite; //!< Sprited version of frame text which is ready to be displayed.
	Scoreboard* sb; //!< A pointer to the scoreboard.
    std::vector<Shape*> allParts; //!<Vector of Shape pointers which contains all created shapes up to now.
	sf::Clock _innerClock; //!< SFML Component clock which measure time.Used for dropping speeed of shapes.
    sf::RenderWindow* _renderWindow; //!< SFML Component RenderWindow which is the main window of the game. "if(_renderWindow->isOpen())" expression defines a main loop for this game.
    sf::Event event; //!< SFML component Event which represents any event occured.
    sf::Clock clock; //!< SFML component "Clock" which is used for time measurement.
    TetrisBoard* tb; //!< A pointer to the gameboard 
    Shape* sq1; //!< A pointer to the current shape which is being controlled.
    /*!
     *\brief This method gets the next element in a queue of upcoming elements.
     *\details PiecePusher is responsible for upcoming elements if the player is done with a part, then next part comes.
     */
    Shape* createPiece() // Function to create new piece.
    {
     return PiecePusher::getInstance()->getShape();

    }
    /*!
     *\brief Constructor of Game class.
     *\details Initializing variables,getting assets and starting the game is done here.
     */
    Game()
    {
    
    sb = new Scoreboard(); //Creating new scoreboard.
	frameTexture.loadFromFile("frame1.png"); //Loading frame asset.
	frameSprite.setTexture(frameTexture);  //Trimming texture into sprite.
	frameSprite.setPosition(sf::Vector2f(0, 0)); //Assigning position of the frame sprite.
    _renderWindow = new sf::RenderWindow(sf::VideoMode(560, 665), "*Tetris Clone*"); //Creating window with a title.
    srand(time(NULL));// Reseting random seed.
    tb = TetrisBoard::getInstance(); // Tetrisboard class which is singleton.
    startGame();
    }
    /*!
     *\brief A Method which contains the game loop and every other calculations and rendering.
     *\details In the game loop checkBlasts() , checkInputs() and renderComponents() methods are invoked.  
    */
    void startGame()
    {
    allParts.push_back(createPiece()); //Invoking createPiece() method and pushing it to the vector.
    sq1 = allParts[allParts.size()-1]; // Current elemenet is the last element of the vector.
    for(int i = 0 ; i < 20 ; ++i) // Printing array to the console.
    {
        for(int j = 0 ; j < 10 ; ++j)
        {
            std::cout << tb->tableAsNumbers[j][i] << " ";
        }
        std::cout << std::endl;

    }
    std::cout << '\n' << '\n' <<std::endl;
    while (_renderWindow->isOpen()) { //Main loop of the game.Checks whether window is open or not.

            
            checkBlasts();
            checkInputs();
            renderComponents();

    }
    }
private:
    const int _size = 32;//!< Constant variable for size of squares 32x32.
    /*!
     *\brief Creates a rectange shape instance according to color of the given shape.
    */
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
    /*!
     *\brief Calculate score according to the number of lines which are exploded.
     *\details A formula similar to classic score system is used.
     */
	int calculateScore(int lineNumber) // calculate score method to determine the upcoming score according to level and lines destroyed.
	{
		int calculatedScore;
		calculatedScore = 0;
		switch (lineNumber)
		{
			case 1:
			{
				calculatedScore = 40 * sb->getLevel();
				break;
			}
			case 2:
			{
				calculatedScore = 100* sb->getLevel();
				break;
			}
			case 3:
			{
				calculatedScore = 400* sb->getLevel();
				break;
			}
			case 4:
			{
				calculatedScore = 1200* sb->getLevel();
				break;
			}
		}
		return calculatedScore;
	}
    /*!
     *\brief Checks keyboard inputs as SFML events an perform actions.
     *\Uses SFML's input system.
    */
    void checkInputs()
    {
        while (_renderWindow->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                _renderWindow->close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Down) {

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
                if(event.key.code == sf::Keyboard::Right)
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
                if(event.key.code == sf::Keyboard::Left)
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
    }
    /*!
     *\brief Renders all the graphic components.
     *\details According to values in TetrisBoard squares are drawn.Texts and sprites in Scoreboard class also rendered here.
    */
    void renderComponents()
    {
            _renderWindow->clear(); // Starting point of drawing functions.
                    
            for (int i = 0; i < 20; i++) {

                for(int k = 0 ; k < 20 ; k++){

                sf::RectangleShape cs(sf::Vector2f(_size, _size));
                sf::Color typeColor ;

                switch(tb->tableAsNumbers[k][i]) //Type of a shape in the main array defines a unique color of each type.
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
                _renderWindow->draw(cs);
                }

            }
            _renderWindow->draw(*sb->scoreText); // Rendering "Score" text.
            _renderWindow->draw(*sb->scoreValue); // Rendering actual score.
            _renderWindow->draw(*sb->levelText);   //Rendering "Level" text.
            _renderWindow->draw(*sb->levelValue);  //Rendering actual level.
            _renderWindow->draw(frameSprite);
            _renderWindow->display(); // Ending of drawing functions.
    }
    /*!
     *\brief Checks is/are there any full rows to explode.
     *\details This method is also responsible dropping of Shape s.
    */
    void checkBlasts()
    {
            float _dropTime = 1 - ((float)sb->getLevel())/10;
            if(clock.getElapsedTime().asSeconds() > _dropTime) //Each one second passed , the current part moves down.
            {

                sq1->movePartDown();
                clock.restart();
            }
         if(!sq1->pathIsClear()) // pathIsClear() method checks whether way of current part is clear.
            {
                
                if(sq1->horizontalPathIsClear() && sq1->hasBoost())
                {
                    sq1->boost();
                    _innerClock.restart();
                    
                }
                if((_innerClock.getElapsedTime().asSeconds() > _dropTime && !sq1->hasBoost()) || !sq1->horizontalPathIsClear() )
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
                            sb->incrementLineCounter();
                            rowC = 0;
                            
                        }

                    }

                }
                //If there is no where to go , then the current piece stops and new piece is sent.
                sb->addToValue(calculateScore(riisCounter)); // if is there any score need to be added then add it to the scoreboard.
                sq1->parts.clear(); // Clear Shape.
                allParts.push_back(createPiece()); //Add vector the next Shape waiting.
                sq1 = allParts[allParts.size()-1]; //Last added Shape is now in play.
                clock.restart(); //Restart the clock.
                }
            }
    }



};

#endif // GAMER_H
