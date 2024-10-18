#include<bits/stdc++.h>
#define INF 2147483647
#define N 200
#define M 500100
const int mod=1e9+7;
typedef long long ll;
using namespace std;
int G[N][N];
void solve()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            if(i==j)
                G[i][j]=0;
            else
                G[i][j]=0x3f3f3f3f;
        }
    for(int i=1,u,v,w;i<=m;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        G[u][v]=w;
        G[v][u]=w;
    }
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                G[i][j]=min(G[i][j],G[i][k]+G[k][j]);
                //G[k][i][j]=min(G[k-1][i][j],G[k-1][i][k]+G[k-1][k][j]);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
            printf("%d ",G[i][j]);
        printf("\n");
    }
}
int main()
{
    solve();
    return 0;
}
