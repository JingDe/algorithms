#ifndef MUTEX_LOCK_H_
#define MUTEX_LOCK_H_

#include"mutex.h"

class MutexLock {
public:
	MutexLock(Mutex& mu);
	~MutexLock();

private:
	Mutex & mu_; 
	
	MutexLock(const MutexLock&);
	void operator=(const MutexLock&);
};

#endif
