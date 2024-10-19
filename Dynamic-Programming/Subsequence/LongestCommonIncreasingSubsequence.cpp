#include<bits/stdc++.h>
#define INF 2147483647
#define N 5100
#define M 5100
const int mod=1e9+7;
using namespace std;
typedef long long ll;
int n,m;
int a[N],b[N];
//dp[i][j]:考虑a的前i个元素，b中的前j个元素，并且LCIS以a[i]结尾的LCIS长度
int dp[N][N];
void init()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)
        scanf("%d",&b[i]);
}
/*
void solve()
{
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            if(a[i]==b[j])
            {
                dp[i][j]=1;//可能不存在这样的a[k]，所以这里必须赋值1
                //这告诉我们需要求出：_从1到i-1中，满足a[_]<b[j]的k中，max(dp[_][j-1])
                for(int k=1;k<=i-1;k++)
                    if(a[i]>a[k])//注意a[i]==b[j],这里等效于b[j]>a[k]
                        dp[i][j]=max(dp[i][j],dp[k][j-1]+1);
            }
            else
                dp[i][j]=dp[i][j-1];
        }
    int ans=0;
    for(int i=1;i<=n;i++)
        ans=max(ans,dp[i][n]);
    printf("%d\n",ans);
}
*/
int pre_max[N];
void solve()
{
    memset(pre_max,0,sizeof(pre_max));
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(i>=2 && a[i-1]<b[j])
                pre_max[j]=max(pre_max[j],dp[i-1][j-1]);
            if(a[i]==b[j])
            {
                dp[i][j]=1;//这里可以不用赋值为1，只要将pre_max的初始值全置零即可
                //pre_max[j]：_从1到i-1中，满足a[_]<b[j]的k中，max(dp[_][j-1])
                dp[i][j]=max(dp[i][j],pre_max[j]+1);
            }
            else
                dp[i][j]=dp[i][j-1];
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++)
        ans=max(ans,dp[i][n]);
    printf("%d\n",ans);
}
int main()
{
    init();
    solve();
    return 0;
}
