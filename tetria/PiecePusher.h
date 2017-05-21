/*!
 *\brief The class which is responsible for waiting Shapes and displaying them.
 *\details This class is implemented with Singleton pattern.
 */



#ifndef  PUSHER_H_
#define PUSHER_H_
#include <queue>
#include "Shaper.h"
#include "Helpers.h"
class PiecePusher
{
public:
	/*!\brief Returns unique instance of the class.
	*\details Singleton implementation.
	*/
	static PiecePusher* getInstance()
	{
		if(_instance == NULL)
			_instance = new PiecePusher();
		return _instance;
	}
	/*!\brief This method generates a vector 1 to 6 which represents type for upcoming Shapes.
	 *\details This vector is shuffle.Therefore,the game does not come up with same Shapes each following rounds.
	*/
	void generate()
	{
		if(_generatedTypes.empty()) //Checks if the vector is empty.If it is , then fills it .
		{
			for(int i = 1 ; i < 7 ; ++i)
			_generatedTypes.push_back(i);
			std::random_shuffle(_generatedTypes.begin(),_generatedTypes.end());
		}

	}
	/*!\brief Returns next element according to Game s request.
	 *\details This method also invokes displayIncomingShape().
	*/
	Shape* getShape()
	{
		int _tempType = _generatedTypes.back(); // What is the next type coming.
		_generatedTypes.pop_back(); //Pop that type so vector can be empty for the new generation.
		displayIncomingShape(12,8); //Display the upcoming element on the screen after this shape.
		return new Shape(_tempType);
	}

	/*!\brief Displays the upcoming Shape on the screen.
	 *\details Takes two parameters to define a place in the screen to display.
	*/
	void displayIncomingShape(int _X , int _Y) //12 10
	{
		generate(); // Invokes display every time it invokes.

		for(int i = _X ; i < _X + 4 ; ++i) //Clear the previously shown piece .
			for(int k = _Y  ; k < _Y + 2 ; ++k)
				TetrisBoard::getInstance()->tableAsNumbers[i][k] = 0; 

		switch(_generatedTypes.back()) //According to the upcoming Shape and parameters,define its position on the screen
										// and redraw it.Uses same logic in Game class .
		{
			case 1:
			{
				TetrisBoard::getInstance()->tableAsNumbers[_X][_Y] = _generatedTypes.back();
				TetrisBoard::getInstance()->tableAsNumbers[_X + 1][_Y] = _generatedTypes.back();
				TetrisBoard::getInstance()->tableAsNumbers[_X][_Y+1] = _generatedTypes.back();
				TetrisBoard::getInstance()->tableAsNumbers[_X + 1][_Y+1] = _generatedTypes.back();
				break;
			}
			case 2:
			{
				TetrisBoard::getInstance()->tableAsNumbers[_X][_Y] = _generatedTypes.back();
				TetrisBoard::getInstance()->tableAsNumbers[_X+1][_Y] = _generatedTypes.back();
				TetrisBoard::getInstance()->tableAsNumbers[_X+2][_Y] = _generatedTypes.back();
				TetrisBoard::getInstance()->tableAsNumbers[_X+1][_Y+1] = _generatedTypes.back();
				break;
				break;
			}
			case 3:
			{
				TetrisBoard::getInstance()->tableAsNumbers[_X][_Y] = _generatedTypes.back();
				TetrisBoard::getInstance()->tableAsNumbers[_X+1][_Y] = _generatedTypes.back();
				TetrisBoard::getInstance()->tableAsNumbers[_X+2][_Y] = _generatedTypes.back();
				TetrisBoard::getInstance()->tableAsNumbers[_X+3][_Y] = _generatedTypes.back();
				break;
			}
			case 4:
			{
				TetrisBoard::getInstance()->tableAsNumbers[_X][_Y] = _generatedTypes.back();
				TetrisBoard::getInstance()->tableAsNumbers[_X+1][_Y] = _generatedTypes.back();
				TetrisBoard::getInstance()->tableAsNumbers[_X+2][_Y] = _generatedTypes.back();
				TetrisBoard::getInstance()->tableAsNumbers[_X+2][_Y + 1] = _generatedTypes.back();
				break;
			}
			case 5:
			{
				TetrisBoard::getInstance()->tableAsNumbers[_X+1][_Y] = _generatedTypes.back();
				TetrisBoard::getInstance()->tableAsNumbers[_X+2][_Y] = _generatedTypes.back();
				TetrisBoard::getInstance()->tableAsNumbers[_X][_Y+1] = _generatedTypes.back();
				TetrisBoard::getInstance()->tableAsNumbers[_X+1][_Y+1] = _generatedTypes.back();
				break;
			}
			case 6:
			{
				TetrisBoard::getInstance()->tableAsNumbers[_X][_Y] = _generatedTypes.back();
				TetrisBoard::getInstance()->tableAsNumbers[_X+1][_Y] = _generatedTypes.back();
				TetrisBoard::getInstance()->tableAsNumbers[_X+1][_Y+1] = _generatedTypes.back();
				TetrisBoard::getInstance()->tableAsNumbers[_X+2][_Y+1] = _generatedTypes.back();
				break;
			}
		}
		
	}
	
private:

	static PiecePusher* _instance; //!< Unique PiecePusher instance.
	/*!\brief Private constructor.
	*\details Fills and shuffles the vector for initialization.
	*/
	PiecePusher(){generate();};
	std::vector<int> _generatedTypes; //!< Vector of waiting Shape types.
};


#endif // ! PUSHER_H_
