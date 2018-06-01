#ifndef BTREE_H_
#define BTREE_H_

#include<vector>

static const int M=5;
static const int MAX=M-1; // 每个节点最多M-1个记录
static const int MIN=M/2-1; // 非根节点最少math.ceil(m/2)-1个记录

template<typename keytype, typename datatype>
class BTree;

template<typename keytype, typename datatype>
class BTNode{
public:
	// 记录类型
	struct RecordType{
		keytype key;
		datatype value;
	};
	
private:	
	BTNode* parent_;
	int num_;	// 记录个数
	std::vector<RecordType> records_; //记录列表，有序
	std::vector<BTNode*> children_; // 子节点列表
	bool isLeaf_;
	
public:
	BTNode();
	~BTNode();
	
	friend class BTree<keytype, datatype>;
};

template<typename keytype, typename datatype>
BTNode::BTNode()
	:parent_(NULL)
{
	
}

template<typename keytype, typename datatype>
void BTNode::addRecordWithRightChild(struct RecordType& record, struct BTNode* rightChild)
{
	
}

template<typename keytype, typename datatype>
class BTree{
public:
	BTree();
	~BTree();
	
	void insert(const keytype& key, const valuetype& value);
	void insert(const RecordType& record);
	
	bool search(const keytype& key, valuetype *value);

private:
	BTNode *root;
	
	bool comparator(const RecordType& lhs, const RecordType& rhs);
};

template<typename keytype, typename datatype>
BTree::BTree()
{
	root=NULL;
}

template<typename keytype, typename datatype>
bool BTree::comparator(const RecordType& lhs, const RecordType& rhs)
{
		return (lhs.key<rhs.key);
}

// 插入一条记录，若已存在则更新value，否则插入叶节点中
template<typename keytype, typename datatype>
void BTree::insert(const keytype& key, const valuetype& value)
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
		root->isLeaf_=true;	// ??
		return;
	}
	while(p)
	{
		// lower_bound是大于等于
		// higher_bound是大于
		it=lower_bound(p->records_.begin(), p->records_.end(), comparator);//查找记录的位置
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
		
		if(p->isLeaf_) // if(p->children_.empty())
			break; // 当p无儿子节点，退出循环
		else
			p=p->children_[idx]; // 定位到相应儿子节点
	}

	//此处，p没有儿子节点
	p->records_.insert(it, newrecord);
	p->num_++;
	
	while(p->num_>=M  &&  p!=root)
	{
		BTNode *parent=p->parent_;//p不为root，则parent不为NULL
		split(p, rightNode, &newrecord); // 分裂当前节点p，得到新的右半边节点和中间位置的记录
		parent->addRecordWithRightChild(newrecord, rightNode);// 临时插入一个记录和处于该记录右边的儿子指针
		
		p=parent;
	}
	if(p==root  &&  p->num_>=M) // 分裂根节点
	{
		split(p, rightNode, &newrecord);
		
		BTNode *newroot=new BTNode();
		newroot->parent=NULL;
		newroot->num_==1;
		newroot->records_.push_back(newrecord);
		newroot->children_.push_back(p);
		newroot->children_.push_back(rightNode);
		root=newroot;
	}
}

// 分裂节点p，获得右边节点rightN 和中间记录
void split(BTNode* p, BTNode** rightN, RecordType *mid)
{
	BTNode* rightNode;
		
	BTNode *parent=p->parent_;
	
	// 分裂后左边节点保留left个键，右边保留right个键，中间一个插入到父节点
	int left=(M-1)/2;
	int right=M-left-1;	
	*mid=p->records_[left];
	
	*rightN=new Node();			
	rightNode=*rightN;
	rightNode->num_=right;
	rightNode->records_.assign(p->records_.begin()+left+1, p->records_.end());
				
	p->records_.resize(left);
	p->num_=left;
	
	rightNode->parent_=parent;
	rightNode->isLeaf_=p->isLeaf_;
	if(p->isLeaf_==false)
	{
		rightNode->children_.assign(p->children_.begin()+left+1, p->children_.end());
		p->children_.resize(left+1);
	}
}

#endif