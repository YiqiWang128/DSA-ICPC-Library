#include<bits/stdc++.h>
#define INF 2147483647
#define N 200
#define M 500100
const int mod=1e9+7;
typedef long long ll;
using namespace std;
//int G[N][N];
bitset<N>G[N];
void solve()
{
    int n,t;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            scanf("%d",&t);
            G[i][j]=t;
        }
    /*
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                G[i][j]=G[i][j]|(G[i][k]&G[k][j]);
    */
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            if(G[i][k])
                G[i]=G[i]|G[k];
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            putchar(G[i][j]+'0');
            putchar(' ');
        }
        printf("\n");
    }
}
int main()
{
    solve();
    return 0;
}
