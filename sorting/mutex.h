
#include"pthread_util.h"

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


Mutex::Mutex()
{
	PthreadCall("Init mutex", pthread_mutex_init(&mu_, NULL)); // 传递char指针，不拷贝数组，使用特定字符或长度参数保证不越界
	// mutex_=PTHREAD_MUTEX_INITIALIZER;
}

Mutex::~Mutex()
{
	PthreadCall("Destroy mutex", pthread_mutex_destroy(&mu_));
}

void Mutex::Lock()
{
	PthreadCall("Lock mutex", pthread_mutex_lock(&mu_));
}

void Mutex::Unlock()
{
	PthreadCall("Unlock mutex", pthread_mutex_unlock(&mu_));
}

void Mutex::AssertHeld()
{

}