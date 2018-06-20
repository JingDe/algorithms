#ifndef MUTEX_H_
#define MUTEX_H_

#include<pthread.h>

class CondVar;

class Mutex {
public:
	Mutex();
	~Mutex();

	void Lock();
	void Unlock();
	void AssertHeld();

	friend CondVar;

private:
	pthread_mutex_t mu_;

	Mutex(const Mutex&);
	void operator=(const Mutex&);
};

#endif