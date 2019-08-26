
TreeNode* sortedListToBST(ListNode* head) {
	return helper(head);
}

TreeNode* helper(ListNode* head) 
{
	if(head==NULL)
		return NULL;
	ListNode* fast=head;
	ListNode* slow=head;
	ListNode* pre=head;
	while(fast!=NULL)
	{
		fast=fast->next;
		if(fast==NULL)
			break;
		fast=fast->next;
		pre=slow;
		slow=slow->next;
	}
		
	
	ListNode* mid=slow;
	TreeNode* root=new TreeNode(mid->value);
	
	pre->next=NULL;
	root->left=helper(head);
	
	root->right=helper(mid->next);
	return root;
}

// 转换成数组，降低时间复杂度
TreeNode* sortedListToBST(ListNode* head) 
{
	vector<int> arr;
	while(head)
	{
		arr.push_back(head->val);
		head=head->next;
	}
	return helper(arr, 0, arr.size()-1);
}

TreeNode* helper(vector<int>& arr,  int start, int end)
{
	if(start>end)
		return NULL;
	int mid=start+(end-start)/2;
	TreeNode* root=new TreeNode(arr[mid]);
	root->left=helper(arr, start, mid-1);
	root->right=helper(arr, mid+1, end);
	return root;
}

// 模拟中序遍历
TreeNode* sortedListToBST(ListNode* head) 
{
	if(head==NULL)
		return NULL;
	ListNode* tmp=head;
	int len=0;
	while(head)
	{
		len++;
		head=head->next;
	}
	
	return formBst(tmp, 0, len-1);
}

TreeNode* formBst(ListNode*& head, int start, int end)
{
	if(start>end)
		return NULL;
	if(head==NULL)
		return NULL;
	int mid=start+(end-start)/2;
	TreeNode* left=formBst(head, start, mid-1);
	
	TreeNode* root=new TreeNode(head->val);
	head=head->next;
	root->left=left;
	
	root->right=formBst(head, mid+1, end);

	return root;
}