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

class AbstractIterator {
public:
	virtual void First() = 0;
	virtual void Next() = 0;
    virtual bool IsDone () const = 0;
	virtual AbstractTask* CurrentItem() const = 0 ;
protected:
	AbstractIterator(){};
};

class Process; 

class TaskIterator : public AbstractIterator
{
public:
	TaskIterator(const Process *collection);
	void First();
    void Next();
    AbstractTask* CurrentItem() const;
	bool IsDone()const ;
private:
	const Process *_collection;
	int _current;

};



class Process : public AbstractTask //Composite Task class
{
public:

	TaskIterator* CreateIterator() {
		return new TaskIterator(this);
    }

	Process(string _NAME)
	{
		_name = _NAME;
	}
	
	void addTask(AbstractTask* _TASK)
	{
		_innerTasks.push_back(_TASK);
	}
	
	AbstractTask* get(int _INDEX) const
	{
		return _innerTasks[_INDEX];
	}
	
	int getCount() const
	{
		return _innerTasks.size();
	}
	
	void Action()
	{
		TaskIterator* _iterator = this->CreateIterator();
		cout << "Working on " << _name << " .. \n";
		for(_iterator->First();  !_iterator->IsDone(); _iterator->Next())
		{
			(*_iterator).CurrentItem()->Action();
		}
		delete _iterator;
	}
private:
	vector<AbstractTask*> _innerTasks;

};

class Thread
{
public:
	Thread(string _TYPE)
	{
		_type = _TYPE;
		if(_type == "HThread")
			{ _memoryAllocated = 512; _priority = 1;}
		else
			{_memoryAllocated = 256; _priority = 5;}
	}
	
private:
	AbstractTask* _currentThread;
	int _memoryAllocated;
	int _priority;
	string _type;
};
//---------------------------------------------
TaskIterator::TaskIterator(const Process *collection) :
	_collection(collection), _current(0) {
}
void TaskIterator::First() {
	_current = 0;
}
void TaskIterator::Next()  {
	_current++;
}
AbstractTask* TaskIterator::CurrentItem() const {
	return (IsDone()?NULL:_collection->get(_current));
}
bool TaskIterator::IsDone() const {
	return _current >= _collection->getCount();
}

//-------------------------------------------

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