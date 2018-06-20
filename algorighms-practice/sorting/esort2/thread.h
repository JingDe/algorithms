#ifndef THREAD_H_
#define THREAD_H_

#include<functional>
#include<string>

class Thread {
public:
	typedef std::function<void(void)> ThreadFunc; // 线程函数类型

	explicit Thread(const ThreadFunc& func);
	~Thread();

	void start();
	int join();

	bool started() const { return started_; }
	pid_t tid() const { return tid_; }

private:

	pthread_t pthreadId_; // 线程id
	pid_t tid_; // 内核的线程id

	ThreadFunc func_; // 线程函数

	bool started_;
	bool joined_;
	
	Thread(const Thread&);
	Thread& operator=(const Thread&);
};

#endif 
