#include"ThreadPool.h"
#include"mutex_lock.h"

#include<exception>
#include<algorithm>
#include<functional>

ThreadPool::ThreadPool()
	:mutex_(),
	cond_(&mutex_),
	running_(false)
{
}

ThreadPool::~ThreadPool()
{
	if(running_)
		stop();
}

void ThreadPool::start(int numThreads)
{
	running_=true;
	threads_.reserve(numThreads);
	for(int i=0; i<numThreads; ++i)
	{
		threads_.push_back(std::make_shared<Thread>( std::bind(&ThreadPool::runInThread, this) ));
		threads_[i]->start();
	}
} 

void ThreadPool::stop()
{
	running_=false;
	cond_.SignalAll();
	for_each(threads_.begin(), threads_.end(), std::bind(&Thread::join, std::placeholders::_1));
}

void ThreadPool::run(const Task& task)
{
	if(threads_.empty())
		task();
	else
	{
		MutexLock lock(mutex_);
		queue_.push_back(task);
		cond_.Signal();
	}
}

ThreadPool::Task ThreadPool::take()
{
	MutexLock lock(mutex_);
	while(queue_.empty()  && running_)
		cond_.Wait();
	Task task;
	if(!queue_.empty())
	{
		task=queue_.front();
		queue_.pop_front();
	}
	return task;
}

void ThreadPool::runInThread()
{
	try{
		while(running_)
		{
			Task task(take());
			if(task)
				task();
		}
	}
	catch (const std::exception& ex)
	{
		fprintf(stderr, "exception caught in ThreadPool\n");
		fprintf(stderr, "reason: %s\n", ex.what());
		abort();
	}
	catch (...)
	{
		fprintf(stderr, "unknown exception caught in ThreadPool\n");
		abort();
	}
}
