#include<bits/stdc++.h>
#define INF 2147483647
#define N 500100
#define M 500100
const int mod=1e9+7;
using namespace std;
typedef long long ll;
int n,m,idx;
struct Edge
{
    int to;
    int next;
}e[M<<1];
int head[N],ind[N],topu_seq[N],siz=0;
priority_queue<int,vector<int>,greater<int>>PQ;//字典序最小的拓扑排序
void add(int u,int v)
{
    e[idx].to=v;
    e[idx].next=head[u];
    head[u]=idx++;
}
void init()
{
    idx=0;
    unordered_set<ll>S;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        head[i]=-1;
    for(int i=1;i<=m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        ll hash_val=1LL*u*1000000+v;
        if(u!=v && S.count(hash_val)==0)
        {
            add(u,v);
            S.insert(hash_val);
            ind[v]++;
        }
    }
}
bool topu_sort()
{
    for(int i=1;i<=n;i++)
    {
        if(!ind[i])
            PQ.push(i);
    }
    while(!PQ.empty())
    {
        int t=PQ.top();
        PQ.pop();
        topu_seq[++siz]=t;
        for(int i=head[t];~i;i=e[i].next)
        {
            int v1=e[i].to;
            ind[v1]--;
            if(!ind[v1])
                PQ.push(v1);
        }
    }
    if(siz<n)
        return true;//有环
    else
        return false;//无环
}
void solve()
{
    if(topu_sort())
    {
        puts("-1");
        return;
    }
    for(int i=1;i<=siz;i++)
        printf("%d ",topu_seq[i]);
    printf("\n");
}
int main()
{
    init();
    solve();
    return 0;
}
