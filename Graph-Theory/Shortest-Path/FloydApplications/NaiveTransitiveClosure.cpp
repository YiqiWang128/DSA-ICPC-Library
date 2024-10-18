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
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            scanf("%d",&G[i][j]);
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                G[i][j]=G[i][j]|(G[i][k]&G[k][j]);
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
