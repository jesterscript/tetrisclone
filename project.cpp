#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Iterable
{
public:
	virtual void f(){};
private:
};

class AbstractTask : public Iterable
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
	virtual Iterable* CurrentItem() const = 0 ;
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



class Process : public AbstractTask  //Composite Task class
{
public:

	TaskIterator* CreateIterator() {
		return new TaskIterator(this);
    }

	Process(string _NAME)
	{
		_name = _NAME;
	}
	
	void add(AbstractTask* _TASK)
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

class Thread : public Iterable
{
public:
	Thread(string _TYPE)
	{
		_type = _TYPE;
		_state = false;
		if(_type == "HThread")
			{ _memoryAllocated = 512; _priority = 1;}
		else if(_type == "LThread")
			{_memoryAllocated = 256; _priority = 5;}
	}
	void Execute()
	{
		display();
		_currentTask->Action();
	}
	
	void display()
	{
		cout << _type << " " << _memoryAllocated << " " << _priority << endl;
	}
	
	bool isBusy()
	{
		return _state;
	}

	void assaignTask(AbstractTask* _TASK)
	{
		_currentTask = _TASK;
	}
private:
	bool _state; // 1 for busy , 0 for idle
	AbstractTask* _currentTask;
	int _memoryAllocated;
	int _priority;
	string _type;
};

class ThreadPool //ThreadPool class with singleton pattern.
{
public:
	static ThreadPool* getInstance()
	{
		if(_instance == NULL)
			_instance = new ThreadPool();
		return _instance;
	}
	void add(Thread * _THREAD)
	{
		_innerThreads.push_back(_THREAD);
	} 		
	int getCount () const { return _innerThreads.size();}
	Thread * get(int _CURRENT) const { return _innerThreads[_CURRENT];}
	
private:
	ThreadPool(){};
	static ThreadPool* _instance;
	vector<Thread*> _innerThreads;
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

	_task1->add(_task2);
	_task1->add(_task3);
	_task1->add(_task4);
	_task1->add(_task5);
	
	

	Thread* _thread1 = new Thread("HThread");
	
	_thread1->assaignTask(_task1);
	_thread1->Execute();
	cout << "balik 1";
	
	return 0;
}