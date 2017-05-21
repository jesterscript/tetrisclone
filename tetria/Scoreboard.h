/*!
 *\brief This class defines a in-game interface to show current level and current score.
 */

#ifndef SCOREBOARD_H
#define SCOREBOARD_H
class Scoreboard
{
public:
	sf::Font font; //!< SFML Font component for Text objects.
	sf::Text* scoreText; //!< A pointer to an SFML Text component which displays "Score" on screen.
	sf::Text* scoreValue; //!< A pointer to an SFML Text component which display actual score on screen. 
	sf::Text* levelText; //!< A pointer to an SFML Text component which display "Level" on screen.
	sf::Text* levelValue; //!< A pointer to tan SFML Text component which display actual level on screen.
	
	/*!\brief Construction of Scoreboard object.
	 *\details Initializing variables and setting positions of interface components.
	*/
	Scoreboard()
	{
		_lineCount = 0;
		_level = 1;
		font.loadFromFile("PressStart2P.ttf");
		scoreText = new sf::Text("Score", font);
		scoreValue = new sf::Text("0", font);
		scoreText->setPosition(sf::Vector2f(415, 40));
		scoreText->setScale(0.8, 0.8);
		scoreValue->setPosition(sf::Vector2f(450, 80));
		levelText = new sf::Text("Level",font);
		levelText->setPosition(sf::Vector2f(415,160));
		levelText->setScale(0.8,0.8);
		levelValue = new sf::Text("1",font);
		levelValue->setPosition(sf::Vector2f(450,200));
		
	}
	/*!\brief After player explodes some lines Game class invokes this method to update score on the screen.
	*/
	void addToValue(int src)
	{
		value += src; //Increase current score by 'src'.
		std::string newResult = std::to_string(value); //Convert int 'value' to string so it can be displayed.
		scoreValue->setString(newResult); // Set scoreValue string  as new score.
	}
	/*!\brief This method counts line numbers which are exploded.
	 *\details In the classical game logic in every 10 lines difficulty (level) increases.
	*/
	void incrementLineCounter()
	{
		std::cout << "worked!!!" <<"\n\n\n\n";
		++_lineCount;
		if(_lineCount % 10 == 0)
		{

			std::string newResult = std::to_string(++_level);
			levelValue->setString(newResult);
		}

	}
	/*!\brief Accessor for '_level' value.
	*/
	int getLevel()
	{
		return _level;
	}
private:
	int value; //!< Current score.
	int _lineCount; //!< Current lines which are destroyed.
	int _level; //!< Current difficulty(level).

};
#endif // !SCOREBOARD_H
