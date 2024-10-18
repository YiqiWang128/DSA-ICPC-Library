#include<bits/stdc++.h>
#define INF 2147483647
#define N 500100
#define M 2001000
const int mod=1e9+7;
using namespace std;
typedef long long ll;
int n,m,idx,num;
int head[N],dfn[N],low[N];
bool brg[M<<1];
int brg_num;
int bel[N],e_dcc_num;
vector<int>e_dcc[N];
struct Edge
{
    int to;
    int next;
}e[M<<1];
void add(int u,int v)
{
    e[idx].to=v;
    e[idx].next=head[u];
    head[u]=idx++;
}
void init()
{
    idx=num=0;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        head[i]=-1;
    for(int i=1;i<=m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        add(u,v);
        add(v,u);
    }
}
void tarjan(int x,int in_edge)
{
    //一定要从1开始，因为时间戳为0会被认为是尚未访问过
    dfn[x]=low[x]=++num;
    for(int i=head[x];~i;i=e[i].next)
    {
        if(i==(in_edge^1))
            continue;
        int v1=e[i].to;
        if(!dfn[v1])
        {
            tarjan(v1,i);
            low[x]=min(low[x],low[v1]);
            if(low[v1]>dfn[x])
            {
                brg[i]=brg[i^1]=true;
                brg_num++;
            }
        }
        else
            low[x]=min(low[x],dfn[v1]);
    }
}
//求出所有割边后dfs整张图，删去割边后的每个连通分量为边双连通分量
void dfs(int x)
{
    bel[x]=e_dcc_num;
    e_dcc[e_dcc_num].push_back(x);
    for(int i=head[x];~i;i=e[i].next)
    {
        int v1=e[i].to;
        if(bel[v1] || brg[i])
            continue;
        dfs(v1);
    }
}
void solve()
{
    for(int i=1;i<=n;i++)
        if(!dfn[i])
            tarjan(i,-1);
    for(int i=1;i<=n;i++)
    {
        if(bel[i])
            continue;
        e_dcc_num++;//这个要放到dfs外面
        dfs(i);
    }
    printf("%d\n",e_dcc_num);
    for(int i=1;i<=e_dcc_num;i++)
    {
        int siz=e_dcc[i].size();
        printf("%d ",siz);
        for(int j=0;j<siz;j++)
            printf("%d ",e_dcc[i][j]);
        printf("\n");
    }
}
int main()
{
    init();
    solve();
    return 0;
}
