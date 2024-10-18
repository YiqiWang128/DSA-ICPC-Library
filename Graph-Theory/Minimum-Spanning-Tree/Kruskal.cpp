#include<bits/stdc++.h>
#define INF 2147483647
#define N 500100
#define M 500100
const int mod=1e9+7;
typedef long long ll;
using namespace std;
struct Edge
{
    int u,v;
    int w;
}e[2*M];
bool cmp(Edge x,Edge y)
{
    return x.w<y.w;
}
int n,m,idx;
int fa[N],Rank[N];
void add(int u,int v,int w)
{
    e[idx].u=u,e[idx].v=v;
    e[idx++].w=w;
}
void init()
{
    idx=0;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        Rank[i]=0;
        fa[i]=i;
    }
    for(int i=1,u,v,w;i<=m;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        add(u,v,w);
    }
}
inline int getfa(int x)//查询
{
    if(fa[x]==x)
        return x;
    return fa[x]=getfa(fa[x]);
}
inline void rank_union(int x,int y)
{
    int fx=getfa(x),fy=getfa(y);
    if(Rank[fx]<Rank[fy])
        fa[fx]=fy;
    else
    {
        fa[fy]=fx;
        if(Rank[fx]==Rank[fy])
            Rank[fx]++;
    }
}
void solve()
{
    ll ans=0;
    int merged=0;
    sort(e,e+idx,cmp);
    for(int i=0;i<idx;i++)
    {
        int u=getfa(e[i].u),v=getfa(e[i].v);
        int w=e[i].w;
        if(u!=v)
        {
            merged++;
            ans+=w;
            rank_union(u,v);
        }
        if(merged>=n-1)
            break;
    }
    if(merged==n-1)
        printf("%lld\n",ans);
    else
        puts("orz");
}
int main()
{
    init();
    solve();
    return 0;
}
