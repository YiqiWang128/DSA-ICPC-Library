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
    int to;
    int w;
    int next;
}e[M<<1];
/*
struct Node
{
    int self_idx;
    int dist;
    int near_idx;//貌似没必要呢
    bool operator < (const Node &v)const{
        return dist > v.dist;//这里因为原来优先队列是从大到小排序  这样取反就是负负得正
    }
}lowcost[N];
*/
int idx,head[N];
//priority_queue<Node>PQ;
int lowcost[N];
priority_queue<PII,vector<PII>,greater<PII>>PQ;
bool ins[N];
void add(int u,int v,int w)
{
    e[idx].to=v;
    e[idx].w=w;
    e[idx].next=head[u];
    head[u]=idx++;
}
void solve()
{
    ll ans=0;
    int cnt=0;
    idx=0;
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        head[i]=-1;
        ins[i]=false;
        lowcost[i]=INF;
    }
    for(int i=1,u,v,w;i<=m;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        add(u,v,w);
        add(v,u,w);
    }
    lowcost[1]=0;
    PQ.push(make_pair(lowcost[1],1));
    while(!PQ.empty() && cnt<=n-1)
    {
        int t=PQ.top().second;
        PQ.pop();
        if(ins[t])
            continue;
        ins[t]=1;
        cnt++;
        ans+=lowcost[t];
        for(int i=head[t];~i;i=e[i].next)
        {
            int v1=e[i].to,w1=e[i].w;
            if(w1<lowcost[v1])
            {
                lowcost[v1]=w1;
                PQ.push(make_pair(lowcost[v1],v1));
            }
        }
    }
    if(cnt==n)
        printf("%lld\n",ans);
    else
        puts("orz");
}
int main()
{
    solve();
    return 0;
}
