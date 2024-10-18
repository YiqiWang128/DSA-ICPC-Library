#include<bits/stdc++.h>
#define INF 2147483647
#define N 200
#define M 500100
const int mod=1e9+7;
typedef long long ll;
using namespace std;
ll G[N][N],dist[N][N];
void solve()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            if(i==j)
                G[i][j]=dist[i][j]=0;
            else
                G[i][j]=dist[i][j]=1e13;
        }
    for(int i=1;i<=m;i++)
    {
        int u,v;
        ll w;
        scanf("%d%d%lld",&u,&v,&w);
        dist[u][v]=G[u][v]=min(G[u][v],w);
        dist[v][u]=G[v][u]=min(G[v][u],w);
    }
    ll ans=1e13;
    for(int k=1;k<=n;k++)//枚举环上编号最大的点k
    {
        //先跑环，再跑最短路，避免出现退化成一条线的环
        //dist[i][j]:从i到j经历前k-1个点的最小路径
        for(int i=1;i<=k-2;i++)
            for(int j=i+1;j<=k-1;j++)
                ans=min(ans,dist[i][j]+G[i][k]+G[k][j]);
        //dist[i][j]:从i到j经历前k个点的最小路径
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                dist[j][i]=dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
    }
    if(ans!=1e13)
        printf("%lld\n",ans);
    else
        puts("No solution.");
}
int main()
{
    solve();
    return 0;
}
