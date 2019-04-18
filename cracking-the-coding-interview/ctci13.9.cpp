#include<stdio.h>
#include<algorithm>
#include<utility>

template<typename T>
class smart_ptr{
private:
	//typedef element_type T;
	//typedef weak_type std::weak_ptr<T>;

	T* object;
	unsigned int *refCnt;
	
public:
	smart_ptr();
	smart_ptr(T*);
	~smart_ptr();
	
	smart_ptr<T>& operator=(smart_ptr<T> &sp);
	void reset();
	void reset(T*);
	void swap(smart_ptr<T> &sp);
	T* get() { return object; }
	T& operator*() const ;
	T* operator->() const ;
	unsigned int use_count() { return *refCnt; }
	unsigned int* ref() { return refCnt; }
	bool unique() { return *refCnt==1; }
};

template<typename T>
smart_ptr<T>::smart_ptr()
{
	object=NULL;
	refCnt=NULL;
}

template<typename T>
smart_ptr<T>::smart_ptr(T* t)
{
	object=t;
	refCnt=new unsigned int;
	*refCnt=1;
}

template<typename T>
smart_ptr<T>::~smart_ptr()
{
	printf("destructor:\n");
	reset();
	//printf("destructor clear\n");
}

template<typename T>
void smart_ptr<T>::reset()
{
	if(object!=NULL)
	{
		if(--(*refCnt)==0)
		{
			delete object;
			delete refCnt;
			object=NULL;
			refCnt=NULL;
			printf("rest or clear\n");
		}
	}
}

template<typename T>
void smart_ptr<T>::reset(T* o)
{
	printf("rest:\n");
	reset();
	//printf("reset clear\n");
	
	if(o!=NULL)
	{
		object=o;
		refCnt=new unsigned int;
		*refCnt=1;
	}
}

template<typename T>
smart_ptr<T>& smart_ptr<T>::operator=(smart_ptr<T> &sp)
{
	if(this != &sp)
	{
		printf("operator=:\n");
		reset();
		//printf("operator= clear\n");
		
		object=sp.get();
		refCnt=sp.ref();
		*refCnt=*refCnt+1;
	}
	return *this;
}

template<typename T>
void smart_ptr<T>::swap(smart_ptr<T> &sp)
{
	std::swap(object, sp.get());
	std::swap(refCnt, sp.ref());
}

template<typename T>
T& smart_ptr<T>::operator*() const
{
	return *object;
}

template<typename T>
T* smart_ptr<T>::operator->() const
{
	return object;
}

int main()
{
	{
		int *ip1 = new int();
		*ip1 = 11111;
		int *ip2 = new int();
		*ip2 = 22222;
		smart_ptr<int> sp1(ip1), sp2(ip2);
		smart_ptr<int> spa = sp1;
		sp2 = spa;
	}
	return 0;
}
