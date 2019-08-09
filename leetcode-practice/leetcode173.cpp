
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class BSTIterator {
public:
    BSTIterator(TreeNode* root) {
        // 中序遍历
		// 记录每个节点的后继节点
		lastVisited=NULL;
		middleTraverse(root);
		nextNode[last]=NULL;
		
		it=nextNode.begin();
    }
	
	void middleTraverse(TreeNode* root)
	{
		if(root==NULL)
			return;
		middleTraverse(root->left);
		if(lastVisited)
			nextNode[lastVisited]=root;
		lastVisited=root;
		middleTraverse(root->left);
	}
    
    /** @return the next smallest number */
    int next() {
        int ret=it->first->val;
		++it;
		return ret;
    }
    
    /** @return whether we have a next smallest number */
    bool hasNext() {
        if(it==nextNode.end())
			return false;
		return true;
    }
	
	TreeNode* lastVisited;
	map<TreeNode*, TreeNode*> nextNode; // 使用vector、list代替
	map<TreeNode*, TreeNode*>::iterator it;
};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
 
 class BSTIterator {
public:
    BSTIterator(TreeNode* root) {
        // 中序遍历
		// 记录每个节点的后继节点
		middleTraverse(root);
		
		it=seq.begin();
    }
	
	void middleTraverse(TreeNode* root)
	{
		if(root==NULL)
			return;
		middleTraverse(root->left);
		seq.push_back(root);
		middleTraverse(root->left);
	}
    
    /** @return the next smallest number */
    int next() {
        int ret=*it->val;
		++it;
		return ret;
    }
    
    /** @return whether we have a next smallest number */
    bool hasNext() {
        if(it==seq.end())
			return false;
		return true;
    }
	
	vector<TreeNode*> seq;
	vector<TreeNode*>::iterator it;
};

class BSTIterator {
public:
    BSTIterator(TreeNode* root) {
        // 中序遍历
		// 记录每个节点的后继节点
		middleTraverse(root);
		
		cur=0;
    }
	
	void middleTraverse(TreeNode* root)
	{
		if(root==NULL)
			return;
		middleTraverse(root->left);
		seq.push_back(root);
		middleTraverse(root->left);
	}
    
    /** @return the next smallest number */
    int next() {
        return seq[cur++];
    }
    
    /** @return whether we have a next smallest number */
    bool hasNext() {
        if(cur==seq.size())
			return false;
		return true;
    }
	
	vector<TreeNode*> seq;
	int cur;
};

Line 29: Char 28: runtime error: member access within misaligned address 0xbebebebebebebebe for type 'struct TreeNode', which requires 8 byte alignment (solution.cpp)
0xbebebebebebebebe: note: pointer points here
<memory cannot be printed>

// 二叉树，中序非递归遍历
void middleTraverse(TreeNode* root)
{
	stack<TreeNode*> S;
	TreeNode* cur=root;
	while(cur  ||  !S.empty())
	{
		while(cur)
		{
			S.push(cur);
			cur=cur->left;
		}
		if(!S.empty())
		{
			cur=S.top();
			S.pop();
			visit(cur);
			cur=cur->right;
		}
	}
	
}

// 参考答案
class BSTIterator {
public:
    BSTIterator(TreeNode* root) {
        find_left(root);
    }
    
    /** @return the next smallest number */
    int next() {
        TreeNode* top=st.top();
		st.pop();
		if(top->right!=NULL)
			find_left(top->right);
		return top->val;
    }
    
    /** @return whether we have a next smallest number */
    bool hasNext() {
        if(st.empty())
			return false;
		return true;
    }
	
	void find_left(TreeNode* root)
	{
		TreeNode* p=root;
		while(!p=NULL)
		{
			st.push(p);
			p=p->left;
		}
	}
	
private:
	stack<TreeNode*> st;
};

class BSTIterator {
public:
    BSTIterator(TreeNode* root) {
        cur=root;
    }
    
    /** @return the next smallest number */
    int next() {
        while(cur!=NULL)
		{
			st.push(cur);
			cur=cur->left;
		}
		TreeNode* next=st.top();
		st.pop();
		cur=next->right;
		return next->val;
    }
    
    /** @return whether we have a next smallest number */
    bool hasNext() {
        if(st.empty()  &&  cur==NULL)
			return false;
		return true;
    }
	
	
private:
	stack<TreeNode*> st;
	TreeNode* cur;
};