

class LRUCache {
public:
    LRUCache(int capacity) {
        this->capacity=capacity;
		this->count=0;
    }
    
    int get(int key) {
        list<ELEM>::iterator it=std::find_if(elems.begin(), elems.end(), [=](const ELEM& e){
			return e.key==key;
		});
		if(it!=elems.end())
		{
			ELEM ans=*it;
			// 移动到链表表头
			elems.erase(it);
			elems.insert(elems.begin(), ans);
			return ans.value;
		}
		return -1;
    }
    
    void put(int key, int value) {
		list<ELEM>::iterator it=std::find_if(elems.begin(), elems.end(), [=](const ELEM& e){
			return e.key==key;
		});
		if(it!=elems.end())
		{
			it->value=value;
			return;
		}
		
        if(count>=capacity)
		{
			elems.pop_back();
			count--;
		}
		elems.insert(elems.begin(), ELEM(key, value));
		count++;		
    }
	
private:
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