#ifndef BTREE_H_
#define BTREE_H_

#include<list>

static const int M=5; // M叉B树
static const int MAX=M-1; // 每个节点最多M-1个记录
static const int MIN=M/2-1; // 非根节点最少math.ceil(m/2)-1个记录


template<typename keytype, typename datatype>
class BTree;

/* 
 *	BTNode
 */

template<typename keytype, typename datatype>
class BTNode{
public:
	
	struct RecordType{
		keytype key;
		datatype value;
		
		bool operator<(const RecordType& lhs, const RecordType& rhs)
		{
			return (lhs.key<rhs.key);
		}
		bool operator=(const RecordType& lhs, const RecordType& rhs) // ??
		{
			return (lhs.key==rhs.key);
		}
	};
	
private:	
	BTNode* parent_;
	int num_;	// 记录个数
	std::list<RecordType> records_; //记录列表，有序, 下标0~num_-1
	std::list<BTNode*> children_; // 子节点列表, 下标0~num_
	//bool isLeaf_;
	
public:
	BTNode();
	~BTNode();
	
	bool isLeaf(){
		return children_.empty();
	}
	
	int FindIdx();
	
	friend class BTree<keytype, datatype>;
};

template<typename keytype, typename datatype>
BTNode::BTNode()
	:parent_(NULL)
{
	
}

template<typename keytype, typename datatype>
void BTNode::addRecordWithRightChild(const struct RecordType& record, struct BTNode* rightChild)
{		
	std::list<RecordType>::iterator it=upper_bound(records_.begin(), records_.end(), record);
	int idx=it-records_.begin();// 确定新纪录record应该在节点的records_中的位置
	
	records_.insert(it, record);
	children_.insert(children_.begin()+idx+1, rightChild);
	
	rightChild->parent_=this;
}


// 分裂节点p，获得右边节点rightN 和中间记录
template<typename keytype, typename datatype>
void BTNode::split(BTNode** rightN, RecordType *mid)
{
	BTNode* rightNode;
	//BTNode *parent=p->parent_;
	
	bool isLeaf;
	if(p->children_.empty())
		isLeaf=true;
	else
		isLeaf=false;
	
	// 分裂后左边节点保留left个键，右边保留right个键，中间一个插入到父节点
	int left=(p->num_-1)/2; // p->num_等于M,  下标0~left-1
	int right=p->num_-left-1; // 下标 left+1~p->num_-1
	
	*mid=p->records_[left];  // 下标left
	
	rightNode=*rightN; // *rightN=rightNode;
	*rightN=new Node();				
	rightNode->num_=right;
	rightNode->records_.assign(p->records_.begin()+left+1, p->records_.end());
	if(!isLeaf)
		rightNode->children_.assign(p->children_.begin()+left+1, p->children_.end());// p->children_[left+1...]
	//rightNode->parent_=parent;
	
	p->num_=left;
	p->records_.resize(left);
	if(!isLeaf)
		p->children_.resize(left+1);// children_[0...left]
}

/* 
 *	BTree
 */

template<typename keytype, typename datatype>
class BTree{
public:
	BTree();
	~BTree();
	
	void Insert(const keytype& key, const valuetype& value);
	//void insert(const RecordType& record);
	
	bool Search(const keytype& key, valuetype *value);
	
	void Delete(const keytype& key);

private:
	void merge(BTNode* parent, int left, int right);

	BTNode *root;
};

template<typename keytype, typename datatype>
BTree::BTree()
{
	root=NULL;
}



// 插入一条记录，若已存在则更新value，否则插入叶节点中
template<typename keytype, typename datatype>
void BTree::Insert(const keytype& key, const valuetype& value)
{
	BTNode *p=root;
	RecordType newrecord(key, data);
	int idx;
	std::vector::iterator it;
	if(root==NULL)
	{
		root=new BTNode();
		root->num_=1;
		root->records_.push_back(newrecord);
		return;
	}
	while(p)
	{
		// lower_bound是大于等于
		// upper_bound是大于
		it=lower_bound(p->records_.begin(), p->records_.end(), newrecord);//查找记录的位置
		if(it!=p->records_.end()  &&  it->key==key)
		{
			it->value=value;
			return;
		}
		else if(it!=p->records_.end())
		{
			idx=it-p->records_.begin();
		}
		else 
		{
			idx=p->num_;// 走到最后一个儿子节点
		}		
		
		if(p->isLeaf()) 
			break; // 当p无儿子节点，退出循环
		else
			p=p->children_[idx]; // 定位到相应儿子节点
	}

	//此处，p是叶节点
	p->records_.insert(it, newrecord);
	p->num_++;

	// 从叶节点向上筛选
	while(p->num_>=M  &&  p!=root)
	{
		BTNode *parent=p->parent_;//p不为root，则parent不为NULL
		p->split(rightNode, &newrecord); // 分裂当前节点p，得到新的右半边节点和中间位置的记录
		parent->addRecordWithRightChild(newrecord, rightNode);// 临时插入一个记录和处于该记录右边的儿子指针
		
		p=parent;
	}
	if(p==root  &&  p->num_>=M) // 分裂根节点
	{
		p->split(rightNode, &newrecord);
		
		BTNode *newroot=new BTNode();
		newroot->parent=NULL;
		newroot->num_==1;
		newroot->records_.push_back(newrecord);
		newroot->children_.push_back(p);
		newroot->children_.push_back(rightNode);
		root=newroot;
	}
}

template<typename keytype, typename datatype>
bool BTree::Search(const keytype& key, valuetype *value)
{
	BTNode * cur=root;
	RecordType record(key, valuetype());
	
	//if(root==NULL)
	//	return false;
	while(cur)
	{
		std::list<RecordType>::iterator it=lower_bound(cur->records_.begin(), cur->records_.end(), record);
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

template<typename keytype, typename datatype>
void BTree::Delete(const keytype& key)
{
	BTNode *cur=root;
	struct RecordType record(key, valuetype());
	int idx;
	BTNode *child;
	std::list<RecordType>::iterator it;
	
	//寻找待删除记录所在节点cur
	//if(root==NULL)
	//	return;
	while(cur)
	{
		it=lower_bound(cur->records_.begin(), cur->records_.end(), record);
		idx=it-cur->records_.begin();
		
		if(it->key==key)
			break;
		if(cur->isLeaf())
			return;
		
		cur=cur->children_[idx];
	}
	if(cur==NULL)
		return;
	
	
	if(cur->isLeaf()==false)//若待删除记录所在节点cur不是叶子结点，寻找后继记录所在的叶子结点child
	{
		child=cur->children_[idx+1]; // 后继结点
		while(child->isLeaf()==false)
			child=child->children[0];
		it=child->records_[0];	// 用后继结点替换待删除记录
		child->records_.pop_front();
		child_->num_--;
		
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
			root=NULL;
			return;
		}
		
		idx=cur->FindIdx(); // 确定cur在其父节点的儿子节点链表中的索引
		
		
		BTNode *parent=cur->parent_;
		int siblingIdx;
		BTNode *sibling;
		if(idx>0)
		{
			siblingIdx=idx-1;
			sibling=parent->children_[siblingIdx]
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
			sibling=parent->children_[siblingIdx]
			if(sibling->num_>MIN+1)
			{
				cur->records_.insert(cur->records_.end(), sibling->records_.front());
				sibling->records_.pop_front();
				return;
			}
		}
		
		
		if(idx>0)// 与左兄弟结点合并
		{
			merge(parent, idx-1, idx)
		}
		else// 与右兄弟结点合并
		{
			merge(parent, idx, idx+1);
		}
		cur=parent;
	}
}

template<typename keytype, typename datatype>
void BTree::merge(BTNode* parent, int left, int right)
{
	BTNode* leftN=parent->children_[left];
	BTNode* rightN=parent->children_[right];
	int mid=parent->records_[left];
	
	leftN->records_.push_back(mid);
	leftN->records_.splice(leftN->records_.end(), rightN->records_);
	leftN->children_.splice(leftN->children_.end(), rightN->children_);
	
	parent->records_.erase(parent->records_.begin()+left);
	parent->children_.erase(parent->children_.begin()+left+1);
	parent->num_--;
}

#endif