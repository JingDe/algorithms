#ifndef THREADPOOL_H_
#define THREADPOOL_H_

#include<vector>
#include<deque>
#include<memory>
#include<functional>

#include"mutex.h" 
#include"condvar.h"
#include"thread.h"

class ThreadPool
{
public:
	typedef std::shared_ptr<Thread> ThreadPtr;
	typedef std::function<void ()> Task;
	
	ThreadPool();
	~ThreadPool();
	
	void start(int numThreads);
	void stop();
	
	void run(const Task& f);

private:
	void runInThread();
	Task take();
	
	Mutex mutex_;
	CondVar cond_;	
	std::vector<ThreadPtr> threads_;
	std::deque<Task> queue_;
	bool running_;	
};

#endif
