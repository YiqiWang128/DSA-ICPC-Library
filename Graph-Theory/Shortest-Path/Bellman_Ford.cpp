#include<bits/stdc++.h>
#define INF 2147483647
#define N 500100
#define M 500100
const int mod=1e9+7;
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
struct Edge
{
    int from,to;
    int w;
    int next;
}e[M<<1];
int n,m,idx;
int head[N],dist[N];
void add(int u,int v,int w)
{
    e[idx].from=u,e[idx].to=v;
    e[idx].w=w;
    e[idx].next=head[u];
    head[u]=idx++;
}
void init()
{
    idx=0;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        head[i]=-1;
    for(int i=1;i<=m;i++)
    {
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        //非负权边为双向边，负权边为单向边
        if(w>=0)
        {
            add(u,v,w);
            add(v,u,w);
        }
        else
            add(u,v,w);
    }
}
//判断图中是否存在从源点x出发能到达的负环，若能返回true，若不能返回false
bool Bellman_Ford(int x)
{
    for(int i=1;i<=n;i++)
        dist[i]=0x3f3f3f3f;
    dist[x]=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<idx;j++)//m不是图的边数，idx才是！！！
        {
            int u1=e[j].from,v1=e[j].to;
            int w1=e[j].w;
            //非常重要！！！这样才能判断从源点出发是否可以抵达一个负环！！！
            if(dist[u1]==0x3f3f3f3f)
                continue;
            if(dist[v1]>dist[u1]+w1)
            {
                dist[v1]=dist[u1]+w1;
                if(i==n)
                    return true;
            }
        }
    }
    return false;
}
void solve()
{
    if(Bellman_Ford(1))
        puts("YES");
    else
        puts("NO");
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        init();
        solve();
    }
    return 0;
}
