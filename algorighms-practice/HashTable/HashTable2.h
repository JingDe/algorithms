
// 平方探测法哈希表
template<typename T>
class HashTable{
public:
	explicit HashTable(int size=101);
	bool contains(const T& x) const;
	
	void makeEmpty();
	bool insert(const T& x);
	bool remove(const T& x);
	
	enum EntryType{ACTIVE, EMPTY, DELETED};

private:
	struct HashEntry{
		T element;
		EntryType info;
		
		HashEntry(const T& e=T(), EntryType i=EMPTY)
			:element(e),
			info(i)
		{}
	};
	
	vector<HashEntry> array_;
	int currentSize_;
	
	bool isActive(int currentPos) const;
	int findPos(const T& x) const;
	void rehash();
	int myhasn(const T& x) const;
};

template<typename T>
HashTable::HashTable(int size=101)
	:array_(nextPrime(size))
{
	makeEmpty();
}

template<typename T>
void HashEntry::makeEmpty()
{
	currentSize_=0;
	for(int i=0;; i<array_.size(); i++)
		array_[i].info=EMPTY;
}

template<typename T>
bool HashTable::contains(const T& x) const
{
	return isActive(findPos(x));
}

template<typename T>
int HashTable::findPos(const T& x) const
{
	int offset=1;
	int currentPos=myhash(x);
	
	while(array_[currentPos].info!=EMPTY &&  array_[currentPost].element!=x)
	{
		currentPos+=offset;
		offset+=2;
		if(currentPos >= array_.size())
			currentPos -= array_.size();
	}
	
	return currentPos;
}

template<typename T>
bool HashTable::isActive(int currentPos) const
{
	return array_[currentPos].info==ACTIVE;
}

template<typename T>
bool HashTable::insert(const T& x)
{
	int currentPos=findPost(x);
	if(isActive(currentPos))
		return false;
	
	array_[currentPos]=HashEntry(x, ACTIVE);
	
	if(++currentSize_ > array_.size()/2)
		rehash();
	
	return true;
}

template<typename T>
void HashTable::rehash()
{
	vector<HashEntry> oldArray=array_;
	
	array_.resize(nextPrime(2*oldArray.size()));
	for(int j=0;; j<array_.size(); j++)
		array_[j].info=EMPTY;
	
	currentSize_=0;
	for(int i=0; i<oldArray.size(); i++)
		if(oldArray[i].info==ACTIVE)
			insert(oldArray[i].element);
}

