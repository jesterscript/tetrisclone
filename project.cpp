#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

class Iterable
{
public:
	virtual void f() {};
private:
};


class AbstractObserver : public Iterable {
public:
	virtual ~AbstractObserver(){};
	virtual void Update(string _INFO) = 0;
};


class AbstractTask : public Iterable
{
public:

	virtual int getMemoryNeeded() = 0;
	virtual bool isDone() = 0;
	virtual void assignToPool() = 0;
	virtual void Action() = 0;
	virtual bool isAssigned() = 0;
	virtual ~AbstractTask() {};
	string getName()
	{
		return _name;
	}

protected:
	AbstractTask() {};
	string _name;
	int _totalMemoryNeeded;

};


class Thread : public Iterable //Thread is subject
{
public:
	Thread(string _TYPE)
	{
		_type = _TYPE;
		_isBusy = false;
		if (_type == "HThread")
		{
			_memoryAllocated = 512; _priority = 1;
		}
		else if (_type == "LThread")
		{
			_memoryAllocated = 256; _priority = 5;
		}
	}
	void Execute()
	{
		if(_currentTask == NULL)
			return;

		else if(!_currentTask->isDone())
			{
				_currentTask->Action();
				
			}
		else
			{
				cout << _currentTask->getName()  << " has been completed" << endl;
				_isBusy = false;
				_currentTask = NULL;
				Notify("availableThread");

			}
	}

	void printThread()
	{
		cout << "T" << _index+1 << "  : " << _type << " " << _memoryAllocated << " " << _priority << endl;
	}

	bool isBusy()
	{
		return _isBusy;
	}

	void assaignTask(AbstractTask* _TASK)
	{
		_currentTask = _TASK;
		_isBusy = true;
	}
	int getMemoryAllocated()
	{
		return _memoryAllocated;
	}

	AbstractTask* getTask() //Get current task of the thread.
	{
		return _currentTask;
	}

	void Attach(AbstractObserver* _OBS) //Attach observer object.
	{
		_innerObservers.push_back(_OBS);
	}

	void Detach(AbstractObserver* _OBS) // Detach observer object.
	{
	for (unsigned int i= 0; i< _innerObservers.size(); i++) {
		if (_innerObservers[i] == _OBS) {
			_innerObservers.erase(_innerObservers.begin()+i);
			return;
		}
		}	
	}

	void Notify(string _INFO) //Notifies observers about change.Observers will be TaskQueue and Memory Manager.
	{
		for(int i = 0 ; i < _innerObservers.size() ; ++i)
			_innerObservers[i]->Update(_INFO);
		cout << "A thread notified about : " << _INFO << endl;

	}
	void setIndex(int _INDEX)
	{
		_index = _INDEX;
	}

private:
	bool _isBusy; // Is thread working on a job currently?
	AbstractTask* _currentTask;
	int _memoryAllocated;
	int _lastMemoryUsedByTask;
	int _priority;
	string _type;
	int _index;
	vector<AbstractObserver*> _innerObservers;
};

class AbstractIterator {
public:
	virtual void First() = 0;
	virtual void Next() = 0;
	virtual bool IsDone() const = 0;
	virtual Iterable* CurrentItem() const = 0;
protected:
	AbstractIterator() {};
};

class ThreadPool;

class ThreadIterator : public AbstractIterator {
public:
	ThreadIterator(const ThreadPool *collection);
	void First();
	void Next();
	Thread* CurrentItem() const;
	bool IsDone()const;
private:
	const ThreadPool *_collection;
	int _current;

};

class ThreadPool : public AbstractObserver //ThreadPool class with singleton pattern.An observer of a thread and also a subject of task queue.
{
public:
	ThreadIterator* CreateIterator() {
		return new ThreadIterator(this);
	}
	void Update(string _INFO)
	{
		if(_INFO == "availableThread")
			Notify(_INFO);

	}
	static ThreadPool* getInstance()
	{
		if (_instance == NULL)
			_instance = new ThreadPool();
		return _instance;
	}
	void createThread(string _TYPE)
	{
		Thread* _newBornThread = new Thread(_TYPE);
		cout << "Thread created" << endl;
		_newBornThread->Attach(this);
		_newBornThread->setIndex(_innerThreads.size());
		 _innerThreads.push_back(_newBornThread);
		 Notify("availableThread");
		 
	}
	
	int getCount() const { return _innerThreads.size(); }
	
	Thread * get(int _CURRENT) const { return _innerThreads[_CURRENT]; }

	Thread* getAvailableThread(int _MEMORY)
	{
		Thread* _returner = NULL;
		ThreadIterator* _iterator = this->CreateIterator();
		for (_iterator->First(); !_iterator->IsDone(); _iterator->Next())
		{
			if ((*_iterator).CurrentItem()->getMemoryAllocated() >= _MEMORY && !(*_iterator).CurrentItem()->isBusy())
				_returner = (*_iterator).CurrentItem();
		}
		delete _iterator;

		

		return _returner;
	}

	void runAll()
	{
		
		cout << "run all started" << endl;
		ThreadIterator* _iterator = this->CreateIterator();

		for(_iterator->First(); !_iterator->IsDone(); _iterator->Next())
		{

			(*_iterator).CurrentItem()->Execute();	
			
		}
		delete _iterator;

	}

	void Notify(string _INFO)  // Threadpool will notify Taskqueue to make it insert new task to new available thread.
	{
		for(int i  = 0 ; i < _innerObservers.size() ; ++i)
			_innerObservers[i]->Update(_INFO);

		cout << "Threadpool notified : " << _INFO << endl;

	}

	void Attach(AbstractObserver* _OBS) //Attach observer object.
	{
		_innerObservers.push_back(_OBS);
	}

	void Detach(AbstractObserver* _OBS) // Detach observer object.
	{
		for (unsigned int i= 0; i< _innerObservers.size(); i++) {
			if (_innerObservers[i] == _OBS) {
				_innerObservers.erase(_innerObservers.begin()+i);
				return;
			}
			}	
	}

private:
	ThreadPool() {};
	static ThreadPool* _instance;
	vector<Thread*> _innerThreads;
	vector<AbstractObserver*> _innerObservers;

	
};
ThreadPool* ThreadPool::_instance = 0;

class Task : public AbstractTask //Leaf task class.
{
public:
	Task(string _NAME,int _WORK,int _MEMORYNEED)
	{
		_totalMemoryNeeded = _MEMORYNEED;
		_workToDo = _WORK;
		_name = _NAME;
		_isAssigned = false;
	}

	void Action()
	{
		cout << "Working on " << _name << " .. " ;
		--_workToDo;
		cout << " " << _workToDo << endl;

	}
	void assignToPool()
	{
 		Thread* _t1 = ThreadPool::getInstance()->getAvailableThread(this->getMemoryNeeded());
 		if(_t1 != NULL && !_t1->isBusy() && !_isAssigned)
 			{
 				_t1->assaignTask(this);
 				_isAssigned = true;
 				cout << _name << " is assaigned to " ;
 				_t1->printThread();
 				cout << endl;
 			}
 		else if(_isAssigned)
 			{ cout << _name << " is already assigned " << endl;	}
 		else
 			cout << _name << " cannot be assaigned.(No proper thread)" << endl;


	}
	bool isDone() {
		return (_workToDo <= 0);
	}
	bool isAssigned()
	{
		return _isAssigned;
	}
	int getMemoryNeeded()
	{
		return _totalMemoryNeeded;
	}
private:
	int _workToDo;
	bool _isAssigned;
};

class Process;

class TaskIterator : public AbstractIterator
{
public:
	TaskIterator(const Process *collection);
	void First();
	void Next();
	AbstractTask* CurrentItem() const;
	bool IsDone()const;
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

	void Action(){}
	
	void assignToPool()
	{
		TaskIterator* _iterator = this->CreateIterator();
		for(_iterator->First();!_iterator->IsDone();_iterator->Next())
		{
			if((*_iterator).CurrentItem() != NULL)
				(*_iterator).CurrentItem()->assignToPool();
		}
		delete _iterator;
	}
	
	bool isDone()
	{
		bool _returner = true;
		TaskIterator* _iterator = this->CreateIterator();
		for (_iterator->First(); !_iterator->IsDone(); _iterator->Next())
		{
			if (!(*_iterator).CurrentItem()->isDone())
			{
				_returner = false;
				break;
			}
		}
		return _returner;
	}
	bool isAssigned()
	{
		bool _returner = true;
		TaskIterator* _iterator = this->CreateIterator();
		for (_iterator->First(); !_iterator->IsDone(); _iterator->Next())
		{
			if (!(*_iterator).CurrentItem()->isAssigned())
			{
				_returner = false;
				break;
			}
		}
		return _returner;

	}

	int getMemoryNeeded()
	{
		int totalMemory = 0;
		TaskIterator* _iterator = this->CreateIterator();
		for (_iterator->First(); !_iterator->IsDone(); _iterator->Next())
		{
			totalMemory += _iterator->CurrentItem()->getMemoryNeeded();
		}
		return totalMemory;

	}
private:
	vector<AbstractTask*> _innerTasks;

};

class TaskQueue : public AbstractObserver //Container for waiting tasks and an observer of the threadpool.
{
public:
	void Update(string _INFO)
	{
		if(_INFO == "availableThread")
			InsertToPool();

		cout << "Task queue gets a notify : " << _INFO	<< endl;
	}
	void InsertToPool()
	{
		if(_innerTasks.empty())
			return;
		if(_innerTasks.front()->isAssigned())
			_innerTasks.pop();
		if(!_innerTasks.empty())
			_innerTasks.front()->assignToPool();
		

	}
	void Add(AbstractTask* _TASK)
	{
		_innerTasks.push(_TASK);
	}
private:
	queue<AbstractTask*> _innerTasks;

};









//---------------------------------------------
TaskIterator::TaskIterator(const Process *collection) :
	_collection(collection), _current(0) {
}
void TaskIterator::First() {
	_current = 0;
}
void TaskIterator::Next() {
	_current++;
}
AbstractTask* TaskIterator::CurrentItem() const {
	return (IsDone() ? NULL : _collection->get(_current));
}
bool TaskIterator::IsDone() const {
	return _current >= _collection->getCount();
}

//-------------------------------------------
ThreadIterator::ThreadIterator(const ThreadPool *collection) :
	_collection(collection), _current(0) {
}

void ThreadIterator::First() {
	_current = 0;
}

void ThreadIterator::Next() {
	_current++;
}

bool ThreadIterator::IsDone() const {
	return _current >= _collection->getCount();
}

Thread* ThreadIterator::CurrentItem() const {
	return (IsDone() ? NULL : _collection->get(_current));
}


//-------------------------------------------

int main()
{

	Process* _task1 = new Process("Dota 2");
	AbstractTask* _task2 = new Task("Matchmaking",7,13);
	AbstractTask* _task3 = new Task("Hero Banning",2,241);
	AbstractTask* _task4 = new Task("Hero Selection",3,456);
	AbstractTask* _task5 = new Task("Game starting",5,98);

	_task1->add(_task2);
	_task1->add(_task3);
	_task1->add(_task4);
	_task1->add(_task5);

	AbstractTask* _task6 = new Task("Deleting browser history",3,123);
	AbstractTask* _task7 = new Task("Handling calendar",2,56);
	AbstractTask* _task8 = new Task("Printing documents",4,77);

	TaskQueue* _tq1 = new TaskQueue();

	ThreadPool::getInstance()->Attach(_tq1);
	_tq1->Add(_task1);
	
	_tq1->Add(_task6);
	_tq1->Add(_task7);
	_tq1->Add(_task8);
	for(int i = 0 ; i < 3 ; ++i)
		ThreadPool::getInstance()->createThread("LThread");
	
	ThreadPool::getInstance()->createThread("HThread");
	

	while(true)
	{
		int a ;

		cin >> a;

		if(a == 0)
			break;

		ThreadPool::getInstance()->runAll();
	}

	
	return 0;
}
