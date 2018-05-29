#ifndef BTREE_H_
#define BTREE_H_

#include<vector>

static const int M=5;// 每个节点最多M-1个关键字
static const int MIN=(m+1)/2-1; // 非根节点最少math.ceil(m/2)-1个关键字

template<typename keytype, typename datatype>
class BTree;

template<typename keytype, typename datatype>
class BTNode{
public:
	struct RecordType{
		keytype key;
		datatype value;
	};
	
private:	
	BTNode* parent_;
	int num_;	// 记录个数
	std::vector<RecordType> records_;
	std::vector<BTNode*> children_;
	bool isLeaf_;
	
public:
	BTNode();
	~BTNode();
	
	friend class BTree<keytype, datatype>;
};

template<typename keytype, typename datatype>
BTNode::BTNode()
{
	
}


template<typename keytype, typename datatype>
class BTree{
public:
	BTree();
	~BTree();
	
	void insert(const keytype& key, const valuetype& value);
	bool search(const keytype& key, valuetype *value);

private:
	BTNode *root;
	
	
};

template<typename keytype, typename datatype>
BTree::BTree()
{
	root=NULL;
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
		it=lower_bound(p->records_.begin(), p->records_.end(), key);
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
		
		if(p->isLeaf_)
			break;
		else
			p=p->children_[idx]; // 定位到相应儿子节点
	}

	
	//p->insertRecord(record, idx); // 向p节点idx位置插入记录id
	p->records_.insert(it, newrecord);
	p->num_++;
	
	while(p->num_>=M  &&  p!=root)
	{
		BTNode *parent=p->parent_;//p不为root，则parent不为NULL
		newrecord=split(p, rightNode);
		parent->insertRecord(newrecord, rightNode);// 临时插入一个记录和一个儿子指针，待实现
		
		p=parent;
	}
	if(p==root  &&  p->num_>=M)
	{
		newrecord=split(p, rightNode);
		
		BTNode *newroot=new BTNode();
		newroot->num_==1;
		newroot->records_.push_back(newrecord);
		newroot->children_.push_back(p);
		newroot->children_.push_back(rightNode);
	}
}

// 分裂节点p，获得右边节点rightN，中间记录mid返回
RecordType split(BTNode* p, BTNode** rightN)
{
	BTNode* rightNode;
		
	BTNode *parent=p->parent_;
	RecordType mid=p->records_[left];
	// 分裂后左边节点保留left个键，右边保留right个键，中间一个插入到父节点
	int left=(M-1)/2;
	int right=M-left-1;			
	
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
	
	return mid;
}

#endif