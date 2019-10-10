
/*
跳跃表：
数据结构定义：
	跳跃表节点：
		key,data,节点所在的层level, level个next指针（指向每一层的下一个节点）
	跳跃表定义：
		head节点、tail节点, max_level


插入：InsertNode(key, data)
删除：DeleteNode(key)
查询某个key是否存在跳表中：Contains(key)
根据key查询data：GetData(key)
查询大于等于key的节点返回，prev返回每一层的前驱节点：FindGreaterOrEqual(key, Node** prev)


跳跃表的迭代器：

*/

#define MAX_LEVEL 10
typedef key_type int;

// 跳跃表 节点：
struct SkipListNode{
	key_type key;
	void* data;
	int level;
	SkipListNode** next; // SkipListNode* next[MAX_LEVEL]
	SkipListNode(key_type key, void* data, int level)
	{
		this->key=key;
		this->data=data;
		this->level=level;
		next=new SkipListNode*[level];
	}
};


class SkipList{
public:
	SkipList(int max_level);
	~SkipList();
	
	void InsertNode(key_type key, void* data);
	void DeleteNode(key_type key);
	bool Contains(key_type key);
	void* GetData(key_type key);
	SkipListNode* FindGreaterOrEqual(key_type key, SkipListNode** prev);

	void displayList();

private:
	int RandomLevel();
	int keyCompare(key_type lhs, key_type rhs)
	{
		return lhs-rhs;
	}

	SkipListNode* head;
	SkipListNode* tail;
	int max_level;
};

SkipList::SkipList(int max_level)
{
	this->max_level=max_level>0 ? max_level : 1;
	//head=new SkipList(0, 0, max_level); // max_level不起作用
	head=new SkipListNode();
	//tail=new SkipList(0, 0, max_level);
	tail=new SkipListNode();
	head->next=new SkipListNode*[max_level];
	for(int i=0; i<max_level; i++)
		head->next[i]=tail;
}

SkipList::~SkipList()
{
	SkipListNode* cur=head;
	while(cur!=tail)
	{
		SkipList* next=cur->next[0];
		delete cur->next;
		delete cur;
		cur=next;
	}
	delete tail;
}

SkipList::~SkipList()
{
	SkipListNode* cur=NULL;
	while(head->next[0]!=tail)
	{
		cur=head->next[0];
		head->next[0]=cur->next[0];
		delete cur->next;
		delete cur;
	}
	delete head->next;
	delete head;
	delete tail;
}

/*
插入节点算法：
	随机算法生成小于max_level的整数k，作为新节点的level。
	构造新节点。
	根据key确定新节点在0到k-1层的前驱节点。
		从第k-1层开始，首先确定新节点在k-1层的插入位置。
		向k-2层，从k-1层的前驱节点往后，找到k-2层的插入位置。
		直到第0层。
*/
// 允许插入相同的key
void SkipList::InsertNode(key_type key, void* data)
{
	int k=RandomLevel(key);
	SkipListNode* newNode=new SkipListNode(key, data, k);
	
	SkipListNode* curPrev=head;
	for(int level=k-1; level>=0; level--)
	{
		while(curPrev->next[level]!=tail  &&  keyCompare(curPrev->next[level].key, key)<0)
			curPrev=curPrev->next[level];
		newNode->next[level]=curPrev->next[level];
		curPrev->next[level]=newNode;
	}
}

// 不允许插入相同的key。最坏情况下，需要查找到第0层，才能确定key已经存在。
void SkipList::InsertNode(key_type key, void* data)
{
	SkipListNode* update[max_level];
	SkipListNode* cur=head;
	
	for(int i=max_level-1; i>=0; --i)
	{
		if(cur->next[i]==tail  ||  cur->next[i]->key>key)
			update[i]=cur;
		else
		{
			while(cur->next[i]!=tail  &&  cur->next[i]->key<key)
				cur=cur->next[i];
			if(cur->next[i]!=tail  &&  cur->next[i]->key==key)
			{
				cur->next[i]->data=data; // 更新key,返回
				return;
			}
			update[i]=cur;
		}
	}
	
	//
	int level=RandomLevel();
	SkipListNode* temp=new SkipListNode(key, data, level);
	
	for(int i=0; i<level; ++i)
	{
		temp->next[i]=update[i]->next[i];
		update[i]->next=temp;
	}
}


/*
删除节点算法：
	从max_level层开始查找key，当在第k层找到key时，依次从第k层到第0层删除对应节点。
*/
// 允许重复的key，需要删除多个key
void SkipList::DeleteNode(key_type key)
{
	SkipListNode* cur=head;
	vector<SkipListNode*> toDelete;
	
	for(int k=max_level-1; k>=0; k--)
	{
		while(cur->next[k]!=tail  &&  keyCompare(cur->next[k]->key, key)<0)
			cur=cur->next[k];
		
		if(cur->next[k]==tail  ||  keyCompare(cur->next[k]->key, key)>0)
			continue;
		
		// cur->next[k]->key == key
		SkipListNode* newNext=cur->next[k];
		while(newNext!=tail  &&  keyCompare(newNext->key, key)==0)
		{
			if(k==0)
			{
				toDelete.push_back(newNext);
			}
			newNext=newNext->next[k];			
		}
		cur->next[k]=newNext;
	}
	
	for(int i=0; i<toDelete.size(); ++i)
	{
		delete toDelete[i]->next;
		delete toDelete[i];
	}
}

// 不允许重复的key，删除最多一个key
void SkipList::DeleteNode(key_type key)
{
	SkipListNode* cur=head;
	vector<SkipListNode*> toDelete;
	
	for(int k=max_level-1; k>=0; k--)
	{
		while(cur->next[k]!=tail  &&  keyCompare(cur->next[k]->key, key)<0)
			cur=cur->next[k];
		
		if(cur->next[k]==tail  ||  keyCompare(cur->next[k]->key, key)>0)
			continue;
		
		// cur->next[k]->key == key
		
		if(k==0)
		{
			SkipListNode* tmp=cur->next[k];
			cur->next[k]=cur->next[k]->next;
			delete tmp->next;
			delete tmp;
		}
		else
		{
			cur->next[k]=cur->next[k]->next;
		}
	}
}

// 不允许重复的key，删除最多一个key
void SkipList::DeleteNode(key_type key)
{
	SkipListNode* update[max_level];
	SkipListNode* cur=head;
	for(int i=max_level-1; i>=0; --i)
	{
		if(cur->next[i]==tail  ||  cur->next[i]->key>key)
			update[i]=NULL;
		else
		{
			while(cur->next[i]!=tail  &&  cur->next[i].key<key)
				cur=cur->next[i];
			if(cur->next[i]!=tail  &&  cur->next[i].key==key
				update[i]=cur;
			else
				update[i]=nullptr;
		}
	}
	
	SkipListNode* tmp=NULL;
	for(int i=0; i<max_level; ++i)
	{
		if(update[i])
		{
			tmp=upate[i]->next[i];
			update[i]->next[i]=tmp->next[i];
		}
	}
	
	if(tmp==NULL)
	{
		delete tmp->next;
		delete tmp;
	}
}


//
void* SkipList::GetData(key_type key)
{
	SkipListNode* cur=head;
	for(int level=max_level-1; level>=0; level--)
	{
		while(cur->next[level]!=tail  &&  cur->next[level].key<key)
			cur=cur->next[level];
		if(cur->next[level]!=tail  &&  cur->next[level].key==key)
			return cur->next[level].data;
	}
	return NULL;
}


bool SkipList::Contains(key_type key)
{
	SkipListNode* cur=head;
	for(int level=max_level-1; level>=0; level--)
	{
		while(cur->next[level]!=tail  &&  cur->next[level].key<key)
			cur=cur->next[level];
		if(cur->next[level]!=tail  &&  cur->next[level].key==key)
			return true;
	}
	return false;
}

/*
随机算法：
	满足p=1/2几何分布
	
*/
int SkipList::RandomLevel()
{
	int level=0;
	while(rand()%2  &&  level<max_level-1)
		++level;
	return level;
}


/*
返回大于等于key的节点。当prev不为空，*prev返回key在每一层的前驱节点
*/
SkipListNode* SkipList::FindGreaterOrEqual(key_type key, SkipListNode** prev);
{
	SkipListNode* cur=head;
	for(int level=max_level-1; level>=0; level--)
	{
		while(cur->next[level]!=tail  &&  cur->next[level]->key < key)
			cur=cur->next[level];
		if(prev)
			prev[level]=cur;
		if(level==0)
			return cur->next[level]; // 可能是tail
	}
}


/*
跳表定义2：
	top指针指向最高层的第一个节点
	第i层的节点通过down指针指向下一层相同值的元素
	在每一层，-1和1两个元素都出现？？
*/

/*
leveldb 跳表：
*/
// leveldb 节点
struct SkipList::Node{
	key_type key;
	AtomicPointer next_[1];// 和节点level相同大小
};

// Leveldb 插入元素, 不允许插入相同key
void SkipList::Insert(const key_type& key)
{
	Node* prev[max_level];
	Node* x=FindGreaterOrEqual(key, prev); //
	
	assert(x==NULL  ||  !Equal(key, x->key));
	
	int height=RandomLevel();
	if(height>GetMaxHeight())
	{
		for(int i=GetMaxHeight(); i<height; i++)
			prev[i]=head;
		SetMaxHeight(height);
	}
	
	x=NewNode(key, height);
	for(int i=0; i<height; i++)
	{
		//x->SetNext(i, prev[i]->next[i]); 
		x->next[i]=prev[i]->next[i];
		prev[i]->next[i]=x;
	}
}

bool SkipList::Contains(const key_type& key)
{
	Node* x=FindGreaterOrEqual(key, NULL);
	if(x!=NULL  &&  Equal(key, x->key))
		return true;
	else
		return false;
}

Node* SkipList::FindGreaterOrEqual(key_type key, Node** prev);
{
	Node* x=head;
	int level=GetMaxHeight()-1;
	while(true)
	{
		Node* next=x->next[level];
		if(KeyIsAfterNode(key, next)) // 当next==tail, 返回false？
			x=next;
		else
		{
			if(prev!=NULL)
				prev[level]=x;
			if(level==0)
				return next;
			else
				level--;
		}
	}
}

