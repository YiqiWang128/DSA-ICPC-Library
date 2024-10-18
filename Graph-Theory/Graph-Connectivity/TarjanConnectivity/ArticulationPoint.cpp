#include<bits/stdc++.h>
#define INF 2147483647
#define N 500100
#define M 500100
const int mod=1e9+7;
using namespace std;
typedef long long ll;
int n,m,idx,num;
int head[N],dfn[N],low[N];
bool cut[N];
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
    int son_x=0;
    for(int i=head[x];~i;i=e[i].next)
    {
        if(i==(in_edge^1))
            continue;
        int v1=e[i].to;
        if(!dfn[v1])
        {
            son_x++;
            tarjan(v1,i);
            low[x]=min(low[x],low[v1]);
            if(low[v1]>=dfn[x])
                cut[x]=true;
        }
        else
            low[x]=min(low[x],dfn[v1]);
    }
    //特判搜索树的根节点
    if(in_edge==-1 && son_x==1)
        cut[x]=false;
}
void solve()
{
    for(int i=1;i<=n;i++)
        if(!dfn[i])
            tarjan(i,-1);
    int cnt_ans=0;
    for(int i=1;i<=n;i++)
        if(cut[i])
            cnt_ans++;
    printf("%d\n",cnt_ans);
    for(int i=1;i<=n;i++)
        if(cut[i])
            printf("%d ",i);
    printf("\n");
}
int main()
{
    init();
    solve();
    return 0;
}
