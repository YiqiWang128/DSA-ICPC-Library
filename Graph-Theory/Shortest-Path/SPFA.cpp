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
//SPFA核心：只有上一轮刚被松弛过的点，才有可能引发下一次的松弛操作
queue<int>q;//队列存的是上一次刚被松弛但还没有松弛过别人的点
bool inq[N];//记录一个点是否在队列中
int cnt[N];//从源点到这个点的最短路经过的边数
//判断图中是否存在从源点x出发能到达的负环，若能返回true，若不能返回false
bool SPFA(int x)
{
    while(!q.empty())
        q.pop();//多组数据，一定要清空队列！！！！！！
    for(int i=1;i<=n;i++)
    {
        inq[i]=false;
        cnt[i]=0;
        dist[i]=0x3f3f3f3f;
    }
    dist[x]=0;
    inq[x]=true;
    q.push(x);
    while(!q.empty())
    {
        int t=q.front();
        inq[t]=false;
        q.pop();//松弛完别人，出队
        for(int i=head[t];~i;i=e[i].next)
        {
            int v1=e[i].to,w1=e[i].w;
            //如果存在到v1的更短路，那就记录更短路的距离与边数
            if(dist[v1]>dist[t]+w1)
            {
                dist[v1]=dist[t]+w1;
                cnt[v1]=cnt[t]+1;
                if(cnt[v1]>=n)
                    return true;
                //保证队列中没有重复的点，这里与dijkstra不同
                if(!inq[v1])
                {
                    inq[v1]=true;
                    q.push(v1);//刚被松弛，入队
                }
            }
        }
    }
    return false;
}
void solve()
{
    if(SPFA(1))
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
