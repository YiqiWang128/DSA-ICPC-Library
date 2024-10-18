#include<bits/stdc++.h>
#define INF 2147483647
#define N 500100
#define M 500100
const int mod=1e9+7;
typedef long long ll;
using namespace std;
struct Edge
{
    int from,to;
    int w;
    int next;
}e[M];
int n,m,idx;
int head[N],fa[N],Rank[N];
int best[N];//best[x]=y:从编号为x的连通分量出发，边权最小的边的编号为y
bool used[M];//标记已经加入最小生成树的边
void add(int u,int v,int w)
{
    e[idx].from=u,e[idx].to=v;
    e[idx].w=w;
    e[idx].next=head[u];
    head[u]=idx++;
}
inline void init()
{
    idx=0;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        head[i]=-1;
        fa[i]=i;
        Rank[i]=0;
    }
    for(int i=1,u,v,w;i<=m;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        add(u,v,w);
        add(v,u,w);
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
inline bool better(int x,int y)//x,y是边的编号，边x比边y更小，则返回true
{
    if(y==-1)
        return true;
    if(e[x].w!=e[y].w)
        return e[x].w<e[y].w;
    return x<y;
}
void solve()
{
    init();
    ll ans=0;
    int merged=0;
    bool update=true;
    while(update)
    {
        update=false;
        memset(best,-1,sizeof(best));
        for(int i=0;i<idx;i++)
        {
            if(used[i])
                continue;
            int u=getfa(e[i].from),v=getfa(e[i].to);
            if(u==v)
                continue;
            if(better(i,best[u]))
                best[u]=i;
            if(better(i,best[v]))
                best[v]=i;
        }
        for(int i=1;i<=n;i++)
        {
            if(best[i]!=-1 && used[best[i]]==false)
            {
                update=true;
                merged++;
                ans+=e[best[i]].w;
                used[best[i]]=1;
                rank_union(e[best[i]].from,e[best[i]].to);
            }
        }
    }
    if(merged==n-1)
        printf("%lld\n",ans);
    else
        puts("orz");
}
int main()
{
    solve();
    return 0;
}
