/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return helper(nums, 0, nums.size());
    }
    TreeNode* helper(vector<int>& nums, int left, int right)
    {
    	if(left>=right)
    		return NULL;
    	int middle=(left+right)/2;
    	TreeNode* root=new TreeNode(nums[middle]);
    	root->left=helper(nums, left, middle);
    	root->right=helper(nums, middle+1, right);
    	return root;
	}
};

// 方法一： 
    TreeNode *sortedArrayToBST(vector<int> &num) {
        if(num.size() == 0) return NULL;
//        if(num.size() == 1)
//        {
//            return new TreeNode(num[0]);
//        }
        
        int middle = num.size()/2;
        TreeNode* root = new TreeNode(num[middle]);
        
        vector<int> leftInts(num.begin(), num.begin()+middle);
        vector<int> rightInts(num.begin()+middle+1, num.end());
        
        root->left = sortedArrayToBST(leftInts);
        root->right = sortedArrayToBST(rightInts);
        
        return root;
    }
    
// 方法二    
struct TreeNode* convert(int* nums,int start,int end)
{
     if(start > end)
          return NULL;
     else{
         int mid = (start+end)/2;
         struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
         node->val = nums[mid];
         node->left = convert(nums,start,mid-1);
         node->right = convert(nums,mid+1,end);
         return node;
     }
}


struct TreeNode* sortedArrayToBST(int* nums, int numsSize) {
        return convert(nums,0,numsSize-1);
}
