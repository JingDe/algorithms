#include<iostream>
#include<cstring>
#include<cstdint>

const static int N=100;

int graph[N][N];
int dmin[N];
//std::set<int>
bool visited[N];
int left;

void makeGraph(int n)
{
    memset(graph, -1, sizeof(graph));
    memset(visited, false, sizeof(visited));
    
    int line=(n)*(n-1)/2;
    for(int i=0; i<line; i++)
    {        
        //std::string str;
        //std::getline(std::cin, str);
            int x, y;
            std::cin>>x;
            std::cin>>y;
            std::cin>>graph[x][y];
            graph[y][x]=graph[x][y];
    }
    
    memset(dmin, -1, sizeof(dmin));
    dmin[1]=0;
    for(int i=2; i<=n; i++)
    {
        graph[i][i]=0;
        dmin[i]=graph[1][i];
    }
}
int getmin(int n)
{
    int min=-1;
    int ret;
    for(int i=2; i<=n; i++)
    {
        if(visited[i]==false &&  dmin[i]>0)
        {            
            if(min!=-1  &&  dmin[i]<min)
            {
                min=dmin[i];
                ret=i;
            }
            else if(min==-1)
            {
                min=dmin[i];
                ret=i;
            }
        }
    }
    return ret;
}

void update(int n, int start)
{
    for(int i=2; i<=n; i++)
    {
        if(visited[i]==false  && dmin[i]>dmin[start]+graph[start][i])
            dmin[i]=dmin[start]+graph[start][i];
    }
}

int solve(int n)
{
    left=n-1;
    int result=0;
    while(left>0)
    {
        int m=getmin(n);// 获得visited为false的dmin中最小值的下标
        visited[m]=true;
        result+=dmin[m];
        
        // 更新剩余节点的dmin
        update(n, m);
        left--;
    }
    return result;
}

int main()
{
    int n;
    while(std::cin>>n  && n)
    {
        makeGraph(n);
        
        int res=solve(n);
        std::cout<<res<<std::endl;
    }
    return 0;
}
