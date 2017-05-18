#ifndef SCOREBOARD_H
#define SCOREBOARD_H
class Scoreboard
{
public:
	sf::Font font;
	sf::Text* scoreText;
	sf::Text* scoreValue;
	int value;
	Scoreboard()
	{
		
		font.loadFromFile("PressStart2P.ttf");
		scoreText = new sf::Text("Score", font);
		scoreValue = new sf::Text("0", font);
		scoreText->setPosition(sf::Vector2f(415, 40));
		scoreText->setScale(0.8, 0.8);
		scoreValue->setPosition(sf::Vector2f(420, 80));
		
	}
	void addToValue(int src)
	{
		value += src;
		std::string newResult = std::to_string(value);
		scoreValue->setString(newResult);
	}
private:

};
#endif // !SCOREBOARD_H
