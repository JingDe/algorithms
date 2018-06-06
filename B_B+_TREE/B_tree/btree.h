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

static const int M=5; // M叉B树
static const int MAX=M-1; // 每个节点最多M-1个记录
static const int MIN=(M+1)/2-1; // 非根节点最少math.ceil(m/2)-1个记录


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
		
		/*RecordType(const keytype& k, const valuetype& v)
			:key(k),value(v)
		{
			
		}*/
		RecordType()
			:key(),value()
		{
		}
		RecordType(keytype k, valuetype v)
			:key(k),value(v)
		{
			
		}
		
		RecordType& operator=(const RecordType & rhs)
		{
			key=rhs.key;
			value=rhs.value;
			return *this;
		}
	};
	
private:	
	BTNode* parent_;
	int num_;	// 记录个数
	std::vector<RecordType> records_; //记录列表，有序, 下标0~num_-1
	std::vector<BTNode*> children_; // 子节点列表, 下标0~num_
	
	
public:
	BTNode();
	~BTNode();
	
	bool isLeaf(){
		return children_.empty();
	}
	
	int FindIdx();
	void addRecordWithRightChild(const RecordType& record, BTNode* rightChild);
	void split(BTNode** rightN, RecordType *mid);
	
	std::string toString();
	
	friend class BTree<keytype, valuetype>;
};

template<typename keytype, typename valuetype>
bool operator<(const typename BTNode<keytype, valuetype>::RecordType& lhs, const typename BTNode<keytype, valuetype>::RecordType& rhs)
{
	return (lhs.key<rhs.key);
}

template<typename keytype, typename valuetype>
bool operator==(const typename BTNode<keytype, valuetype>::RecordType& lhs, const typename BTNode<keytype, valuetype>::RecordType& rhs) // ??
{
	return (lhs.key==rhs.key);
}

template<typename keytype, typename valuetype>
BTNode<keytype, valuetype>::BTNode()
	:parent_(0),num_(0),records_(),children_()
{
	
}



template<typename keytype, typename valuetype>
BTNode<keytype, valuetype>::~BTNode()
{
	//for(std::vector<BTNode*>::it=children_.begin(); it!=children_.end(); it++)
	//	delete *it;
	parent_=0;
	num_=0;
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
template<typename keytype, typename valuetype>
void BTNode<keytype, valuetype>::split(BTNode** rightN, RecordType *mid)
{
	printf("结点分裂前：%s\n", toString().c_str());
	
	BTNode* rightNode;
	//BTNode *parent=p->parent_;
		
	// 分裂后左边节点保留left个键，右边保留right个键，中间一个插入到父节点
	int left=(num_-1)/2; // p->num_等于M,  下标0~left-1
	int right=num_-left-1; // 下标 left+1~p->num_-1
	
	*mid=records_[left];  // 下标left, vector
	
	printf("分裂中：左边0~~%d, 中间key=%d, 右边%d~~%d\n", left-1, *mid, left+1, num_-1);
	
	/*typename std::list<RecordType>::iterator ite=records_.begin();//list
	for(int i=0; i<left; i++)
	{
		ite++;
	}
	*mid=*ite;*/
	

	*rightN=new BTNode();
	rightNode=*rightN;				
	rightNode->num_=right;	
	/*typename std::list<RecordType>::iterator ite2=records_.begin();
	for(int i=0; i<left+1; i++)
		ite2++;
	rightNode->records_.assign(ite2, records_.end());*/
	//rightNode->records_.assign(records_.begin()+left+1, records_.end());//p->records_[left+1, num_-1]//赋值函数？？
	for(int i=left+1; i<num_; i++)
	{
		//RecordType tempRecord(records_[i].key, records_[i].value);
		RecordType tempRecord = records_[i];
		rightNode->records_.push_back(tempRecord);
	}
	if(!isLeaf())
		rightNode->children_.assign(children_.begin()+left+1, children_.end());// p->children_[left+1...]
	//rightNode->parent_=parent;
	
	num_=left;
	records_.resize(left);
	if(!isLeaf())
		children_.resize(left+1);// children_[0...left]
	
	printf("结点分裂后：%s\n", toString().c_str());
	printf("新结点：%s\n", rightNode->toString().c_str());
}

template<typename keytype, typename valuetype>
int BTNode<keytype, valuetype>::FindIdx()
{
	if(parent_==0)
		return -1;
	
	//for(typename std::list<BTNode*>::iterator it=parent_->children_.begin();
	for(typename std::vector<BTNode*>::iterator it=parent_->children_.begin();  
		it!=parent_->children_.end(); it++)
	{
		if(*it==this)
			return it-parent_->children_.begin();
	}
}


template<typename keytype, typename valuetype>
std::string BTNode<keytype, valuetype>::toString()
{
	std::string res;
	std::ostringstream oss;
	oss<<"<"<<num_<<" |";
	//for(typename std::list<RecordType>::iterator it=records_.begin(); it!=records_.end(); it++)
	for(typename std::vector<RecordType>::iterator it=records_.begin(); it!=records_.end(); it++)
		oss<<" "<<it->key;
	oss<<">";
	res=oss.str();
	return res;
}








/* 
 *	BTree
 */

template<typename keytype, typename valuetype>
class BTree{
public:
	BTree();
	~BTree();
	
	void Insert(const keytype& key, const valuetype& value);
	//void insert(const RecordType& record);
	
	bool Search(const keytype& key, valuetype *value);
	
	void Delete(const keytype& key);
	
	void Print();

private:
	void merge(BTNode<keytype, valuetype> * parent, int left, int right);

	void dfs(BTNode<keytype, valuetype>* cur, int level);

	BTNode<keytype, valuetype> *root;
};

template<typename keytype, typename valuetype>
BTree<keytype, valuetype>::BTree()
{
	root=0;
}

template<typename keytype, typename valuetype>
BTree<keytype, valuetype>::~BTree()
{
	//???z 
	std::stack<BTNode<keytype, valuetype>*> S;
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
	}
}


// 插入一条记录，若已存在则更新value，否则插入叶节点中
template<typename keytype, typename valuetype>
void BTree<keytype, valuetype>::Insert(const keytype& key, const valuetype& value)
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
		root->num_=1;
		root->records_.push_back(newrecord);
		root->children_.clear();
		return;
	}
	while(p)
	{
		//idx既是第一个大于等于新纪录的记录索引，也是可能的下一个考虑的儿子结点的索引
		
		// lower_bound是大于等于，upper_bound是大于
		//it=lower_bound(p->records_.begin(), p->records_.end(), newrecord);//查找记录的位置,vector
		for(it=p->records_.begin(); it!=p->records_.end(); it++)//list
		{
			if(it->key>=newrecord.key)
				break;
		}
		
		if(it!=p->records_.end()  &&  it->key==key)
		{
			printf("更新节点: %s\n", p->toString().c_str());
			it->value=value;
			printf("更新后节点: %s\n", p->toString().c_str());
			return;
		}
		
		if(it!=p->records_.end())
		{
			idx=it - p->records_.begin();//vector迭代器
			//idx=std::distance(it, p->records_.begin());//list迭代器
			printf("middle child: %d\n", idx);
		}
		else 
		{			
			idx=p->num_;// 走到最后一个儿子节点
			printf("last child: %d, %d\n", p->num_, idx);
		}		
		
		if(p->isLeaf()) 
			break; // 当p无儿子节点，退出循环
		p=p->children_[idx]; // 定位到相应儿子节点
	}

	printf("插入叶节点: %s\n", p->toString().c_str());
	//此处，p是叶节点
	
	p->num_++;
	printf("p->records_.size()=%d, idx=%d\n", p->records_.size(), idx);
	p->records_.insert(it, newrecord); 
	assert(p->records_.size()==p->num_);
	printf("插入之后临时: %s\n", p->toString().c_str());

	// 从叶节点向上筛选
	while(p->num_>=M  &&  p!=root)
	{
		printf("分裂节点: %s\n", p->toString().c_str());
		
		BTNode<keytype, valuetype> *parent=p->parent_;//p不为root，则parent不为0
		p->split(&rightNode, &newrecord); // 分裂当前节点p，得到新的右半边节点和中间位置的记录
		parent->addRecordWithRightChild(newrecord, rightNode);// 临时插入一个记录和处于该记录右边的儿子指针
		
		p=parent;
	}
	if(p==root  &&  p->num_>=M) // 分裂根节点
	{
		printf("分裂根节点: %s\n", p->toString().c_str());
		p->split(&rightNode, &newrecord);
		
		BTNode<keytype, valuetype> *newroot=new BTNode<keytype, valuetype>();
		newroot->parent_=0;
		newroot->num_=1;
		newroot->records_.push_back(newrecord);
		newroot->children_.push_back(p);
		newroot->children_.push_back(rightNode);
		root=newroot;
	}
	
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

template<typename keytype, typename valuetype>
void BTree<keytype, valuetype>::Delete(const keytype& key)
{
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
		return;
	
	
	if(cur->isLeaf()==false)//若待删除记录所在节点cur不是叶子结点，寻找后继记录所在的叶子结点child
	{
		child=cur->children_[idx+1]; // 后继结点
		while(child->isLeaf()==false)
			child=child->children[0];
		it=child->records_[0];	// 用后继结点替换待删除记录
		child->records_.pop_front();
		child->num_--;
		
		cur=child;
	}
	else
	{
		cur->erase(it);
		cur->num_--;
	}
	
	while(true)
	{
		if(cur->num_>=MIN)
			return;
		
		if(cur==root &&  cur->num_>=1)
			return;
		else if(cur==root)
		{
			delete root;
			root=0;
			return;
		}
		
		idx=cur->FindIdx(); // 确定cur在其父节点的儿子节点链表中的索引
		
		
		BTNode<keytype, valuetype> *parent=cur->parent_;
		int siblingIdx;
		BTNode<keytype, valuetype> *sibling;
		if(idx>0)
		{
			siblingIdx=idx-1;
			sibling=parent->children_[siblingIdx]; 
			if(sibling->num_>MIN+1)
			{
				cur->records_.insert(cur->records_.begin(), sibling->records_.back());
				sibling->records_.pop_back();
				return;
			}
		}
		else
		{
			siblingIdx=idx+1;
			sibling=parent->children_[siblingIdx];
			if(sibling->num_>MIN+1)
			{
				cur->records_.insert(cur->records_.end(), sibling->records_.front());
				sibling->records_.pop_front();
				return;
			}
		}
		
		
		if(idx>0)// 与左兄弟结点合并
		{
			merge(parent, idx-1, idx);
		}
		else// 与右兄弟结点合并
		{
			merge(parent, idx, idx+1);
		}
		cur=parent;
	}
}

template<typename keytype, typename valuetype>
void BTree<keytype, valuetype>::merge(BTNode<keytype, valuetype>* parent, int left, int right)
{
	BTNode<keytype, valuetype>* leftN=parent->children_[left];
	BTNode<keytype, valuetype>* rightN=parent->children_[right];
	int mid=parent->records_[left];
	
	leftN->records_.push_back(mid);
	//leftN->records_.splice(leftN->records_.end(), rightN->records_);// list
	for(typename std::vector<typename BTNode<keytype, valuetype>::RecordType>::iterator it=rightN->records_.begin(); it!=rightN->records_.end(); it++)//vector
		leftN->records_.push_back(*it);
	//leftN->children_.splice(leftN->children_.end(), rightN->children_);// list
	for(typename std::vector<BTNode<keytype, valuetype>*>::iterator it=rightN->children_.begin(); it!=rightN->children_.end(); it++)//vector
		leftN->children_.push_back(*it);
	
	parent->records_.erase(parent->records_.begin()+left);//list
	parent->children_.erase(parent->children_.begin()+left+1);//vector
	parent->num_--;
}


template<typename keytype, typename valuetype>
void BTree<keytype, valuetype>::Print()
{
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

#endif
