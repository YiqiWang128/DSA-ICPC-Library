#include<bits/stdc++.h>
#define INF 2147483647
#define N 500100
#define M 500100
const int mod=1e9+7;
using namespace std;
typedef long long ll;
int n,idx;
int head[N],d1[N],d2[N];
int ans;
struct Edge
{
    int to;
    int w;
    int next;
}e[M<<1];
void add(int u,int v,int w)
{
    e[idx].to=v;
    e[idx].w=w;
    e[idx].next=head[u];
    head[u]=idx++;
}
void init()
{
    idx=0;
    ans=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        head[i]=-1;
    for(int i=1;i<=n-1;i++)
    {
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        add(u,v,w);
        add(v,u,w);
    }
}
void dfs(int u,int fa)
{
    d1[u]=d2[u]=0;
    for(int i=head[u];~i;i=e[i].next)
    {
        int v1=e[i].to,w1=e[i].w;
        if(v1==fa)
            continue;
        dfs(v1,u);
        int t=d1[v1]+w1;
        if(t>d1[u])
            d2[u]=d1[u],d1[u]=t;
        else if(t>d2[u])
            d2[u]=t;
        ans=max(ans,d1[u]+d2[u]);
    }
}
int main()
{
    init();
    dfs(1,0);
    printf("%d\n",ans);
    return 0;
}
