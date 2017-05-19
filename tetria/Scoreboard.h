#ifndef SCOREBOARD_H
#define SCOREBOARD_H
class Scoreboard
{
public:
	sf::Font font;
	sf::Text* scoreText;
	sf::Text* scoreValue;
	sf::Text* levelText;
	sf::Text* levelValue;
	

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
	void addToValue(int src)
	{
		value += src;
		std::string newResult = std::to_string(value);
		scoreValue->setString(newResult);
	}
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

	int getLevel()
	{
		return _level;
	}
private:
	int value;
	int _lineCount;
	int _level;

};
#endif // !SCOREBOARD_H
