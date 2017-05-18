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
		generate();
		int _tempType = _generatedTypes.back();
		_generatedTypes.pop_back();
		return new Shape(_tempType);
	}

	
private:

	static PiecePusher* _instance;
	PiecePusher(){generate();};
	std::vector<int> _generatedTypes;
};


#endif // ! PUSHER_H_
