

// 在树root中，查找所有累积和等于sum的路径
void getPath(int sum, BTNode* root)
{
	if(root==NULL)
		return;
	int level=0;
	if(computeSum(root, sum, &level))
		printPath(root, level);
	getPath(sum, root->left);
	getPath(sum, root->right);
}

bool computeSum(BTNode* child, int sum, int *level)
{
	int cur=0;
	level=0;
	while(child)
	{
		level++;
		cur+=child->data;
		if(cur>=sum)
			break;
		child=child->parent;
		
	}
	return cur==sum;
}

void printPath(BTNode* child, int level)
{
	for(int l=0; l<level; ++l)
	{
		printf("%d ", child->data);
		child=child->parent;
	}
	printf("\n");
}


// ============================================================
void getPath2(BTNode* root, int sum)
{
	std::vector<BTNode*> vec;
	traversePath(root, sum, vec);
}

void traversePath(BTNode* root, int sum, std::vector<BTNode*> vec)
{
	if(root==NULL)
		return;
	vec.push_back(root);
	int level=0;
	if(equalSum(vec, &level))
		printPath(vec, level);
	
	if(root->left)
		traversePath(root->left, sum, vec);
	if(root->right)
		traversePath(root->right, sum, vec);
}

bool equalSum(const std::vector<BTNode*> &vec, int sum, int *level)
{
	int cur=0;
	level=0;
	for(int i=vec.size()-1; i>=0; --i)
	{
		level++;
		cur+=vec[i]->data;
		if(cur>=sum)
			break;
	}
	return cur==sum;
}

void printPath(const std::vector<BTNode*> &vec, int level)
{
	for(int i=vec.size()-1; level>0; --i, --level)
		printf("%d ", vec[i]->data);
	printf("\n");
}


// ============================================================

void print2(vector<int> v, int level){
    for(int i=level; i<v.size(); ++i)
        cout<<v.at(i)<<" ";
    cout<<endl;
}
void find_sum2(Node* head, int sum, vector<int> v, int level){
    if(head == NULL) return;
    v.push_back(head->key);
    int tmp = 0;
    for(int i=level; i>-1; --i){
        tmp += v.at(i);
        if(tmp == sum)
            print2(v, i);
    }
    vector<int> v1(v), v2(v);
    find_sum2(head->lchild, sum, v1, level+1);
    find_sum2(head->rchild, sum, v2, level+1);
}






