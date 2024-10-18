#include<bits/stdc++.h>
#define INF 2147483647
#define N 500100
#define M 500100
const int mod=1e9+7;
typedef long long ll;
using namespace std;
int n,q,root;
int a[N];
struct Edge
{
    int to;
    int next;
}e[2*M];
int head[N],depth[N],idx;
int fa[N][30];//fa[i][j]:从i点往上跳2^j步所达到节点的编号
void add(int u,int v)
{
    e[idx].to=v;
    e[idx].next=head[u];
    head[u]=idx++;
}
void init()
{
    idx=0;
    scanf("%d%d%d",&n,&q,&root);
    for(int i=0;i<=n;i++)
    {
        head[i]=-1;
        depth[i]=INF;//一种标记，便于bfs
    }
    for(int i=1,u,v;i<=n-1;i++)
    {
        scanf("%d%d",&u,&v);
        add(u,v);
        add(v,u);
    }
}
void bfs(int x)//以x为根bfs
{
    depth[0]=0;//哨兵的深度为0
    depth[x]=1;//根的深度为1
    for(int k=0;k<=20;k++)
    {
        //超过根节点就认为它们跳到了0
        fa[x][k]=0;
        fa[0][k]=0;
    }
    queue<int>Q;
    Q.push(x);
    while(!Q.empty())
    {
        int t=Q.front();
        Q.pop();
        //t及其所有祖先的fa信息已更新完毕，下面的for循环更新t所有直接儿子的fa信息
        for(int i=head[t];~i;i=e[i].next)
        {
            int v1=e[i].to;
            if(depth[v1]!=INF)
                continue;
            depth[v1]=depth[t]+1;
            Q.push(v1);
            fa[v1][0]=t;//动态规划的初始化
            for(int k=1;k<=20;k++)
                fa[v1][k]=fa[fa[v1][k-1]][k-1];//动态规划，递推
        }
    }
}
int LCA(int x,int y)
{
    if(depth[x]<depth[y])
        swap(x,y);//跳更深的那一个点
    //先跳到同样的深度
    for(int k=20;k>=0;k--)//从大到小试探着往上跳
        if(depth[fa[x][k]]>=depth[y])
            x=fa[x][k];//只要还没有越过目标位置就继续跳，k依次递减
    if(x==y) 
        return x;//如果重合，直接return
    for(int k=20;k>=0;k--)//从大到小试探着往上跳
    {
        //两个点一起尽量往上跳，限制它们不相遇（也就是一直跳到恰比LCA更深一层的位置）
        if(fa[x][k]!=fa[y][k])//这里暗含了超过根结点的情况，因为超过根的话就认为它们跳到了0
        {
            x=fa[x][k];
            y=fa[y][k];
        }
    }
    return fa[x][0];
}
void solve()
{
    bfs(root);//O(NlogN)预处理
    for(int i=1,x,y;i<=q;i++)
    {
        scanf("%d%d",&x,&y);
        printf("%d\n",LCA(x,y));//O(logN)单词查询
    }
}
int main()
{
    init();
    solve();
    return 0;
}
