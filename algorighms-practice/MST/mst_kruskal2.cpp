/*
 * mst kruskal算法的第二种实现：
 *
 * 改动：
 * 不使用map，使用排序数组
 *
 * 改进：
 * 并查集，union的时候，只查找一个子树的根节点，修改它的父节点
 * */

#include<iostream>
#include<algorithm>

 const static int N=100; // 顶点的最大个数
 const static int MAXEDGE=N*(N-1)/2;

 struct EdgeType{
     int l;
     int r;
     int w;

     EdgeType(){}
     EdgeType(int l, int r, int w):l(l),r(r),w(w){}
     bool operator<(const EdgeType& r)
     {
         return w<r.w;
     }
 };

 EdgeType edges[MAXEDGE];
int ufset[N];

int find(int x)
{
    while(ufset[x]>-1)
        x=ufset[x];
    return x;
}


void make_graph(int n)
{
    int count=n*(n-1)/2;
    int e1, e2, w;
    for(int i=0; i<count; i++)
    {
        std::cin>>e1>>e2>>w;
        edges[i]=EdgeType(e1, e2, w);
    }
    std::sort(edges, edges+count);

    for(int i=0; i<n; i++)
    {
        ufset[i]=-1;
    }

    //debug_print();
}


int solve(int n)
{
    int res=0;
    int e1, e2, w;
    int edgeno=0;

    // n个节点要连通，选择n-1条边
    for(int c=0; c<n-1; )
    {
        w=edges[edgeno].w;
        e1=edges[edgeno].l;
        e2=edges[edgeno].r;
        edgeno++;

        //printf("%d —— %d : %d\n", e1, e2, w);

        int root1=find(e1);
        int root2=find(e2);
        if(root1 != root2)
        {
            // 两个不连通的节点
            //Union(e1, e2);
            ufset[root1]=root2;
            res+=w;
            //printf("%d —— %d : %d, %d\n", e1, e2, w, res);
            c++;
        }
    }
    return res;
}


int main()
{
    int n;
    int res;

    while(std::cin>>n  &&  n)
    {
        make_graph(n);

        res=solve(n);
        std::cout<<res<<std::endl;
    }

    return 0;
}

