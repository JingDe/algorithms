
// https://my.oschina.net/victorlovecode/blog/344444

void RBTree::rbtree_left_rotate( rbtree_node_t* node_x)
{
     rbtree_node_t *node_y;
     rbtree_node_t **root = & m_rbtree. root;
     rbtree_node_t *sentinel = m_rbtree. sentinel;

     node_y = node_x-> right;                       //Setp 1. 设置y
	 
	 // 更新 node_x->right和其parent
     node_x-> right = node_y-> left;               //Step 2 .将y 的左子树变为x的右子树
     if(node_y-> left != sentinel)
     {
          node_y-> left-> parent = node_x;
     }
	 
	 // 更新node_y的parent和其left或者right 或者root
     node_y-> parent = node_x-> parent;            //Step 3. 设置y的父亲
     if(node_x == *root)                            //空树，将y设为根
     {
          *root = node_y;
     }
     else if(node_x == node_x->parent ->left )      //x为左子树，将y放在x父节点的左子树
     {
          node_x-> parent-> left = node_y;
     }
     else                                           //x为右子树，将y放在x父节点的右子树
     {
          node_x-> parent-> right = node_y;
     }
	 
	 // 更新node_y和node_x的父子关系
     node_y-> left = node_x;                       //Step4.将x链到y的左子树
     node_x-> parent = node_y;
}

void RBTree::rbtree_insert_fixup( rbtree_node_t *node_z)
{
	rbtree_node_t **root = & m_rbtree.root;
	rbtree_node_t *node_y;
	while( node_z != *root && rbt_is_red(node_z-> parent))
	{
		if(node_z-> parent == node_z->parent->parent->left)
		{
			node_y = node_z->parent->parent->right;
			//case1:z的叔叔y是红色
			if(rbt_is_red(node_y))
			{
				rbt_black( node_z->parent);
				rbt_black(node_y);
				rbt_red( node_z->parent->parent);
				node_z = node_z ->parent ->parent ;
			}
			else
			{
				//case2:z的叔叔y是黑色，且z是右孩子
				if(node_z == node_z->parent->right)
				{
					node_z = node_z ->parent ;
					rbtree_left_rotate( node_z);
				}
				rbt_black( node_z->parent);
				rbt_red( node_z->parent->parent);
				rbtree_right_rotate( node_z);
			}
		}
		else
		{
			node_y = node_z->parent->parent->left;
			//case1:z的叔叔y是红色
			if(rbt_is_red(node_y))
			{
				rbt_black( node_z->parent);
				rbt_black(node_y);
				rbt_red( node_z->parent->parent);
				node_z = node_z ->parent ->parent ;
			}
			else
			{
				//case2:z的叔叔y是黑色，且z是左孩子
				if(node_z == node_z->parent->left)
				{
					node_z =node_z ->parent ;
					rbtree_right_rotate( node_z);
				}
				rbt_black( node_z->parent);
				rbt_red( node_z->parent->parent);
				rbtree_left_rotate( node_z->parent->parent);
			}
		}
	}
	rbt_black(*root);
}