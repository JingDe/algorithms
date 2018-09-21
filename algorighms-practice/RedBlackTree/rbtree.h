nginx的红黑树实现：

节点
struct rbtree_node_s{
	uintptr_t key;
	rbtree_node_t *left;
	rbtree_node_t *right;
	rbtree_node_t *parent;
	
	u_char color;
	u_char data;
};



树
struct rbtree_s{
	rbtree_node_t *root;
	rbtree_node_t *sentinel;
	rbtree_insert_pt insert;
};

插入一个节点函数
typedef void (*rbtree_insert_pt)(rbtree_node_t *root, rbtree_node_t* node, rbtree_node_t* sentinel);


初始化
rbtree_t newtree;
rbtree_node_t sentinel;

rbtree_init(newtree, sentinel, insertFunc)
{
	sentinel.color=0;
	
	newtree.root=sentinel;
	newtree.sentinel=sentinel;
	newtree.insert=insertFunc;
}

#define ngx_rbtree_init(tree, s, i) \
ngx_rbtree_sentinel_init(s); \
(tree)->root=s;
(tree)->sentinel=s;
(tree)->insert=i;

#define ngx_rbtree_sentinel_init(node) ngx_rbt_black(node)

#define ngx_rbt_black(node) ((node)->color=0)



左旋转
void ngx_rbtree_left_rotate(ngx_rbtree_node_t **root, ngx_rbtree_node_t *sentinel, ngx_rbtree_node_t *node)
{
	ngx_rbtree_node_t *temp;
	
	temp=node->right;
	
}




插入
void rbtree_insert(rbtree_t *tree, rbtree_node_t *node)
{
	rbtree_node_t **root, *temp, *sentinel;
	
	root=&(tree->root);
	sentinel=tree->sentinel;
	
	if(*root==sentinel)
	{
		node->parent=NULL;
		node->left=sentinel;
		node->right=sentinel;
		
	}
}



