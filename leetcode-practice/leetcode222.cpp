
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */


// 方法一：
// 返回树的高度，只有一个根节点的树的高度为0。
int height(TreeNode* root)
{
	return root==NULL ? -1 : 1+height(root->left);
}

// 时间复杂度 O(log(n)^2)
int countNodes(TreeNode* root) {
	int h=height(root);
	return h<0? 0 : 
			height(root->right)==h-1 ? (1<<h)+countNodes(root->right) 
				/*root->right的高度等于root->left的高度, root->left的高度是高度为h-1的满二叉树 */
								: (1<<h-1)+countNodes(root->left);
								/* root->right是高度为h-2的满二叉树*/
}

// 迭代版本
int countNodes(TreeNode* root)
{
	int nodes=0;
	int h=height(root);
	while(root!=NULL)
	{
		if(height(root->right)==h-1)
		{
			nodes+=1<<h;
			root=root->right;
		}
		else
		{
			nodes+=1<< (h-1);
			root=root->left;
		}
		h--;
	}
	return nodes;
}

// O(n)
int countNodes(TreeNode* root) 
{
	if(root==NULL)
		return 0;
	return 1+countNodes(root->left)+countNodes(root->right);
}

int countNodes(TreeNode* root)
{
	if(root==NULL)
		return 0;
	TreeNode* left=root;
	TreeNode* right=root;
	int height=0;
	while(right!=NULL)
	{
		left=left->left;
		right=right->right;
		height++;
	}
	if(left==NULL)
	｛
		return (1<<height) - 1; // 满二叉树，高度为height-1（单节点树高度为0）
	return 1+countNodes(root->left)+countNodes(root->right);
}
/*
时间复杂度：O(log(n)^2)
	
*/












