
#include"mutex.h"
#include"condvar.h"
#include"mutex_lock.h"

template<typename T>
class BlockingQueue
{
public:
	BlockingQueue()
		:mutex_(),notEmpty_(mutex_),queue_(){}
	
	void put(const T& x)
	{
		MutexLock lock(mutex_);
		queue_.push_back(x);
		notEmpty_.notify();
	}
	
	T take()
	{
		MutexLock lock(mutex_);
		while(queue_.empty)
		{
			notEmpty_.wait();
		}
		T front(queue_.front());
		queue_.pop_front();
		return front;
	}
	
	size_t size() const
	{
		MutexLock lock(mutex_);
		return queue_.size();
	}
	
private:
	Mutex mutex_;
	Condition notEmpty_;
	std::deque<T> queue_;	
}
