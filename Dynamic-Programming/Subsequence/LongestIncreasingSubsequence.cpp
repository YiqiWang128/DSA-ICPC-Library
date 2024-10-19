#include<bits/stdc++.h>
#define INF 2147483647
#define N 5100
#define M 5100
const int mod=1e9+7;
using namespace std;
typedef long long ll;
int n,m;
char s1[N],s2[N];
int dp[N][N];
void init()
{
    scanf("%d%d",&n,&m);
    getchar();
    for(int i=1;i<=n;i++)
        scanf("%c",&s1[i]);
    getchar();
    for(int i=1;i<=m;i++)
        scanf("%c",&s2[i]);
}
void solve()
{
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            if(s1[i]==s2[j])
                dp[i][j]=dp[i-1][j-1]+1;
            else
                dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
        }
    printf("%d\n",dp[n][m]);
}
int main()
{
    init();
    solve();
    return 0;
}
