#pragma once
#include <tuple>
#include "FuncPointer.h"
#include <queue>
#include <thread>
#include <condition_variable>
#include <iostream>

class BaseTask 
{
public:
	virtual ~BaseTask() {};
	void execute() 
	{
		call();
	}
private:
	virtual void call() = 0;
};

template<typename ...ARGS>
class Task : public BaseTask
{
public:
	Task(ARGS ...args) : m_TaskParams(std::make_tuple(args...)){}

	~Task() {}

	void call() 
	{
		std::apply(function, m_TaskParams);
	}
	std::function<void(ARGS...)> function;
private:
	std::tuple<ARGS ...> m_TaskParams;
};

class Worker;

class TaskManager 
{
public:
	TaskManager();
	~TaskManager();

	void addTask(BaseTask &baseTask);

	bool empty() const;

	BaseTask* getTask();

private:
	mutable std::mutex mutex;
	std::condition_variable conditionVariable;
	std::queue<BaseTask *> container;
	std::vector<Worker *> workers;
	const unsigned int numOfWorkers;
};

class Worker 
{
public:
	Worker(std::condition_variable& conditionVariable, TaskManager &taskManager);

	~Worker();
	//loop
	void loop();
	//wait until notified
	void wait();
	//execute
	void execute();
private:
	std::thread thread;
	std::condition_variable& conditionVariable;
	TaskManager& taskManager;
	std::mutex mutex;
	bool running = true;
	static unsigned int counter;
	unsigned int id;
};
