
class FooBar {
private:
    int n;

public:
    FooBar(int n) {
        this->n = n;
    }

    void foo(function<void()> printFoo) {
        
        for (int i = 0; i < n; i++) {
            
        	// printFoo() outputs "foo". Do not change or remove this line.
        	printFoo();
        }
    }

    void bar(function<void()> printBar) {
        
        for (int i = 0; i < n; i++) {
            
        	// printBar() outputs "bar". Do not change or remove this line.
        	printBar();
        }
    }
};


// 两个条件变量
class FooBar {
private:
    int n;
	pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER;
	pthread_cond_t cond1=PTHREAD_COND_INITIALIZER;
	pthread_cond_t cond2=PTHREAD_COND_INITIALIZER;
	bool flag1=false;
	bool flag2=false;

public:
    FooBar(int n) {
        this->n = n;
    }

    void foo(function<void()> printFoo) {
        
        for (int i = 0; i < n; i++) {
            if(i==0)
			{
				printFoo();
				pthread_mutex_lock(&mtx);
				flag1=true;
				// flag2=false;
				pthread_cond_signal(&cond1);
				pthread_mutex_unlock(&mtx);
			}
			else
			{
				pthread_mutex_lock(&mtx);
				while(flag2==false)
					pthread_cond_wait(&cond2, &mtx);
				// printFoo() outputs "foo". Do not change or remove this line.
				printFoo();
				flag2=false;
				flag1=true;
				pthread_mutex_unlock(&mtx);
				pthread_cond_signal(&cond1);
			}
        }
    }

    void bar(function<void()> printBar) {
        
        for (int i = 0; i < n; i++) {
            pthread_mutex_lock(&mtx);
			while(flag1==false)
				pthread_cond_wait(&cond1, &mtx);
        	// printBar() outputs "bar". Do not change or remove this line.
        	printBar();
			flag2=true;
			flag1=false;
			pthread_cond_signal(&cond2);
			pthread_mutex_unlock(&mtx);			
        }
    }
};

// 两把锁
class FooBar {
private:
    int n;
	pthread_mutex_t m1=PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_t m2=PTHREAD_MUTEX_INITIALIZER;

public:
    FooBar(int n) {
        this->n = n;
		pthread_mutex_lock(&m2);
    }

    void foo(function<void()> printFoo) {
        
        for (int i = 0; i < n; i++) {
            pthread_mutex_lock(&m1);
        	// printFoo() outputs "foo". Do not change or remove this line.
        	printFoo();
			pthread_mutex_unlock(&m2);
        }
    }

    void bar(function<void()> printBar) {
        
        for (int i = 0; i < n; i++) {
            pthread_mutex_lock(&m2);
        	// printBar() outputs "bar". Do not change or remove this line.
        	printBar();
			pthread_mutex_unlock(&m1);
        }
    }
};