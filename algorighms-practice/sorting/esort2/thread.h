#ifndef THREAD_H_
#define THREAD_H_

#include<functional>
#include<string>

class Thread {
public:
	typedef std::function<void(void)> ThreadFunc; // �̺߳�������

	explicit Thread(const ThreadFunc& func);
	~Thread();

	void start();
	int join();

	bool started() const { return started_; }
	pid_t tid() const { return tid_; }

private:

	pthread_t pthreadId_; // �߳�id
	pid_t tid_; // �ں˵��߳�id

	ThreadFunc func_; // �̺߳���

	bool started_;
	bool joined_;
	
	Thread(const Thread&);
	Thread& operator=(const Thread&);
};

#endif 
