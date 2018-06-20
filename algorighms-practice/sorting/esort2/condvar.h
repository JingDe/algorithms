#ifndef CONDVAR_H_
#define CONDVAR_H_

#include<pthread.h>

class Mutex;

class CondVar {
public:
	explicit CondVar(Mutex* mu);
	~CondVar();

	void Wait();
	void WaitForSeconds(int secs);
	void Signal();
	void SignalAll();

private:
	Mutex * mu_;

	pthread_cond_t cv_;
};



#endif