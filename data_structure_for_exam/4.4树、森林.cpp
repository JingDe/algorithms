typedef struct node
{
	ElemType data;
	struct node *fch, *nsib;
}*Tree;

int Leaves(Tree t)
{
	if(t==NULL)
		return 0;
	if(t->fch==NULL)
		return 1+t->nsib;
	else
		return Leaves(t->fch)+Leaves(t->nsib);
}


int Height(CSTree t)
{
	int hc, hs;
	if(bt==NULL)
		return 0;
	else
	{
		hc=Height(bt->firstchild);
		hs=Height(bt->nextsibling);
		if(hc+1>hs)
			return hc+1;
		else
			return hs;
	}
}


#define maxNodes 15
void createCSTree_Degree(CSTree &T, DataType e[], int degree[], int n)
{
	CSNode *pointer=new CSNode[maxNodes];
	int i, j, d, k=0;
	for(i=0; i<n; i++)
	{
		pointer[i]=new CSNode;
		pointer[i]->data=e[i];
		pointer[i]->lchild=pointer[i]->rsibling=NULL;
	}
	for(i=0; i<n; i++)
	{
		d=degree[i];
		if(d)
		{
			k++;
			pointer[i]->lchild=pointer[k];
			for(j=2; j<=d; j++)
				pointer[k]->rsibling=pointer[++k];
		}
	}
	T=pointer[0];
	delete [] pointer;
}