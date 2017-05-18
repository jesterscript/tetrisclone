#ifndef  PUSHER_H_
#define PUSHER_H_
#include <queue>
#include "Shaper.h"
#include "Helpers.h"
class PiecePusher
{
public:
	static PiecePusher* getInstance()
	{
		if(_instance == NULL)
			_instance = new PiecePusher();
		return _instance;
	}
	void generate()
	{
		if(_generatedTypes.empty())
		{
			for(int i = 1 ; i < 7 ; ++i)
			_generatedTypes.push_back(i);
			std::random_shuffle(_generatedTypes.begin(),_generatedTypes.end());
		}

	}
	Shape* getShape()
	{
		//generate();
		int _tempType = _generatedTypes.back();
		_generatedTypes.pop_back();
		displayIncomingShape(12,10);
		return new Shape(_tempType);
	}
	void displayIncomingShape(int _X , int _Y) //12 10
	{
		generate();

		switch(_generatedTypes.back())
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
		TetrisBoard::getInstance()->tableAsNumbers[13][10] = _generatedTypes.back();
	}
	
private:

	static PiecePusher* _instance;
	PiecePusher(){generate();};
	std::vector<int> _generatedTypes;
};


#endif // ! PUSHER_H_
