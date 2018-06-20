#include"mutex_lock.h"

MutexLock::MutexLock(Mutex& mu) :mu_(mu) {
	mu_.Lock();
}


MutexLock::~MutexLock() {
	mu_.Unlock();
}
