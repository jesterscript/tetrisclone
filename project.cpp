#include <iostream>
#include <string>
#include <vector>
using namespace std;


class AbstractTask 
{
public:

	virtual void Action() = 0;
	virtual ~AbstractTask(){};
	
protected:
	AbstractTask(){};
	string _name ;
	
};

class Task : public AbstractTask //Leaf task class.
{
public:
	Task(string _NAME) 
	{
		_name = _NAME;
	}

	void Action()
	{
		cout << "Working on " << _name << " .. \n";
	}
private:
	
};



class Process : public AbstractTask //Composite Task class
{
public:

	Process(string _NAME)
	{
		_name = _NAME;
	}
	void addTask(AbstractTask* _TASK)
	{
		_innerTasks.push_back(_TASK);
	}
	AbstractTask* get(int _INDEX)
	{
		return _innerTasks[_INDEX];
	}
	void Action()
	{
		cout << "Working on " << _name << " .. \n";
		for(int i = 0 ; i < _innerTasks.size() ; ++i)
		{
			_innerTasks[i]->Action();
		}
	}
private:
	vector<AbstractTask*> _innerTasks;


};


int main()
{

	Process* _task1 = new Process("Dota 2");
	AbstractTask* _task2 = new Task("Matchmaking");
	AbstractTask* _task3 = new Task("Hero Banning");
	AbstractTask* _task4 = new Task("Hero Selection");
	AbstractTask* _task5 = new Task("Game starting");

	_task1->addTask(_task2);
	_task1->addTask(_task3);
	_task1->addTask(_task4);
	_task1->addTask(_task5);
	
	_task1->Action();

	
	return 0;
}