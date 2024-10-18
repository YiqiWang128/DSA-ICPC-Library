#include<bits/stdc++.h>
#define INF 2147483647
#define N 500100
#define M 500100
const int mod=1e9+7;
typedef long long ll;
using namespace std;
int n,q,root,idx;
int head[N],fa[N],st[N],ans[N];
vector<pair<int,int>>Query[N];
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
    idx=0;
    scanf("%d%d%d",&n,&q,&root);
    for(int i=1;i<=n;i++)
    {
        fa[i]=i;
        head[i]=-1;
    }
    for(int i=1,u,v;i<=n-1;i++)
    {
        scanf("%d%d",&u,&v);
        add(u,v);
        add(v,u);
    }
    for(int i=1,x,y;i<=q;i++)
    {
        scanf("%d%d",&x,&y);
        if(x==y)
            ans[i]=x;
        else
        {
            Query[x].push_back({y,i});
            Query[y].push_back({x,i});
        }
    }
}
int getfa(int x)
{
    if(x!=fa[x])
        fa[x]=getfa(fa[x]);
    return fa[x];
}
void tarjan_LCA(int x)
{
    st[x]=1;
    for(int i=head[x];~i;i=e[i].next)
    {
        int v1=e[i].to;
        if(st[v1]!=0)
            continue;
        tarjan_LCA(v1);
        fa[v1]=x;//这句话必须在递归之后，否则WA
    }
    for(auto item:Query[x])
    {
        int y=item.first;
        int id=item.second;
        if(st[y]==2)
            ans[id]=getfa(y);
    }
    st[x]=2;
}
void solve()
{
    tarjan_LCA(root);
    for(int i=1;i<=q;i++)
        printf("%d\n",ans[i]);
}
int main()
{
    init();
    solve();
    return 0;
}
