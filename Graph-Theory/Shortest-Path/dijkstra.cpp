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
int n,m,S,idx;
int head[N],dist[N];
//dijkstra不需要标记访问过的点，因为同一个点可能被多次访问然后多次松弛，算法的可终止性由P标号点数量单调不减保证
bool ins[N];//储存P标号点
//优先队列本该只存T标号点，但STL不支持删除，因此取min，一直pop，直到出现T标号点
priority_queue<PII,vector<PII>,greater<PII>>PQ;//其中既有没删干净的P标号点，也有被松弛过的T标号点
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
    scanf("%d%d%d",&n,&m,&S);
    for(int i=1;i<=n;i++)
        head[i]=-1;
    for(int i=1;i<=m;i++)
    {
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        add(u,v,w);
    }
}
//先取dis最小的T标号点将其改为P标号，再用刚获得的P标号点松弛它的(T标号)邻居
void dijkstra(int x)
{
    for(int i=1;i<=n;i++)
        dist[i]=0x3f3f3f3f;//大于1e9
    dist[x]=0;
    PQ.push({0,x});
    while(!PQ.empty())
    {
        int t=PQ.top().second;
        PQ.pop();
        //同一个点可能被多次松弛然后被多次加入堆，无法一次全部删除，因此堆中可能存在垃圾值
        if(ins[t]) 
            continue;
        ins[t]=true;//取dist值最小的T标号点，将其改为P标号
        //用刚获得的P标号点松弛它的T标号邻居
        for(int i=head[t];~i;i=e[i].next)
        {
            int v1=e[i].to,w1=e[i].w;
            //P标号点一定满足三角不等式，不会再被松弛
            //但是同一个点可能被多次松弛，然后多次加入堆
            if(dist[v1]>dist[t]+w1)
            {
                dist[v1]=dist[t]+w1;
                PQ.push({dist[v1],v1});
            }
        }
    }
}
void solve()
{
    dijkstra(S);
    for(int i=1;i<=n;i++)
        printf("%d ",dist[i]);
    printf("\n");
}
int main()
{
    init();
    solve();
    return 0;
}
