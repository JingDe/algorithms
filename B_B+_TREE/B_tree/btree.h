#ifndef BTREE_H_
#define BTREE_H_

#include<cstdio>
#include<algorithm>
#include<list>
#include<vector>
#include<stack> 
#include<string>
#include<sstream>

static const int M=5; // M��B��
static const int MAX=M-1; // ÿ���ڵ����M-1����¼
static const int MIN=(M+1)/2-1; // �Ǹ��ڵ�����math.ceil(m/2)-1����¼


template<typename keytype, typename valuetype>
class BTree;

/* 
 *	BTNode
 */

template<typename keytype, typename valuetype>
class BTNode{
public:
	
	struct RecordType{
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
	};
	
private:	
	BTNode* parent_;
	int num_;	// ��¼����
	std::list<RecordType> records_; //��¼�б�����, �±�0~num_-1
	std::vector<BTNode*> children_; // �ӽڵ��б�, �±�0~num_
	
	
public:
	BTNode();
	~BTNode();
	
	bool isLeaf(){
		return children_.empty();
	}
	
	int FindIdx();
	void addRecordWithRightChild(const struct RecordType& record, struct BTNode* rightChild);
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
	:parent_(0)
{
	
}



template<typename keytype, typename valuetype>
BTNode<keytype, valuetype>::~BTNode()
{
	//for(std::vector<BTNode*>::it=children_.begin(); it!=children_.end(); it++)
	//	delete *it;
	
}

template<typename keytype, typename valuetype>
void BTNode<keytype, valuetype>::addRecordWithRightChild(const struct RecordType& record, struct BTNode* rightChild)
{		
	//typename std::list<RecordType>::iterator it=upper_bound(records_.begin(), records_.end(), record);
	//int idx=it-records_.begin();// ȷ���¼�¼recordӦ���ڽڵ��records_�е�λ��
	typename std::list<RecordType>::iterator it=records_.begin();
	int idx=0;
	for(; it!=records_.end(); it++)
	{		
		if(it->key>record.key)
			break;
		idx++;
	}
	
	records_.insert(it, record);
	children_.insert(children_.begin()+idx+1, rightChild);
	
	rightChild->parent_=this;
}



// ���ѽڵ�p������ұ߽ڵ�rightN ���м��¼
template<typename keytype, typename valuetype>
void BTNode<keytype, valuetype>::split(BTNode** rightN, RecordType *mid)
{
	BTNode* rightNode;
	//BTNode *parent=p->parent_;
	
	bool isLeaf;
	if(children_.empty())
		isLeaf=true;
	else
		isLeaf=false;
	
	// ���Ѻ���߽ڵ㱣��left�������ұ߱���right�������м�һ�����뵽���ڵ�
	int left=(num_-1)/2; // p->num_����M,  �±�0~left-1
	int right=num_-left-1; // �±� left+1~p->num_-1
	
	//*mid=records_[left];  // �±�left, vector
	//*mid=getIdx(records_, left);//list
	typename std::list<RecordType>::iterator ite=records_.begin();
	for(int i=0; i<left; i++)
	{
		ite++;
	}
	*mid=*ite;
	
	rightNode=*rightN; // *rightN=rightNode;
	*rightN=new BTNode();				
	rightNode->num_=right;
	
	typename std::list<RecordType>::iterator ite2=records_.begin();
	for(int i=0; i<left+1; i++)
		ite2++;
	rightNode->records_.assign(ite2, records_.end());
	//rightNode->records_.assign(records_.begin()+left+1, records_.end());
	if(!isLeaf)
		rightNode->children_.assign(children_.begin()+left+1, children_.end());// p->children_[left+1...]
	//rightNode->parent_=parent;
	
	num_=left;
	records_.resize(left);
	if(!isLeaf)
		children_.resize(left+1);// children_[0...left]
}

template<typename keytype, typename valuetype>
int BTNode<keytype, valuetype>::FindIdx()
{
	if(parent_==0)
		return -1;
	
	for(typename std::list<BTNode*>::iterator it=parent_->children_.begin(); 
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
	for(typename std::list<RecordType>::iterator it=records_.begin(); it!=records_.end(); it++)
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


// ����һ����¼�����Ѵ��������value���������Ҷ�ڵ���
template<typename keytype, typename valuetype>
void BTree<keytype, valuetype>::Insert(const keytype& key, const valuetype& value)
{
	printf("\n\n*** ����<%d, %d> ***\n", key, value);
	
	BTNode<keytype, valuetype> *p=root;
	BTNode<keytype, valuetype> *rightNode;
	typename BTNode<keytype, valuetype>::RecordType newrecord(key, valuetype());
	int idx;
	typename std::list<typename BTNode<keytype, valuetype>::RecordType>::iterator it;
	
	if(root==0)
	{
		printf("�����root\n"); 
		root=new BTNode<keytype, valuetype>();
		root->num_=1;
		root->records_.push_back(newrecord);
		root->children_.clear();
		return;
	}
	while(p)
	{
		if(p->isLeaf()) 
			break; // ��p�޶��ӽڵ㣬�˳�ѭ��
		
		// lower_bound�Ǵ��ڵ��ڣ�upper_bound�Ǵ���
		//it=lower_bound(p->records_.begin(), p->records_.end(), newrecord);//���Ҽ�¼��λ��
		for(it=p->records_.begin(); it!=p->records_.end(); it++)
		{
			if(it->key>=newrecord.key)
				break;
		}
		if(it!=p->records_.end()  &&  it->key==key)
		{
			printf("���½ڵ�: %s\n", p->toString().c_str());
			it->value=value;
			printf("���º�ڵ�: %s\n", p->toString().c_str());
			return;
		}
		
		if(it!=p->records_.end())
		{
			//idx=it - p->records_.begin();//vector������
			idx=std::distance(it, p->records_.begin());//list������
		}
		else 
		{
			idx=p->num_;// �ߵ����һ�����ӽڵ�
		}		
		
		
		p=p->children_[idx]; // ��λ����Ӧ���ӽڵ�
	}

	printf("����Ҷ�ڵ�: %s\n", p->toString().c_str());
	//�˴���p��Ҷ�ڵ�
	
	p->num_++;
	p->records_.insert(it, newrecord); // �쳣�˳����� 
	printf("����֮����ʱ: %s\n", p->toString().c_str());

	// ��Ҷ�ڵ�����ɸѡ
	while(p->num_>=M  &&  p!=root)
	{
		printf("���ѽڵ�: %s\n", p->toString().c_str());
		
		BTNode<keytype, valuetype> *parent=p->parent_;//p��Ϊroot����parent��Ϊ0
		p->split(&rightNode, &newrecord); // ���ѵ�ǰ�ڵ�p���õ��µ��Ұ�߽ڵ���м�λ�õļ�¼
		parent->addRecordWithRightChild(newrecord, rightNode);// ��ʱ����һ����¼�ʹ��ڸü�¼�ұߵĶ���ָ��
		
		p=parent;
	}
	if(p==root  &&  p->num_>=M) // ���Ѹ��ڵ�
	{
		printf("���Ѹ��ڵ�: %s\n", p->toString().c_str());
		p->split(&rightNode, &newrecord);
		
		BTNode<keytype, valuetype> *newroot=new BTNode<keytype, valuetype>();
		newroot->parent_=0;
		newroot->num_==1;
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
		typename std::list<typename BTNode<keytype, valuetype>::RecordType>::iterator it=lower_bound(cur->records_.begin(), cur->records_.end(), record);
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
	struct RecordType record(key, valuetype());
	int idx;
	BTNode<keytype, valuetype> *child;
	typename std::list<typename BTNode<keytype, valuetype>::RecordType>::iterator it;
	
	//Ѱ�Ҵ�ɾ����¼���ڽڵ�cur
	//if(root==0)
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
	if(cur==0)
		return;
	
	
	if(cur->isLeaf()==false)//����ɾ����¼���ڽڵ�cur����Ҷ�ӽ�㣬Ѱ�Һ�̼�¼���ڵ�Ҷ�ӽ��child
	{
		child=cur->children_[idx+1]; // ��̽��
		while(child->isLeaf()==false)
			child=child->children[0];
		it=child->records_[0];	// �ú�̽���滻��ɾ����¼
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
		
		idx=cur->FindIdx(); // ȷ��cur���丸�ڵ�Ķ��ӽڵ������е�����
		
		
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
		
		
		if(idx>0)// �����ֵܽ��ϲ�
		{
			merge(parent, idx-1, idx);
		}
		else// �����ֵܽ��ϲ�
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
	leftN->records_.splice(leftN->records_.end(), rightN->records_);// list
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
