#include "TaskManager.h"


TaskManager::TaskManager()
	: numOfWorkers(std::thread::hardware_concurrency())
{
	for (unsigned int i = 0; i < numOfWorkers; i++)
	{
		workers.push_back(new Worker(conditionVariable, *this));
	}
}

TaskManager::~TaskManager(){}

void TaskManager::addTask(BaseTask & baseTask)
{
	{
		std::lock_guard<std::mutex> lock(mutex);
		container.push(&baseTask);
	}
	conditionVariable.notify_one();
}

bool TaskManager::empty() const
{
	std::lock_guard<std::mutex> lock(mutex);
	return container.empty();
}

BaseTask * TaskManager::getTask()
{
	BaseTask *result;
	{
		std::lock_guard<std::mutex> lock(mutex);
		result = container.front();
		container.pop();
	}
	return result;
}

unsigned int Worker::counter = 0;

Worker::Worker(std::condition_variable & conditionVariable, TaskManager & taskManager) : conditionVariable(conditionVariable), taskManager(taskManager)
{
	id = ++counter;
	thread = std::thread(std::bind(&Worker::loop, this));
}

Worker::~Worker()
{
	running = false;
}

void Worker::loop()
{
	while (running)
	{
		std::cout << "Thread loop \n";
		wait();
		execute();
	}
}

void Worker::wait()
{

	std::unique_lock<std::mutex> lock(mutex);
	while (taskManager.empty())
	{
		conditionVariable.wait(lock);
		std::cout << "Awoken! Thread ID: " << id << std::endl;
	}
}

void Worker::execute()
{
	std::cout << "Executing \n";
	auto task = taskManager.getTask();
	task->execute();
	delete task;
}
