#include"ThreadPool.h"

#incluce<exception>

ThreadPool::ThreadPool()
	:mutex_(),
	cond_(mutex_),
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
		threads_.push_back(new Thread(std::bind(&ThreadPool::runInThread, this));
		threads_[i].start();
	}
} 

void ThreadPool::stop()
{
	running_=false;
	cond_.notifyAll();
	for_each(threads_.begin(), threads_.end(), std::bind(&Thread::join(), _1));
}

void ThreadPool::run(const Task& task)
{
	if(threads_.empty())
		task();
	else
	{
		MutexLock lock(mutex_);
		queue_.push_back(task);
		cond_.notify();
	}
}

ThreadPool::Task ThreadPool::take()
{
	MutexLock lock(mutex_);
	while(queue_.empty()  && running_)
		cond_.wait();
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
    fprintf(stderr, "exception caught in ThreadPool %s\n", name_.c_str());
    fprintf(stderr, "reason: %s\n", ex.what());
    abort();
  }
  catch (...)
  {
    fprintf(stderr, "unknown exception caught in ThreadPool %s\n", name_.c_str());
    abort();
  }
}
