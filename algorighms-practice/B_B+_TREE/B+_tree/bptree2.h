#ifndef BPLUS_TREE_H_
#define BPLUS_TREE_H_

#include<vector>
#include<deque>
#include<string>
#include<sstream>
#include<cassert>
#include<algorithm>

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
	
	void LeafInsertRecord(int idx, const keytype& key, const valuetype& value);
	void LeafPushRecord(const keytype& key, const valuetype& value); // Insert at end()
	
	void IndexInsert(const keytype& key, BPTNode* left, BPTNode* right);
	
	void LeafDeleteRecord(int idx);
	
	void LeafSplit(BPTNode<keytype, valuetype>** rightSibling);
	void IndexSplit(BPTNode<keytype, valuetype> **rightSibling, keytype *middleKey);
	
	int FindSelfIdx();
	
	void LeafBorrowLeft(int selfIdx);
	void LeafBorrowRight(int selfIdx);
	
	void IndexBorrowLeft(int selfIdx);
	void IndexBorrowRight(int selfIdx);
	
	void LeafMergeLeft(int selfIdx);
	void LeafMergeRight(int selfIdx);
	
	void IndexMergeLeft(int selfIdx);
	void IndexMergeRight(int selfIdx);
	
	std::string toString();
	
	bool isLeaf(){
		return isLeaf_;
	}
	bool isRoot(){
		return isRoot_;
	}
	
	void node_assert()
	{
		assert(
	(isLeaf_==true  &&  keys_.size()==values_.size()  &&  keys_.size()!=0  &&  children_.size()==0)
|| 	(isLeaf_==false  &&  values_.size()==0  &&  keys_.size()!=0  &&  keys_.size()+1==children_.size())	

|| 	(isRoot_==true  &&  parent_==0)
|| 	(isRoot_==true  &&  isLeaf_==true  &&  children_.size()==0  &&  keys_.size()==values_.size()  &&  keys_.size()!=0)
||  (isRoot_==true  &&  isLeaf_==false  &&  children_.size()!=0  &&  values_.size()==0  &&  keys_.size()!=0  &&  keys_.size()+1==children_.size())

		);
	}
	
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
	
	friend class BPlusTree<keytype, valuetype>;
};

template<typename keytype, typename valuetype>
BPTNode<keytype, valuetype>::BPTNode():isLeaf_(false),isRoot_(false),parent_(0),next_(0)
{}

template<typename keytype, typename valuetype>
BPTNode<keytype, valuetype>::~BPTNode()
{
	keys_.clear();
	values_.clear();
	children_.clear();
}

template<typename keytype, typename valuetype>
void BPTNode<keytype, valuetype>::LeafPushRecord(const keytype& key, const valuetype& value)
{
	keys_.push_back(key);
	values_.push_back(value);
}

template<typename keytype, typename valuetype>
void BPTNode<keytype, valuetype>::LeafInsertRecord(int idx, const keytype& key, const valuetype& value)
{
	keys_.insert(keys_.begin()+idx, key);
	values_.insert(values_.begin()+idx, value);
}

template<typename keytype, typename valuetype>
void BPTNode<keytype, valuetype>::IndexInsert(const keytype& key, BPTNode* left, BPTNode* right)
{
	typename std::vector<keytype>::iterator it=std::lower_bound(keys_.begin(), keys_.end(), key);
	int idx=it-keys_.begin();
	keys_.insert(it, key);
	children_.insert(children_.begin()+idx+1, right);
}

template<typename keytype, typename valuetype>
void BPTNode<keytype, valuetype>::LeafDeleteRecord(int idx)
{
	keys_.erase(keys_.begin()+idx);
	values_.erase(values_.begin()+idx);
}

// 计算机整数相除，只保留整数位
// 6 3+3
// 5 2+3
// 叶节点分裂
template<typename keytype, typename valuetype>
void BPTNode<keytype, valuetype>::LeafSplit(BPTNode<keytype, valuetype>** rightSibling)
{
	printf("before LeafSplit %s\n", toString().c_str());
	int left=(keys_.size())/2; // 0-left-1  与 left~keys_.size()-1
	(*rightSibling)->parent_=parent_;
	(*rightSibling)->isLeaf_=isLeaf_;
	(*rightSibling)->isRoot_=isRoot_;
	(*rightSibling)->keys_.assign(keys_.begin()+left, keys_.end());
	(*rightSibling)->values_.assign(values_.begin()+left, values_.end());
	(*rightSibling)->children_.clear();
	
	keys_.resize(left);
	values_.resize(left);
	
	(*rightSibling)->next_=next_;
	next_=*rightSibling;
	
	printf("LeafSplit %s, %s\n", toString().c_str(), (*rightSibling)->toString().c_str());
}

// 6 2+1+3 3+3
// 5 2+1+2 3+2
// 索引节点分裂
template<typename keytype, typename valuetype>
void BPTNode<keytype, valuetype>::IndexSplit(BPTNode<keytype, valuetype>** rightSibling, keytype *middleKey)
{
	assert(values_.size()==0);
	printf("将分裂索引节点 %s, keys.size=%d, values.size=%d, children.size=%d\n", toString().c_str(), keys_.size(), values_.size(), children_.size());
	int left=(keys_.size()+1)/2-1; // 0-left-1  与 left  与 left+1~keys_.size()-1
	(*rightSibling)->parent_=parent_;
	(*rightSibling)->isLeaf_=isLeaf_;
	(*rightSibling)->isRoot_=isRoot_;
	(*rightSibling)->keys_.assign(keys_.begin()+left+1, keys_.end());
	(*rightSibling)->children_.assign(children_.begin()+left+1, children_.end());
	
	keys_.resize(left);
	children_.resize(left+1);
	
	*middleKey=keys_[left];
	
	printf("索引节点分裂得到 %s, %s, %d\n", toString().c_str(), (*rightSibling)->toString().c_str(), *middleKey);
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

template<typename keytype, typename valuetype>
int BPTNode<keytype, valuetype>::FindSelfIdx()
{
	typename std::vector<BPTNode*>::iterator it=std::find(parent_->children_.begin(), parent_->children_.end(), this);
	assert(it!=parent_->children_.end());
	return it-parent_->children_.begin();
}

template<typename keytype, typename valuetype>
void BPTNode<keytype, valuetype>::LeafBorrowLeft(int selfIdx)
{
	BPTNode<keytype, valuetype> *leftSibling=parent_->children_[selfIdx-1];
	keys_.insert(keys_.begin(), leftSibling->keys_.back());
	values_.insert(keys_.begin(), leftSibling->values_.back());
	
	leftSibling->keys_.pop_back();
	leftSibling->values_.pop_back();
	
	parent_->keys_[selfIdx-1]=keys_.front();
}

template<typename keytype, typename valuetype>
void BPTNode<keytype, valuetype>::LeafBorrowRight(int selfIdx)
{
	BPTNode<keytype, valuetype> *rightSibling=parent_->children_[selfIdx-1];
	keys_.push_back(rightSibling->keys_.front());
	values_.push_back(rightSibling->values_.front());
	
	rightSibling->keys_.erase(rightSibling->keys_.begin());
	rightSibling->values_.erase(rightSibling->keys_.begin());
	
	parent_->keys_[selfIdx]=rightSibling->keys_.front();
}

template<typename keytype, typename valuetype>
void BPTNode<keytype, valuetype>::IndexBorrowLeft(int selfIdx)
{
	keys_.insert(keys_.begin(), parent_->keys_[selfIdx-1]);
	BPTNode<keytype, valuetype> *leftSibling=parent_->children_[selfIdx-1];
	parent_->keys_[selfIdx-1]=leftSibling->keys_.back();
	leftSibling->keys_.pop_back();
}

template<typename keytype, typename valuetype>
void BPTNode<keytype, valuetype>::IndexBorrowRight(int selfIdx)
{
	keys_.insert(keys_.begin(), parent_->keys_[selfIdx]);
	BPTNode<keytype, valuetype> *rightSibling=parent_->children_[selfIdx-1];
	parent_->keys_[selfIdx]=rightSibling->keys_.front();
	rightSibling->keys_.erase(rightSibling->keys_.begin());
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
	void PrintRecord();
	
private:
	bool Search_for_Insert(const keytype& key, BPTNode<keytype, valuetype>** leaf, int *idx);
	bool Search_for_Delete(const keytype& key, BPTNode<keytype, valuetype>** leaf, int *idx);
	bool insert_empty_tree(const keytype& key, const valuetype& value);
	void dfs(BPTNode<keytype, valuetype>* cur, int level);
	void free1();
	
	bool borrowRichSiblingLeaf(BPTNode<keytype, valuetype> *node);
	bool borrowRichSiblingIndex(BPTNode<keytype, valuetype> *node);
	
	bool mergeLeaf(BPTNode<keytype, valuetype> *node);
	bool mergeIndex(BPTNode<keytype, valuetype> *node);

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
	free1();
}

template<typename keytype, typename valuetype>
void BPlusTree<keytype, valuetype>::free1()
{
	std::deque<BPTNode<keytype, valuetype>*> Q;
	BPTNode<keytype, valuetype>* cur=0;
	if(root_==0)
		return;
	Q.push_back(root_);
	while(!Q.empty())
	{
		cur=Q.front();
		Q.pop_front();
		for(typename std::vector<BPTNode<keytype, valuetype>*>::iterator it=cur->children_.begin(); 
			it!=cur->children_.end(); it++)
		{
			BPTNode<keytype, valuetype>* child=*it;
			Q.push_back(child);
		}
		cur->children_.clear();
		delete cur;
	}
}

// 左子树关键字<当前关键字<=右子树关键字
template<typename keytype, typename valuetype>
bool BPlusTree<keytype, valuetype>::Search(const keytype& key, valuetype *value)
{
	if(root_==0)
		return false;
	BPTNode<keytype, valuetype> * cur=root_;
	typename std::vector<keytype>::iterator it;
	
	while(cur)
	{
		// TODO	
		for(it=cur->keys_.begin(); it!=cur->keys_.end(); it++)
		{
			if(*it>key) 
				break;
		}
		if(cur->isLeaf_)
		{
			break;
		}
		
		int idx=it-cur->keys_.begin();
		cur=cur->children_[idx];
	}
	if(cur!=NULL  &&  cur->isLeaf_  &&  it!=cur->keys_.end()  &&  *it==key)
	{
		*value=cur->values_[it-cur->keys_.begin()];
		return true;
	}
	return false;
}

template<typename keytype, typename valuetype>
bool BPlusTree<keytype, valuetype>::Insert(const keytype& key, const valuetype& value)
{
	printf("Call Insert %d %d\n", key, value);
	if(root_==NULL)
	{
		printf("插入空树\n");
		insert_empty_tree(key, value);
		return true;
	}
	
	BPTNode<keytype, valuetype>* leaf=NULL;
	int idx=-1;
	bool exists=Search_for_Insert(key, &leaf, &idx);
	if(exists)
	{
		printf("插入，更新value\n");
		leaf->values_[idx]=value;
		return true;
	}
	
	printf("插入叶节点,%s\n", leaf->toString().c_str());
	leaf->LeafInsertRecord(idx, key, value);
	
	if(leaf->keys_.size()<=L)
		return true;
	printf("插入，叶节点数%d, 超过%d\n", leaf->keys_.size(), L);
	BPTNode<keytype, valuetype>* rightSibling=new BPTNode<keytype, valuetype>();
	leaf->LeafSplit(&rightSibling);
	
	if(leaf->isRoot_) // root_==leaf  head_==leaf
	{
		BPTNode<keytype, valuetype>* newRoot=new BPTNode<keytype, valuetype>();
		newRoot->isRoot_=true;
		newRoot->keys_.push_back(rightSibling->keys_[0]);
		newRoot->children_.push_back(leaf);
		newRoot->children_.push_back(rightSibling);
		root_=newRoot;
		
		leaf->parent_=root_; rightSibling->parent_=root_;
		leaf->isRoot_=false; rightSibling->isRoot_=false;
		return true;
	}
	
	assert(leaf->parent_->isLeaf_==false);
	leaf->parent_->IndexInsert(rightSibling->keys_[0], leaf, rightSibling);
	
	BPTNode<keytype, valuetype>* cur=leaf->parent_;
	while(true)
	{
		if(cur->keys_.size()<M)
			return true;
		
		BPTNode<keytype, valuetype>* rightSibling=new BPTNode<keytype, valuetype>();
		keytype middleKey;
		cur->IndexSplit(&rightSibling, &middleKey);
		printf("cur->isRoot=%d\n", cur->isRoot_);

		//if(cur->isRoot_)
		if(cur==root_)
		{
			printf("分裂到根节点, %s\n", cur->toString().c_str());
			BPTNode<keytype, valuetype>* newRoot=new BPTNode<keytype, valuetype>();
			newRoot->isRoot_=true;
			newRoot->keys_.push_back(middleKey);
			newRoot->children_.push_back(cur);
			newRoot->children_.push_back(rightSibling);
			root_=newRoot;
			
			cur->parent_=root_; rightSibling->parent_=root_;
			cur->isRoot_=false; rightSibling->isRoot_=false;
			return true;
		}
		printf("将分裂索引节点(key %d, rightSibling %s), 插入到父节点%s\n", middleKey, rightSibling->toString().c_str(), cur->parent_->toString().c_str());
		cur->parent_->IndexInsert(middleKey, cur, rightSibling);
		cur=cur->parent_;
	}
	return false;
}

// 在B+树中查询key关键字，直到叶子节点通过leaf返回，查找成功返回true，idx返回key的位置
// 查找失败，返回false，idx返回key应该插入的位置
template<typename keytype, typename valuetype>
bool BPlusTree<keytype, valuetype>::Search_for_Insert(const keytype& key, BPTNode<keytype, valuetype>** leaf, int *idx)
{
	if(root_==0)
		return false;
	BPTNode<keytype, valuetype> * cur=root_;
	typename std::vector<keytype>::iterator it;
	
	while(cur)
	{
		for(it=cur->keys_.begin(); it!=cur->keys_.end(); it++)
		{
			if(*it>key) 
				break;
		}
		if(cur->isLeaf_)
		{
			break;
		}
		
		int idx=it-cur->keys_.begin();
		cur=cur->children_[idx];
	}
	assert(cur!=NULL  &&  cur->isLeaf_);
	
	*leaf=cur;
	*idx=it-cur->keys_.begin();
	if(cur!=NULL  &&  cur->isLeaf_  &&  it!=cur->keys_.end()  &&  *it==key)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<typename keytype, typename valuetype>
bool BPlusTree<keytype, valuetype>::insert_empty_tree(const keytype& key, const valuetype& value)
{
	assert(root_==NULL  &&  head_==NULL);
	root_=new BPTNode<keytype, valuetype>();
	head_=root_;
	
	root_->isRoot_=true;
	root_->isLeaf_=true;
	root_->parent_=NULL;
	root_->LeafPushRecord(key, value);
	root_->children_.clear();
	root_->next_=NULL;
	return true;
}

template<typename keytype, typename valuetype>
bool BPlusTree<keytype, valuetype>::Delete(const keytype& key)
{
	printf("删除 %d\n", key);
	if(root_==NULL)
		return false;
	BPTNode<keytype, valuetype> *leaf;
	int idx;
	int exist=Search_for_Delete(key, &leaf, &idx);
	if(!exist)
		return true;
	
	printf("从叶节点%s中删除第%d个key\n", leaf->toString().c_str(), idx);
	leaf->LeafDeleteRecord(idx);
	if(leaf==root_)
	{
		if(leaf->keys_.size()==0)
		{
			delete leaf;// TODO
			root_=head_=NULL;
		}
		return true;
	}
	
	if(leaf->keys_.size()>=MIN_RECORD)
		return true;
	
	if(borrowRichSiblingLeaf(leaf))
	{
		return true;
	}
	
	mergeLeaf(leaf);
	BPTNode<keytype, valuetype> *cur=leaf->parent_;
	while(true)
	{
		if(cur->isRoot_  &&  cur->keys_.size()>0)
			return true;
		if(cur->isRoot_  &&  cur->keys_.size()==0)
		{
			printf("删除根节点%s\n", root_->toString().c_str());
			root_=root_->children_[0];
			delete cur;
			return true;
		}
		if(cur->isRoot_==false  &&  cur->keys_.size()>MIN_KEY)
			return true;
		if(borrowRichSiblingIndex(cur))
		{
			return true;
		}
		mergeIndex(cur);
		cur=cur->parent_;
	}
	assert(false);
	return false;
}

template<typename keytype, typename valuetype>
bool BPlusTree<keytype, valuetype>::borrowRichSiblingLeaf(BPTNode<keytype, valuetype> *node)
{
	int idx=node->FindSelfIdx();
	printf("叶子节点 %s 是父节点的第%d个子树\n", idx);
	if(idx>0  &&  node->parent_->children_[idx-1]->keys_.size()>MIN_RECORD)
	{
		node->LeafBorrowLeft(idx);
		return true;
	}
	if(node->parent_->keys_.size()>idx+1  &&  node->parent_->children_[idx+1]->keys_.size()>MIN_RECORD)
	{
		node->LeafBorrowRight(idx);
		return true;
	}
	return false;
}

template<typename keytype, typename valuetype>
bool BPlusTree<keytype, valuetype>::borrowRichSiblingIndex(BPTNode<keytype, valuetype> *node)
{
	int idx=node->FindSelfIdx();
	printf("索引节点 %s 是父节点的第%d个子树\n", idx);
	if(idx>0  &&  node->parent_->children_[idx-1]->keys_.size()>MIN_RECORD)
	{
		node->IndexBorrowLeft(idx);
		return true;
	}
	if(node->parent_->keys_.size()>idx+1  &&  node->parent_->children_[idx+1]->keys_.size()>MIN_RECORD)
	{
		node->IndexBorrowRight(idx);
		return true;
	}
	return false;
}

template<typename keytype, typename valuetype>
bool BPlusTree<keytype, valuetype>::mergeLeaf(BPTNode<keytype, valuetype> *node)
{
	int idx=node->FindSelfIdx();
	printf("叶子节点 %s 是父节点的第%d个子树\n", idx);
	if(idx>0)
	{
		node->LeafMergeLeft(idx);
	}
	else
	{
		node->LeafMergeRight(idx);
	}
	return true;
}

template<typename keytype, typename valuetype>
bool BPlusTree<keytype, valuetype>::mergeIndex(BPTNode<keytype, valuetype> *node)
{
	int idx=node->FindSelfIdx();
	printf("索引节点 %s 是父节点的第%d个子树\n", idx);
	if(idx>0)
	{
		node->IndexMergeLeft(idx);
	}
	else
	{
		node->IndexMergeRight(idx);
	}
	return true;
}

// 在B+树中查询key直到叶子节点，若查询成功返回true，leaf返回叶子节点，idx返回key所在位置
// 若查询失败，返回false
template<typename keytype, typename valuetype>
bool BPlusTree<keytype, valuetype>::Search_for_Delete(const keytype& key, BPTNode<keytype, valuetype>** leaf, int *idx)
{
	return Search_for_Insert(key, leaf, idx);
}

template<typename keytype, typename valuetype>
void BPlusTree<keytype, valuetype>::Print()
{
	printf("打印B+树：\n");
	BPTNode<keytype, valuetype>* cur= root_;
	int level=0;
	dfs(cur, level);
	printf("\t记录链表：");
	PrintRecord();
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


template<typename keytype, typename valuetype>
void BPlusTree<keytype, valuetype>::PrintRecord()
{
	for(BPTNode<keytype, valuetype> *node=head_; node!=NULL; node=node->next_)
	{
		printf("%s ", node->toString().c_str());
	}
	printf("\n");
}

#endif