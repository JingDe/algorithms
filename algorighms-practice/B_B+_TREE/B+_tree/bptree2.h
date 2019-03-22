#ifndef BPLUS_TREE_H_
#define BPLUS_TREE_H_

#include<vector>
#include<string>
#include<sstream>

// B+树实现
// 根结点：或者是叶节点，或者是儿子数在2和M之间
// 除根以外的非叶节点：⌈M/2⌉~M个子结点，和少于1个的键。(键i代表子树i+1中的最小的键, 键i代表子树i中的最大的键)
// 叶节点有ceil(L/2)~L个数据项

static const int M_DEFAULT=228;
static const int L_DEFAULT=32;

template<typename keytype, typename valuetype>
class BPlusTree;


template<typename keytype, typename valuetype>
class BPTNode{
public:
	BPTNode();
	~BPTNode();
	
	void InsertRecord(const keytype& key, const valuetype& value);
	void PushRecord(const keytype& key, const valuetype& value);
	std::string toString();
	
private:
	bool isLeaf_;
	bool isRoot_;
	BPTNode *parent_; // 父节点
	std::vector<keytype> keys_; // 索引节点的索引key，叶节点的key
		// 索引节点的关键字的个数，当不是根节点时，在ceil(M/2)-1和M-1之间。当是根节点时，在1和M-1之间
		// 叶节点的关键字个数，ceil(L/2)和L之间
	
	std::vector<BPTNode*> children_; // 只对索引节点有效，索引节点的子树节点
		// 索引节点的子节点个数，当不是根节点时，在ceil(M/2)和M之间。当是根节点时，在1和M之间

	
	std::vector<valuetype> values_; // 只对叶节点有效，叶节点key对应的value
		// 叶节点的value和叶节点的keys_一一对应
	
	BPTNode *next_; // 只对叶节点有效，下一个叶节点
	
	// assert(
	// 		(isLeaf_==true  &&  keys_.size()==values_.size()  &&  keys_.size()!=0  &&  children_.size()==0)
	// || 	(isLeaf_==false  &&  values_.size()==0  &&  keys_.size()!=0  &&  children_.size()!=0)
	
	// || 	(isRoot_==true  &&  parent_==0)
	// || 	(isRoot_==true  && isLeaf_==true  &&  parent_==0  &&  children_.size()==0  &&  keys_.size()==values_.size()  &&  keys_.size()!=0)
	// )
	
	friend class BPlusTree<keytype, valuetype>;
};

template<typename keytype, typename valuetype>
BPTNode<keytype, valuetype>::BPTNode():isLeaf_(false),isRoot_(false),parent_(0),next_(0)
{}


template<typename keytype, typename valuetype>
void BPTNode<keytype, valuetype>::InsertRecord(const keytype& key, const valuetype& value)
{
	
}

template<typename keytype, typename valuetype>
void BPTNode<keytype, valuetype>::PushRecord(const keytype& key, const valuetype& value)
{
	keys_.push_back(key);
	values_.push_back(value);
}


template<typename keytype, typename valuetype>
std::string BPTNode<keytype, valuetype>::toString()
{
	std::ostringstream oss;
	std::string result;
	if(isLeaf_)
	{
		typename std::vector<keytype>::iterator it=keys_.begin();
		while(it!=keys_.end())
		{
			oss<<"("<<*it<<", "<<values_[it-keys_.begin()]<<")";
			++it;
		}
	}
	else
	{
		typename std::vector<keytype>::iterator it=keys_.begin();
		while(it!=keys_.end())
		{
			oss<<"("<<*it<<")";
			++it;
		}
	}
	result=oss.str();
	return result;
}

/*
BPlusTree
*/
template<typename keytype, typename valuetype>
class BPlusTree{
public:
	BPlusTree();
	BPlusTree(int m, int l);
	~BPlusTree();
	
	bool Search(const keytype& key, valuetype *value);
	bool Insert(const keytype& key, const valuetype& value);
	bool Delete(const keytype& key);
	void Print();
	
private:

	bool insert_empty_tree(const keytype& key, const valuetype& value);
	void dfs(BPTNode<keytype, valuetype>* cur, int level);

	BPTNode<keytype, valuetype>* root_; // 根节点
	BPTNode<keytype, valuetype>* head_; // 叶节点链表表头节点
		
	const int M; // M叉B树，所有节点包含x个记录和x+1个子树指针，每个记录包含一个关键字和一个指向对应数据的指针
	const int MAX_KEY; // 每个节点最多M-1个关键字，最多M个子树

	const int MIN_KEY; // 非根节点最少math.ceil(M/2)-1个关键字
	const int MIN_KEY_ROOT; // 根节点最少1个关键字
	
	const int L; // 叶节点记录个数ceil(L/2)和L之间
	const int MAX_RECORD;
	const int MIN_RECORD;
};

template<typename keytype, typename valuetype>
BPlusTree<keytype, valuetype>::BPlusTree():root_(0),head_(0),
	M(M_DEFAULT),MAX_KEY(M-1),MIN_KEY((M+1)/2-1),MIN_KEY_ROOT(1),
	L(L_DEFAULT),MAX_RECORD(L),MIN_RECORD((L/2))
{
	
}

template<typename keytype, typename valuetype>
BPlusTree<keytype, valuetype>::BPlusTree(int m, int l):root_(0),head_(0),
	M(m),MAX_KEY(M-1),MIN_KEY((M+1)/2-1),MIN_KEY_ROOT(1),
	L(l),MAX_RECORD(L),MIN_RECORD((L/2))
{
	
}

template<typename keytype, typename valuetype>
BPlusTree<keytype, valuetype>::~BPlusTree()
{
	
}

template<typename keytype, typename valuetype>
bool BPlusTree<keytype, valuetype>::Search(const keytype& key, valuetype *value)
{
	if(root_==0)
		return false;
	BPTNode<keytype, valuetype> * cur=root_;
	typename BPTNode<keytype, valuetype>::RecordType record(key, valuetype());
	
	typename std::vector<typename BPTNode<keytype, valuetype>::RecordType>::iterator it;
	while(cur)
	{
		//typename std::vector<typename BPTNode<keytype, valuetype>::RecordType>::iterator it=lower_bound(cur->records_.begin(), cur->records_.end(), record);
		
		for(it=cur->records_.begin(); it!=cur->records_.end(); it++)
		{
			if(it->key>=record.key)
				break;
		}
		if(cur->isLeaf_)
		{
			break;
		}
		
		int idx=it-cur->records_.begin();
		cur=cur->children_[idx];
	}
	if(it!=cur->records_.end()  &&  it->key==record.key)
	{
		*value=cur->values_[it-cur->records_.begin()];
		return true;
	}
	return false;
}

template<typename keytype, typename valuetype>
bool BPlusTree<keytype, valuetype>::Insert(const keytype& key, const valuetype& value)
{
	if(root_==NULL)
	{
		insert_empty_tree(key, value);
	}
}

template<typename keytype, typename valuetype>
bool BPlusTree<keytype, valuetype>::insert_empty_tree(const keytype& key, const valuetype& value)
{
	assert(root_==NULL  &&  head_==NULL);
	root_=new BPTNode<keytype, valuetype>();
	head_=root_;
	root_->PushRecord(key, value);
	
}


template<typename keytype, typename valuetype>
void BPlusTree<keytype, valuetype>::Print()
{
	printf("打印B+树：\n");
	BPTNode<keytype, valuetype>* cur= root_;
	int level=0;
	dfs(cur, level);
}

template<typename keytype, typename valuetype>
void BPlusTree<keytype, valuetype>::dfs(BPTNode<keytype, valuetype>* cur, int level)
{
	if(cur)
	{
		printf("%*c%s\n", level*4, '-', cur->toString().c_str());
		
		for(typename std::vector<BPTNode<keytype, valuetype>*>::iterator it=cur->children_.begin(); it!=cur->children_.end(); it++)
		{
			dfs(*it, level+1);
		}
	}
}

#endif