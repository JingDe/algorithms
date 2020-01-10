
// 方法一：链表
class LRUCache {
public:
    LRUCache(int capacity) {
        this->capacity=capacity;
		this->count=0;
    }
    
    int get(int key) {
        list<ELEM>::iterator it=std::find_if(elems.begin(), elems.end(), [=](const ELEM& e){
            debug_print();
			return e.key==key;
		});
		if(it!=elems.end())
		{
			ELEM ans=*it;
			// 移动到链表表头
			elems.erase(it);
			elems.insert(elems.begin(), ans);
            debug_print();
			return ans.value;
		}
        debug_print();
		return -1;
    }
    
    void put(int key, int value) {
        list<ELEM>::iterator it=std::find_if(elems.begin(), elems.end(), [=](const ELEM& e){
                return e.key==key; });
		if(it!=elems.end())
		{
			it->value=value;
            //debug_print();
			//return;
            elems.erase(it);
            count--;
		}
        
        if(count>=capacity)
		{
			elems.pop_back();
			count--;
		}
		elems.insert(elems.begin(), ELEM(key, value));
		count++;
        debug_print();
    }
	
private:
    void debug_print()
    {
        //for(list<ELEM>::iterator it=elems.begin(); it!=elems.end(); ++it)
          //  printf("(%d,%d) ", it->key, it->value);
        //printf("\n");
    }
    
	struct ELEM{
		int key;
		int value;
		ELEM(int k, int v)
		{
			key=k;
			value=v;
		}
		ELEM& operator=(const ELEM& rhs)
		{
			this->key=rhs.key;
			this->value=rhs.value;
			return *this;
		}
	};
	list<ELEM> elems;
	int capacity;
	int count;
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
 
 
// 方法二： 哈希表unordered_map+链表，复杂度O(1)
class LRUCache {
public:
    LRUCache(int capacity) {
        size=capacity;
    }
    
    int get(int key) {
        if(kv.count(key)==0) // O(1)
			return -1;
		updateLRU(key);
		return kv[key]; // 返回值
    }
    
    void put(int key, int value) {
        if(kv.size()==size  &&  kv.count(key)==0) // O(1) O(1) key存在时不删除
			evict();
		updateLRU(key);
		kv[key]=value; // 插入或者更新值 O(1)
    }
	
private:
	void updateLRU(int key) // 将key插入到表头
	{
		if(kv.count(key))
			lru.earse(mp[key]); // O(1)
		lru.push_front(key); // O(1), 不会导致mp中的迭代器失效
		mp[key]=lru.begin(); // O(1)
	}
	
	void evict() // 淘汰lru元素
	{
		mp.erase(lru.back());  // O(1)
		kv.erase(lru.back()); // O(1)
		lru.pop_back(); // O(1)
	}

	int size;
	list<int> lru; // 从mru到lru，最近访问到最久访问
	unordered_map<int, list<int>::iterator> mp; // kv的key——lru的迭代器
	unordered_map<int, int> kv;	// 元素只在lru中移动，在kv中无序存储
	
	/*
		类似memcached、leveldb等实现：
		一个哈希表，一个lru链表。
		每个记录，同时包含链接哈希表冲突链 和 lru链表的指针。
		哈希表使用kv存储db的键值对。
		链表使用lru的顺序连接记录，便于淘汰。
	*/
};

class LRUCache {
public:
    LRUCache(int capacity) {
        this.->capacity=capacity;
    }
    
    int get(int key) {
        auto it=cache.find(key); // 
		if(it==cache.end())
			return -1;
		update(it);
		return it->second.first;
    }
    
    void put(int key, int value) {
        auto it=cache.find(key);
		if(it!=cache.end())
			update(it);
		else
		{
			if(cache.size()==capacity)
			{
				cache.erase(used.back());
				used.pop_back();
			}
			used.push_front(key);
		}
		cache[key]={value, used.begin()};
    }
	
private:

	typedef list<int> LI;
	typedef pair<int, LI::iterator> PII; // value+迭代器
	typedef unordered_map<int, PII> HIPII;

	void update(HIPII::iterator it)
	{
		int key=it->first;
		used.erase(it->second.second);
		used.push_front(key);
		it->second.second=used.begin();
	}
	
	int capacity;	
	HIPII cache; //unordered_map<int, pair<int, list<int>::iterator> > cache;
	LI used; //list<int> used;
};


class LRUCache {
public:
    LRUCache(int capacity) {
        this->capacity=capacity;
    }
    
    int get(int key) {
		if(cache.count(key)==0)
			return -1;
		hit(key, cache[key]->second);
		// item.push_front({key, cache[key]->second}); // 不会使迭代器或引用失效
		// item.erase(cache[key]); // 其他迭代器或引用不会失效
		// cache[key]=item.begin();
		return cache[key]->second; // value
    }
    
    void put(int key, int value) {
        if(item.size()==capacity  &&  cache.count(key)==0)
		{
			evict();
			// cache.erase(item.back()->first);
			// item.pop_back();
		}
		hit(key, value);
		// if(cache.count(key))
			// item.erase(cache[key]);
		// item.push_front({key, cache[key]->second});
		// cache[key]=item.begin();
		
		//cache[key]->second=value;
    }
	
private:
	typedef list<pair<int, int>> LIST;
	
	list<pair<int, int>> item;
	unordered_map<int, list<pair<int,int>>::iterator> cache;
	int capacity;
	
	void hit(int key, int value)
	{
        if(cache.count(key))
		    item.erase(cache[key]); // 其他迭代器或引用不会失效
		item.push_front({key, value}); // 不会使迭代器或引用失效        
		cache[key]=item.begin();
	}
	void evict()
	{
		cache.erase(item.back().first);
		item.pop_back();
	}
};

class LRUCache {
public:
    LRUCache(int capacity) {
        
    }
    
    int get(int key) {
        if(cache.find(key)==cache.end())
			return -1;
		item.splice(item.begin(), item, cache[key]);
		return cache[key]->second;
    }
    
    void put(int key, int value) {
        if(cache.find(key)==cache.end())
		{
			if(item.size()==capacity)
			{
				cache.erase(item.back().first);
				item.pop_back();
			}
			item.push_front({key, value});
			cache[key]=item.begin();
		}
		else
		{
			cache[key]->second=value;
			item.splice(item.begin(), item, cache[key]);
		}
    }
	
private:
	list<pair<int, int>> item;
	unordered_map<int, list<pair<int,int>>::iterator> cache; // splice不会使迭代器失效，所以存储迭代器
	int capacity;
};

class LRUCache {
public:
    LRUCache(int capacity) {
        
    }
    
    int get(int key) {
        
    }
    
    void put(int key, int value) {
        
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */