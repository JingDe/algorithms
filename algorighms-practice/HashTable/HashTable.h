
// 分离链接法哈希表
template<typename T>
class HashTable{
public:
	explicit HashTable(int size=101);
	bool contains(const T& x) const;
	
	void makeEmpty();
	void insert(const T& x);
	void remove(const T& x);

private:
	vector<list<T> > lists_;//
	int currentSize_;
	
	void rehash();
	int myhash(const T& x) const;
};

int hashVal(const string& key);
int hashVal(int key);

template<typename T>
int HashTable::myhash(const T& x) const
{
	int hashVal=hashVal(x);
	
	hashVal%= lists_.size();
	if(hashVal < 0)
		hashVal += lists_.size();
	
	return hashVal;
}

template<typename T>
void HashTable::makeEmpty()
{
	for(int i=0; i<lists_.size(); i++)
		lists_[i].clear();
}

template<typename T>
bool HashTable::contains(const T& x) const
{
	const list<T>& whichList=lists_[myhash(x)];
	return find(whichList.begin(), whichList.end(), x)!=whichList.end();
}

template<typename T>
void HashTable::rehash()
{
	vector<list<T> > oldLists=lists_;
	
	lists_.resize(nextPrime(2*lists_.size()));
	for(int j=0; j<lists_.size(); j++)
		lists_[j].clear();
	
	currentSize_=0;
	for(int i=0; i<oldLists.size(); ++i)
	{
		list<T>::iterator itr=oldLists[i].begin();
		while(itr!=oldLists[i].end())
			insert(*itr++);
	}
}
