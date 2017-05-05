#include <iostream>
#include <string>

using namespace std;


class AbstractTask 
{
public:

	virtual void Action() = 0;
	
protected:
	AbstractTask(){};
	string _name ;
};

class Task : public AbstractTask //Leaf task class.
{
public:
	Task(string _NAME) 
	{
		AbstractTask::_name = _NAME;
	}

	void Action()
	{
		cout << "Working on " << _name << " .. \n";
	}
private:

};

class Process : public AbstractTask //Composite Task class


int main()
{

	AbstractTask* _task1 = new Task("Matchmaking");

	return 0;
}