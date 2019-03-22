#ifndef BTREE_H_
#define BTREE_H_

#include<cstdio>
#include<cassert>
#include<algorithm>
//#include<list>
#include<vector>
#include<stack> 
#include<string>
#include<sstream>

// static const int M=5; // M叉B树，所有节点包含x个记录和x+1个子树指针，每个记录包含一个关键字和一个指向对应数据的指针
// static const int MAX_KEY=M-1; // 每个节点最多M-1个关键字，最多M个子树

// static const int MIN_KEY=(M+1)/2-1; // 非根节点最少math.ceil(M/2)-1个关键字
// static const int MIN_KEY_ROOT=1; // 根节点最少1个关键字

static const int M_DEFAULT=4; // 默认4叉B树


template<typename keytype, typename valuetype>
class BTree;

/* 
 *	BTNode
 */

template<typename keytype, typename valuetype>
class BTNode{
public:
	
	class RecordType{
	public:
		keytype key;
		valuetype value;	
		
        RecordType(const RecordType& other):key(other.key),value(other.value)
        {}
		RecordType(const keytype& k, const valuetype& v)
			:key(k),value(v)
		{	
		}
        RecordType()
			:key(),value()
		{
		}
		/*RecordType(keytype k, valuetype v)
			:key(k),value(v)
		{	
		}*/
		
		RecordType& operator=(const RecordType & rhs)
		{
			key=rhs.key;
			value=rhs.value;
			return *this;
		}
	};
	
private:	
	BTNode* parent_;
	//int num_;	// 记录个数
	std::vector<RecordType> records_; //记录列表，有序, 下标0~num_-1
	std::vector<BTNode*> children_; // 子节点列表, 下标0~num_
// children_[i]的所有记录都小于records_[i], children_[i+1]的所有记录都大于records_[i]	
	
public:
	BTNode();
	~BTNode();
	
	bool isLeaf(){
		return children_.empty();
	}
	void InsertLeafRecordData(int idx, keytype key, valuetype value);
	int FindIdx();
	void addRecordWithRightChild(const RecordType& record, BTNode* rightChild);
	void split(BTNode** rightN, RecordType *mid);
	
	int RecordNum(){
		return static_cast<int>(records_.size());
	}
	
	std::string toString();
	
	friend class BTree<keytype, valuetype>;
};

/* template<typename keytype, typename valuetype>
bool operator<(const typename BTNode<keytype, valuetype>::RecordType& lhs, const typename BTNode<keytype, valuetype>::RecordType& rhs)
{
	return (lhs.key<rhs.key);
}

template<typename keytype, typename valuetype>
bool operator==(const typename BTNode<keytype, valuetype>::RecordType& lhs, const typename BTNode<keytype, valuetype>::RecordType& rhs) // ??
{
	return (lhs.key==rhs.key);
} */

template<typename keytype, typename valuetype>
BTNode<keytype, valuetype>::BTNode()
	:parent_(0),records_(),children_()
{
	
}



template<typename keytype, typename valuetype>
BTNode<keytype, valuetype>::~BTNode()
{
	//for(std::vector<BTNode*>::it=children_.begin(); it!=children_.end(); it++)
	//	delete *it;
	parent_=0;
	records_.clear();
	children_.clear();
}

template<typename keytype, typename valuetype>
void BTNode<keytype, valuetype>::addRecordWithRightChild(const RecordType& record, BTNode* rightChild)
{		
	//typename std::vector<RecordType>::iterator it=upper_bound(records_.begin(), records_.end(), record);
	//int idx=it-records_.begin();// 确定新纪录record应该在节点的records_中的位置
	
	typename std::vector<RecordType>::iterator it=records_.begin();
	int idx=0;
	for(; it!=records_.end(); it++)
	{		
		if(it->key>record.key)
			break;
		idx++;
	}
	
	/*typename std::list<RecordType>::iterator it=records_.begin();
	int idx=0;
	for(; it!=records_.end(); it++)
	{		
		if(it->key>record.key)
			break;
		idx++;
	}*/
	
	records_.insert(it, record);
	children_.insert(children_.begin()+idx+1, rightChild);
	
	rightChild->parent_=this;
}



// 分裂节点p，获得右边节点rightN 和中间记录
// 节点数num，关键字数num+1。分裂后，左节点记录数left=(RecordNum-1)/2，关键字数left+1个。
// 右节点记录数right=RecordNum-left-1个，关键字数right+1个
// 中间记录返回给父节点
template<typename keytype, typename valuetype>
void BTNode<keytype, valuetype>::split(BTNode** rightN, RecordType *mid)
{
	printf("结点分裂前：%s\n", toString().c_str());
	if(parent_)
	{
		printf("分裂节点前，节点父节点：%s\n", parent_->toString().c_str());
	}
	
	BTNode* rightNode;
		
	// 分裂后左边节点保留left个键，右边保留right个键，中间一个插入到父节点
	int left=(RecordNum()-1)/2; // p->num_等于M,  下标0~left-1
	int right=RecordNum()-left-1; // 下标 left+1~p->num_-1
	
	*mid=records_[left];  // 下标left, vector
	
	printf("分裂中：左边0~~%d, 中间key %d, 右边%d~~%d\n", left-1, mid->key, left+1, RecordNum()-1);
	
	/*typename std::list<RecordType>::iterator ite=records_.begin();//list
	for(int i=0; i<left; i++)
	{
		ite++;
	}
	*mid=*ite;*/	

	*rightN=new BTNode();
	rightNode=*rightN;				
	rightNode->parent_=parent_;
	rightNode->records_.assign(records_.begin()+left+1, records_.end());  //p->records_[left+1, num_-1]//赋值函数？？
	if(!isLeaf())
	{
		rightNode->children_.assign(children_.begin()+left+1, children_.end());// p->children_[left+1...]
		for(typename std::vector<BTNode*>::iterator it=rightNode->children_.begin(); it!=rightNode->children_.end(); it++)
		{
			BTNode* oneChildNode=*it;
			oneChildNode->parent_=rightNode;
			// printf("rightNode %s has childNode %s\n", rightNode->toString().c_str(), it->toString().c_str());
			// printf("rightNode's childNode %s has  parentNode %s\n", it->toString().c_str(), it->parent_->toString().c_str());
		}
	}
	
	
	records_.resize(left);
	if(!isLeaf())
		children_.resize(left+1);// children_[0...left]
	
	printf("结点分裂后：%s\n", toString().c_str());
	printf("新结点：%s, 中间记录key %d\n", rightNode->toString().c_str(), mid->key);
	
}

template<typename keytype, typename valuetype>
int BTNode<keytype, valuetype>::FindIdx()
{
	if(parent_==0)
		return -1;
	
	//for(typename std::list<BTNode*>::iterator it=parent_->children_.begin();
/*	for(typename std::vector<BTNode*>::iterator it=parent_->children_.begin();  
		it!=parent_->children_.end(); it++)
	{
		if(*it==this)
			return it-parent_->children_.begin();
	}*/
    return std::find(parent_->children_.begin(), parent_->children_.end(), this)-parent_->children_.begin();
}


template<typename keytype, typename valuetype>
std::string BTNode<keytype, valuetype>::toString()
{
	std::string res;
	std::ostringstream oss;
	oss<<"<"<<RecordNum()<<" |";
	//for(typename std::list<RecordType>::iterator it=records_.begin(); it!=records_.end(); it++)
	for(typename std::vector<RecordType>::iterator it=records_.begin(); it!=records_.end(); it++)
		oss<<" ("<<it->key<<","<<it->value<<")";
	oss<<">";
	res=oss.str();
	return res;
}

template<typename keytype, typename valuetype>
void BTNode<keytype, valuetype>::InsertLeafRecordData(int idx, keytype key, valuetype value)
{
	RecordType r(key, value);
    // typename BTNode<keytype, valuetype>::RecordType
	records_.insert(records_.begin()+idx, r);
}



/* 
 *	BTree
 */

template<typename keytype, typename valuetype>
class BTree{
public:
	BTree();
	BTree(int m);
	~BTree();
	
	bool Search(const keytype& key, valuetype *value);
	
	void Insert(const keytype& key, const valuetype& value);
	//void insert(const RecordType& record);
	
	void Delete(const keytype& key);
	
	void Print();
	void Print2();
	

private:
	bool Search_for_Insert(const keytype& key, valuetype **value, BTNode<keytype, valuetype>** leaf, int *idx);
    void Insert_with_search(const keytype& key, const valuetype& value);
	void Insert_without_search(const keytype& key, const valuetype& value);
	
	void Delete_with_search(const keytype& key);
	void Delete_without_search(const keytype& key);
	bool Search_for_Delete(const keytype& key, BTNode<keytype, valuetype>** node, int *idx);
	
	// 寻找parent节点的idx子树的有富余记录的兄弟节点的索引siblingIdx
	bool findRichSibling(BTNode<keytype, valuetype> *parent, int idx, int *siblingIdx);
	
	void merge(BTNode<keytype, valuetype> * parent, int left, int right);
	void borrow(BTNode<keytype, valuetype>* parent, int leftIdx, int rightIdx, bool left);
	void borrow(BTNode<keytype, valuetype>* parent, int idx, int siblingIdx);
	
	void dfs(BTNode<keytype, valuetype>* cur, int level);

	void free1();
	void free2();
	void free3();
	void dfs_free(BTNode<keytype, valuetype> *);
	
	BTNode<keytype, valuetype> *root;
	
	const int M; // M叉B树，所有节点包含x个记录和x+1个子树指针，每个记录包含一个关键字和一个指向对应数据的指针
	const int MAX_KEY; // 每个节点最多M-1个关键字，最多M个子树

	const int MIN_KEY; // 非根节点最少math.ceil(M/2)-1个关键字
	const int MIN_KEY_ROOT; // 根节点最少1个关键字
};

template<typename keytype, typename valuetype>
BTree<keytype, valuetype>::BTree():root(0),M(M_DEFAULT),MAX_KEY(M-1),MIN_KEY((M+1)/2-1),MIN_KEY_ROOT(1)
{
}

template<typename keytype, typename valuetype>
BTree<keytype, valuetype>::BTree(int m):root(0),M(m),MAX_KEY(M-1),MIN_KEY((M+1)/2-1),MIN_KEY_ROOT(1)
{
}

template<typename keytype, typename valuetype>
BTree<keytype, valuetype>::~BTree()
{
	//free1();
	//free2();
	free3();
/* 	std::stack<BTNode<keytype, valuetype>*> S;
	BTNode<keytype, valuetype>* cur=0;
	if(root==0)
		return;
	S.push(root);
	while(!S.empty())
	{
		cur=S.top();
		if(cur->isLeaf())
		{
			S.pop();
			delete cur;
		}
		else
		{
			for(typename std::vector<BTNode<keytype, valuetype>*>::iterator it=cur->children_.begin(); 
				it!=cur->children_.end(); it++)
			{
				BTNode<keytype, valuetype>* child=*it;
				S.push(child);
			}
			cur->children_.clear();
		}
	} */
}

// BFS 遍历释放
template<typename keytype, typename valuetype>
void BTree<keytype, valuetype>::free1()
{
	std::deque<BTNode<keytype, valuetype>*> Q;
	BTNode<keytype, valuetype>* cur=0;
	if(root==0)
		return;
	Q.push_back(root);
	while(!Q.empty())
	{
		cur=Q.front();
		Q.pop_front();
		for(typename std::vector<BTNode<keytype, valuetype>*>::iterator it=cur->children_.begin(); 
			it!=cur->children_.end(); it++)
		{
			BTNode<keytype, valuetype>* child=*it;
			Q.push_back(child);
		}
		cur->children_.clear();
		delete cur;
	}
}

// DFS 递归方式释放
template<typename keytype, typename valuetype>
void BTree<keytype, valuetype>::free2()
{
	dfs_free(root);
}

template<typename keytype, typename valuetype>
void BTree<keytype, valuetype>::dfs_free(BTNode<keytype, valuetype>* node)
{
	if(node==NULL)
		return;
	BTNode<keytype, valuetype>* cur=node;
	for(typename std::vector<BTNode<keytype, valuetype>*>::iterator it=cur->children_.begin(); 
			it!=cur->children_.end(); it++)
	{
		dfs_free(*it);
	}
	delete cur;
}

// DFS 非递归方式释放
template<typename keytype, typename valuetype>
void BTree<keytype, valuetype>::free3()
{
	std::stack<BTNode<keytype, valuetype>*> S;
	BTNode<keytype, valuetype>* cur=0;
	if(root==0)
		return;
	S.push(root);
	while(!S.empty())
	{
		cur=S.top();
		S.pop();
		for(typename std::vector<BTNode<keytype, valuetype>*>::iterator it=cur->children_.begin(); 
			it!=cur->children_.end(); it++)
		{
			BTNode<keytype, valuetype>* child=*it;
			S.push(child);
		}
		cur->children_.clear();
		delete cur;
	}
}

template<typename keytype, typename valuetype>
void BTree<keytype, valuetype>::Insert(const keytype& key, const valuetype& value)
{
//	Insert_without_search(key, value);
	Insert_with_search(key, value);
}

// 插入一条记录，若已存在则更新value，否则插入叶节点中
template<typename keytype, typename valuetype>
void BTree<keytype, valuetype>::Insert_without_search(const keytype& key, const valuetype& value)
{
	printf("\n\n*** 插入<%d, %d> ***\n", key, value);
	
	BTNode<keytype, valuetype> *p=root;
	BTNode<keytype, valuetype> *rightNode;
	typename BTNode<keytype, valuetype>::RecordType newrecord(key, value);
	int idx;
	//typename std::list<typename BTNode<keytype, valuetype>::RecordType>::iterator it;
	typename std::vector<typename BTNode<keytype, valuetype>::RecordType>::iterator it;
	
	if(root==0)
	{
		printf("插入空root\n"); 
		root=new BTNode<keytype, valuetype>();
        root->parent_=0;
		root->records_.push_back(newrecord);
		root->children_.clear();
		return;
	}
	while(p)
	{
		//idx既是第一个大于等于新纪录的记录索引，也是可能的下一个考虑的儿子结点的索引
		
		//it=lower_bound(p->records_.begin(), p->records_.end(), newrecord);//查找记录的位置,vector
		for(it=p->records_.begin(); it!=p->records_.end(); it++)//list
		{
			if(it->key>=newrecord.key)
				break;
		}
		
		if(it!=p->records_.end()  &&  it->key==key)
		{
			printf("更新节点: %s, %d->%d\n", p->toString().c_str(), it->value, value);
			it->value=value;
			printf("更新后节点: %s, %d\n", p->toString().c_str(), it->value);
			return;
		}		
		idx=it - p->records_.begin();
		printf("child idx=%d\n", idx);
		
		if(p->isLeaf()) 
			break; // 当p无儿子节点，退出循环
		
		/*if(it!=p->records_.end())
		{
			idx=it - p->records_.begin();//vector迭代器
			//idx=std::distance(it, p->records_.begin());//list迭代器
			printf("middle child: %d\n", idx);
		}
		else 
		{			
			idx=p->RecordNum();// 走到最后一个儿子节点
            printf("end()-begin()=%d, idx=%d\n", it-p->records_.begin(), idx);
			printf("last child: %d, %d\n", p->RecordNum(), idx);
		}*/	
		
		p=p->children_[idx]; // 定位到相应儿子节点
	}

	printf("插入叶节点: %s\n", p->toString().c_str());
	p->records_.insert(it, newrecord); 
	printf("插入之后临时: %s\n", p->toString().c_str());

	// 从叶节点向上筛选
/* 	while(p->RecordNum()>MAX_KEY  &&  p!=root)
	{
		printf("分裂节点: %s\n", p->toString().c_str());
		
		BTNode<keytype, valuetype> *parent=p->parent_;//p不为root，则parent不为0
		p->split(&rightNode, &newrecord); // 分裂当前节点p，得到新的右半边节点和中间位置的记录
		parent->addRecordWithRightChild(newrecord, rightNode);// 临时插入一个记录和处于该记录右边的儿子指针
		rightNode->parent_=parent;
		
		p=parent;
	}
	if(p==root  &&  p->RecordNum()>=M) // 分裂根节点
	{
		printf("分裂根节点: %s\n", p->toString().c_str());
		p->split(&rightNode, &newrecord);
		
		BTNode<keytype, valuetype> *newroot=new BTNode<keytype, valuetype>();
		newroot->parent_=0;
		//newroot->num_=1;
		newroot->records_.push_back(newrecord);
		newroot->children_.push_back(p);
		newroot->children_.push_back(rightNode);
		root=newroot;
		
		p->parent_=root;
		rightNode->parent_=root;
	} */	
	while(p->RecordNum()>MAX_KEY)
	{
		printf("分裂节点: %s\n", p->toString().c_str());
				
		p->split(&rightNode, &newrecord); // 分裂当前节点p，得到新的右半边节点和中间位置的记录
		
		BTNode<keytype, valuetype> *parent=p->parent_;//p不为root，则parent不为0
        printf("parent=%p, p=%p, root=%p\n", parent, p, root);
		if(parent!=0) // TODO
		//if(p!=root)
		{
			printf("插入分裂节点和记录到父节点\n");
			parent->addRecordWithRightChild(newrecord, rightNode);// 临时插入一个记录和处于该记录右边的儿子指针
			rightNode->parent_=parent;
		
			p=parent;
		}
		else
		{
			printf("父节点为空,创建新根节点\n");
			BTNode<keytype, valuetype> *newroot=new BTNode<keytype, valuetype>();
			newroot->parent_=0;
			newroot->records_.push_back(newrecord);
			newroot->children_.push_back(p);
			newroot->children_.push_back(rightNode);
			root=newroot;
			
			p->parent_=root;
			rightNode->parent_=root;
			return;
		}
	}
	return;
}


template<typename keytype, typename valuetype>
void BTree<keytype, valuetype>::Insert_with_search(const keytype& key, const valuetype& value)
{
	printf("\n\n*** 插入<%d, %d> ***\n", key, value);
	
	BTNode<keytype, valuetype> *p=NULL;
	typename BTNode<keytype, valuetype>::RecordType newrecord(key, value);
	
	if(root==0)
	{
		printf("插入空root\n"); 
		root=new BTNode<keytype, valuetype>();
        root->parent_=0;
		root->records_.push_back(newrecord);
		root->children_.clear();
		return;
	}
	
	valuetype *oldValue;
	BTNode<keytype, valuetype> *leafNode;
	int idx=-1;
	bool found=Search_for_Insert(key, &oldValue, &leafNode, &idx);
	if(found)
	{
		printf("更新节点 %d->%d\n", *oldValue, value);
		*oldValue=value;
		return;
	}	
	printf("插入叶节点之前: %s\n", leafNode->toString().c_str());
	leafNode->InsertLeafRecordData(idx, key, value); // 叶节点有序位置插入记录
	printf("插入叶节点之后: %s\n", leafNode->toString().c_str());
	if(leafNode->records_.size()<=M-1)
	{
		printf("叶节点不分裂\n");
		return;
	}

	// 从叶节点向上筛选
	p=leafNode;
	BTNode<keytype, valuetype> *rightNode;
	while(p->RecordNum()>=M)
	{
		printf("分裂节点: %s\n", p->toString().c_str());
				
		p->split(&rightNode, &newrecord); // 分裂当前节点p，得到新的右半边节点和中间位置的记录
		
		BTNode<keytype, valuetype> *parent=p->parent_;//p不为root，则parent不为0
		if(parent!=NULL)
		{
			parent->addRecordWithRightChild(newrecord, rightNode);// 临时插入一个记录和处于该记录右边的儿子指针
			rightNode->parent_=parent;
		
			p=parent;
		}
		else
		{
			BTNode<keytype, valuetype> *newroot=new BTNode<keytype, valuetype>();
			newroot->parent_=0;
			newroot->records_.push_back(newrecord);
			newroot->children_.push_back(p);
			newroot->children_.push_back(rightNode);
			root=newroot;
			
			p->parent_=root;
			rightNode->parent_=root;
		}
	}
	return;
}

template<typename keytype, typename valuetype>
bool BTree<keytype, valuetype>::Search(const keytype& key, valuetype *value)
{
	BTNode<keytype, valuetype> * cur=root;
	typename BTNode<keytype, valuetype>::RecordType record(key, valuetype());
	
	//if(root==0)
	//	return false;
	while(cur)
	{
		//typename std::list<typename BTNode<keytype, valuetype>::RecordType>::iterator it=lower_bound(cur->records_.begin(), cur->records_.end(), record);
		//typename std::vector<typename BTNode<keytype, valuetype>::RecordType>::iterator it=lower_bound(cur->records_.begin(), cur->records_.end(), record);
		
		typename std::vector<typename BTNode<keytype, valuetype>::RecordType>::iterator it;
		for(it=cur->records_.begin(); it!=cur->records_.end(); it++)
		{
			if(it->key>=record.key)
				break;
		}
		
		if(it->key==key)
		{
			value=it->value;
			return true;
		}
		if(cur->isLeaf())
			return false;
		int idx=it-cur->records_.begin();
		cur=cur->children_[idx];
	}
	return false;
}

/*
template<typename keytype, typename valuetype>
bool BTree<keytype, valuetype>::Search_for_Insert(const keytype& key, valuetype **value, BTNode<keytype, valuetype>** leaf)
{
	BTNode<keytype, valuetype> * cur=root;
	typename BTNode<keytype, valuetype>::RecordType record(key, valuetype());
	
	if(root==0)
		return false;
	while(cur)
	{
		//typename std::list<typename BTNode<keytype, valuetype>::RecordType>::iterator it=lower_bound(cur->records_.begin(), cur->records_.end(), record);
		//typename std::vector<typename BTNode<keytype, valuetype>::RecordType>::iterator it=lower_bound(cur->records_.begin(), cur->records_.end(), record);
		
		typename std::vector<typename BTNode<keytype, valuetype>::RecordType>::iterator it;
		for(it=cur->records_.begin(); it!=cur->records_.end(); it++)
		{
			if(it->key>=record.key)
				break;
		}
		
		if(it->key==key)
		{
			*value=&(it->value);
			return true;
		}
		if(cur->isLeaf())
		{			
			break;
		}
		int idx=it-cur->records_.begin();
		cur=cur->children_[idx];
	}
	*left=&cur;
	return false;
}*/

// 辅助 Insert_with_search函数，查询key关键字，查找成功返回value，返回true
// 查找失败，返回false，返回key应该插入的叶节点leaf，和插入的位置idx
template<typename keytype, typename valuetype>
bool BTree<keytype, valuetype>::Search_for_Insert(const keytype& key, valuetype **value, BTNode<keytype, valuetype>** leaf, int *idx)
{
	BTNode<keytype, valuetype> * cur=root;
	typename BTNode<keytype, valuetype>::RecordType record(key, valuetype());
	
	if(root==0)
	{
		*leaf=root;
		*idx=0;
		return false;
	}
	while(cur)
	{		
		// vector随机访问迭代器，O(logN)
		//typename std::vector<typename BTNode<keytype, valuetype>::RecordType>::iterator it=lower_bound(cur->records_.begin(), cur->records_.end(), record);// 返回大于等于key的迭代器
		typename std::vector<typename BTNode<keytype, valuetype>::RecordType>::iterator it;
		it=lower_bound(cur->records_.begin(), cur->records_.end(), record);// 返回大于等于key的迭代器
		if(it!=cur->records_.end()  &&  it->key==key) // 
		{
			*value=&(it->value);
			return true;
		}
		// it指向一个大于key的元素，或者end()
		*idx=it-cur->records_.begin();
		
		if(cur->isLeaf())
		{			
			break;
		}
		
		cur=cur->children_[*idx];
	}
	*leaf=cur;
	return false;
}

// 辅助 Delete_with_search函数，查询key关键字，查找失败返回false
// 查找成功，返回true，返回key所在节点node和关键字位置idx
template<typename keytype, typename valuetype>
bool BTree<keytype, valuetype>::Search_for_Delete(const keytype& key, BTNode<keytype, valuetype>** node, int *idx)
{
	BTNode<keytype, valuetype> * cur=root;
    typename BTNode<keytype, valuetype>::RecordType record(key, valuetype());
	
	if(root==0)
	{
		return false;
	}
	while(cur)
	{		
		// vector随机访问迭代器，O(logN)
		typename std::vector<typename BTNode<keytype, valuetype>::RecordType>::iterator it=lower_bound(cur->records_.begin(), cur->records_.end(), record);// 返回大于等于key的迭代器
		if(it!=cur->records_.end()  &&  it->key==key) // 
		{
			*node=cur;
			*idx=it-cur->records_.begin();
			return true;
		}		
		
		if(cur->isLeaf())
		{			
			break;
		}
		*idx=it-cur->records_.begin();
		cur=cur->children_[*idx];
	}
	return false;
}

template<typename keytype, typename valuetype>
void BTree<keytype, valuetype>::Delete(const keytype& key)
{
	//Delete_without_search(key);
	Delete_with_search(key);
}

template<typename keytype, typename valuetype>
void BTree<keytype, valuetype>::Delete_without_search(const keytype& key)
{
	printf("\n\n*** 删除key=%d ***\n", key);

	BTNode<keytype, valuetype> *cur=root;
	typename BTNode<keytype, valuetype>::RecordType record(key, valuetype());
	int idx;
	BTNode<keytype, valuetype> *child;
	//typename std::list<typename BTNode<keytype, valuetype>::RecordType>::iterator it;
	typename std::vector<typename BTNode<keytype, valuetype>::RecordType>::iterator it;
	
	//寻找待删除记录所在节点cur
	//if(root==0)
	//	return;
	while(cur)
	{
		//it=lower_bound(cur->records_.begin(), cur->records_.end(), record);
		for(it=cur->records_.begin(); it!=cur->records_.end(); it++)//list
		{
			if(it->key>=record.key)
				break;
		}
		
		idx=it-cur->records_.begin();
		
		if(it->key==key)
			break;
		if(cur->isLeaf())
			return;
		
		cur=cur->children_[idx];
	}
	if(cur==0)
	{
		printf("删除中，不存在该key，返回\n");
		return;
	}
	
	
	if(cur->isLeaf()==false)//若待删除记录所在节点cur不是叶子结点，寻找后继记录所在的叶子结点child
	{
		printf("删除中，待删除记录不在叶子结点，寻找后继的叶子结点的记录替换它\n");
		child=cur->children_[idx+1]; // 后继结点
		while(child->isLeaf()==false)
			child=child->children_[0];
		printf("删除中，找到后继叶子结点：%s\n", child->toString().c_str());
		*it=child->records_[0];	// 用后继结点替换待删除记录
		//child->records_.pop_front();
		child->records_.erase(child->records_.begin());
		//child->num_--;
		
		printf("删除中，当前处理删除后继记录之后的叶子结点：%s\n", child->toString().c_str());
		cur=child;
	}
	else
	{
		printf("删除中，待删除结点是叶子结点%s，从中删除该key\n", cur->toString().c_str());
		cur->records_.erase(it);
		//cur->num_--;
	}
	
	while(true)
	{
		if(cur->RecordNum()>=MIN_KEY)
		{
			printf("删除中，当前结点的记录数满足最小值：%s, 返回\n", cur->toString().c_str());
			return;
		}
		
		if(cur==root &&  cur->RecordNum()>=1)
		{
			printf("删除中，当前结点为root，满足最少一个key:%s\n", cur->toString().c_str());
			return;
		}
		else if(cur==root)
		{
			printf("删除中，root记录数小于1, 更新新root:%s\n当前的B树：\n", root->toString().c_str());
			Print();
			BTNode<keytype, valuetype> *newroot=root->children_[0];
			delete root;
			root=newroot;
            root->parent_=0;
			//printf("更新后的树：");
			//Print();
			return;
		}
		
		idx=cur->FindIdx(); // 确定cur在其父节点的儿子节点链表中的索引
		printf("当前结点：%s, 是父结点的第%d个儿子结点\n", cur->toString().c_str(), idx);
		//assert(idx>=0);
		
		BTNode<keytype, valuetype> *parent=cur->parent_;
		
		
		int siblingIdx;//兄弟索引
		BTNode<keytype, valuetype> *sibling;//兄弟结点
		if(idx>0)
		{
			siblingIdx=idx-1;
			sibling=parent->children_[siblingIdx]; 
			
			if(sibling->RecordNum()>=MIN_KEY+1)
			{
				printf("从左兄弟结点借一个记录：%s\n", sibling->toString().c_str());
				borrow(parent, siblingIdx, idx, 1);
				return;
			}
		}
		else
		{
			siblingIdx=idx+1;		
			printf("右兄弟：siblingIdx=%d\n", siblingIdx);	
			sibling=parent->children_[siblingIdx];
			
			if(sibling->RecordNum()>=MIN_KEY+1)
			{
				printf("从右兄弟结点借一个记录：%s\n", sibling->toString().c_str());
				//cur->records_.insert(cur->records_.end(), sibling->records_.front());
				//sibling->records_.pop_front();
				//sibling->records_.erase(sibling->records_.begin());
				borrow(parent, idx, siblingIdx, 0);
				return;
			}
		}
		
		
		if(idx>0)// 与左兄弟结点合并
		{
			printf("与左兄弟结点、父结点记录合并\n");
			merge(parent, idx-1, idx);
		}
		else// 与右兄弟结点合并
		{
			printf("与右兄弟结点、父结点记录合并\n");
			merge(parent, idx, idx+1);
		}
		cur=parent;
	}
}


template<typename keytype, typename valuetype>
void BTree<keytype, valuetype>::Delete_with_search(const keytype& key)
{
	printf("\n\n*** 删除key=%d ***\n", key);
	if(root==0)
	{
		printf("删除空树\n"); 
		return;
	}
	
	BTNode<keytype, valuetype> *keyNode;
	int idx=-1; // idx返回查找成功时，key所在keyNode的关键字序号
	bool found=Search_for_Delete(key, &keyNode, &idx);
	if(found==false)
	{
		printf("删除节点不存在");
		return;
	}	
	
	BTNode<keytype, valuetype> *cur=NULL;
	BTNode<keytype, valuetype> *child;
	if(keyNode->isLeaf()==false)//若待删除记录所在节点cur不是叶子结点，寻找后继记录所在的叶子结点child
	{
		printf("删除中，待删除记录不在叶子结点，寻找后继的叶子结点的记录替换它\n");
		child=cur->children_[idx+1]; // 后继记录所在子树
		while(child->isLeaf()==false)
			child=child->children_[0];
		printf("删除中，找到后继叶子结点：%s\n", child->toString().c_str());
		keyNode->records_[idx]=child->records_[0];	// 用后继结点替换待删除记录
		child->records_.erase(child->records_.begin());
		
		printf("删除中，删除后继记录之后的叶子结点：%s\n", child->toString().c_str());
		cur=child;
	}
	else
	{
		printf("删除中，待删除结点是叶子结点%s，从中删除该key\n", cur->toString().c_str());
		//keyNode->DeleteRecordWithKey(key);
		keyNode->records_.erase(keyNode->records_.begin()+idx);		
		if(keyNode==root)
		{
			printf("删除，根节点即叶节点%s\n", cur->toString().c_str());
			return;
		}
		cur=keyNode;
	}
	
	while(true)
	{
		if(cur==root &&  cur->RecordNum()>=MIN_KEY_ROOT)
		{
			printf("删除中，当前结点为root，满足最少一个key:%s\n", cur->toString().c_str());
			return;
		}
		if(cur!=root  &&  cur->RecordNum()>=MIN_KEY)
		{
			printf("删除中，当前非根结点的记录数满足最小值：%s, 返回\n", cur->toString().c_str());
			return;
		}	
				
		idx=cur->FindIdx(); // 确定cur在其父节点的儿子节点链表中的索引
		printf("当前结点：%s, 是父结点的第%d个儿子结点\n", cur->toString().c_str(), idx);
		
		BTNode<keytype, valuetype> *parent=cur->parent_;
		int siblingIdx=-1;
		if(findRichSibling(parent, idx, &siblingIdx)==true)// 寻找超过M/2-1个记录的兄弟节点
		{
			borrow(parent, idx, siblingIdx);// 节点parent将索引为idx的子树向兄弟节点借一个记录
			return;
		}
		
		if(idx>0)// 与左兄弟结点合并
		{
			printf("与左兄弟结点、父结点记录合并\n");
			merge(parent, idx-1, idx);// 合并节点parent的两个子树记录和一个父节点记录
		}
		else// 与右兄弟结点合并
		{
			printf("与右兄弟结点、父结点记录合并\n");
			merge(parent, idx, idx+1);
		}	
		if(parent==root  &&  parent->RecordNum()==0)
		{
			printf("删除中，root记录数小于1, 更新新root:%s\n当前的B树：\n", root->toString().c_str());
			Print();
			BTNode<keytype, valuetype> *newroot=root->children_[0];
			delete root;
			root=newroot;
            root->parent_=0;
			//printf("更新后的树：");
			//Print();
			return;
		}
		
		cur=parent;
	}
	return ;
}

template<typename keytype, typename valuetype>
void BTree<keytype, valuetype>::merge(BTNode<keytype, valuetype>* parent, int left, int right)
{
	BTNode<keytype, valuetype>* leftN=parent->children_[left];
	BTNode<keytype, valuetype>* rightN=parent->children_[right];
	typename BTNode<keytype, valuetype>::RecordType mid=parent->records_[left];
	
	leftN->records_.push_back(mid);
	//leftN->records_.splice(leftN->records_.end(), rightN->records_);// list
	leftN->records_.reserve(leftN->records_.size()+rightN->records_.size());
	for(typename std::vector<typename BTNode<keytype, valuetype>::RecordType>::iterator it=rightN->records_.begin(); it!=rightN->records_.end(); it++)//vector
		leftN->records_.push_back(*it);
		
	//leftN->children_.splice(leftN->children_.end(), rightN->children_);// list
	leftN->children_.reserve(leftN->children_.size()+rightN->children_.size());
	for(typename std::vector<BTNode<keytype, valuetype>*>::iterator it=rightN->children_.begin(); it!=rightN->children_.end(); it++)//vector
		leftN->children_.push_back(*it);
	
	parent->records_.erase(parent->records_.begin()+left);
	parent->children_.erase(parent->children_.begin()+right);
}


template<typename keytype, typename valuetype>
void BTree<keytype, valuetype>::borrow(BTNode<keytype, valuetype>* parent, int leftIdx, int rightIdx, bool left)
{
	typename BTNode<keytype, valuetype>::RecordType midRecord=parent->records_[leftIdx];
	BTNode<keytype, valuetype> *leftNode=parent->children_[leftIdx];
	BTNode<keytype, valuetype> *rightNode=parent->children_[rightIdx];
	
	if(left)// left为1表示leftIdx->rightIdx
	{
		rightNode->records_.insert(rightNode->records_.begin(), midRecord);
		//rightNode->num_++;
		parent->records_[leftIdx]=leftNode->records_.back();
		leftNode->records_.pop_back();
		//leftNode->num_--;
	}
	else
	{
		leftNode->records_.push_back(midRecord);
		//leftNode->num_++;
		parent->records_[leftIdx]=rightNode->records_.front();
		rightNode->records_.erase(rightNode->records_.begin());
		//rightNode->num_--;
	}
}

// idx从siblingIdx借
template<typename keytype, typename valuetype>
void BTree<keytype, valuetype>::borrow(BTNode<keytype, valuetype>* parent, int idx, int siblingIdx)
{
	if(idx>siblingIdx)
		borrow(parent, siblingIdx, idx, 1);
	else
		borrow(parent, idx, siblingIdx, 0);
}

template<typename keytype, typename valuetype>
void BTree<keytype, valuetype>::Print()
{
	printf("打印B树：\n");
	// DFS
	BTNode<keytype, valuetype>* cur= root;
	int level=0;
	dfs(cur, level);
}

template<typename keytype, typename valuetype>
void BTree<keytype, valuetype>::dfs(BTNode<keytype, valuetype>* cur, int level)
{
	if(cur)
	{
		printf("%*c%s\n", level*4, '-', cur->toString().c_str());
		
		for(typename std::vector<BTNode<keytype, valuetype>*>::iterator it=cur->children_.begin(); it!=cur->children_.end(); it++)
		{
			dfs(*it, level+1);
		}
	}
}

template<typename keytype, typename valuetype>
void BTree<keytype, valuetype>::Print2()
{
	printf("Print2 打印B树：\n");
	if(root==NULL)
	{
		printf("empty tree\n");
		return;
	}
	
	BTNode<keytype, valuetype>* cur= root;
	int level=0;
	//std::stack<BTNode<keytype, valuetype>*> s;
	std::stack<std::pair<BTNode<keytype, valuetype>*, int> > s; // BTNode*, level
	
	s.push(std::make_pair<BTNode<keytype, valuetype>*, int>(cur, level));
	while(s.empty()==0)
	{
		std::pair<BTNode<keytype, valuetype>*, int> elem=s.top();
		s.pop();
		cur=elem.first;
		printf("%*c%s\n", elem.second, '-', cur->toString().c_str());
		
		for(typename std::vector<BTNode<keytype, valuetype>*>::iterator it=cur->children_.begin(); it!=cur->children_.end(); it++)
		{
			s.push(std::make_pair<BTNode<keytype, valuetype>*, int>(*it, elem.second+4));
		}
	}
}

template<typename keytype, typename valuetype>
bool BTree<keytype, valuetype>::findRichSibling(BTNode<keytype, valuetype> *parent, int idx, int *siblingIdx)
{
	bool exist=false;
	BTNode<keytype, valuetype>* sibling;
	if(idx>0)
	{
		sibling=parent->children_[idx-1];
		if(sibling->RecordNum()>MIN_KEY)
		{
			*siblingIdx=idx-1;
			return true;
		}
	}
	if(idx+1<parent->RecordNum())
	{
		sibling=parent->children_[idx+1];
		if(sibling->RecordNum()>MIN_KEY)
		{
			*siblingIdx=idx+1;
			return true;
		}
	}
	return false;
}

#endif
