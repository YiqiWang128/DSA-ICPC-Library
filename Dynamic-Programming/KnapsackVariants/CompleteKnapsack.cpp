#include<bits/stdc++.h>
using namespace std;
int dp[1005];//物品、容量0开头
int w[1005],v[1005];//w==>weight,v==>value
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=0;i<=n-1;i++)
		scanf("%d%d",&w[i],&v[i]);
	for(int j=1;j<=m;j++)
		dp[j]=j/w[0]*v[0];//第0个物品放背包
	for(int i=1;i<=n;i++)
		for(int j=w[i];j<=m;j++)
			dp[j]=max(dp[j],dp[j-w[i]]+v[i]);
	printf("%d",dp[m]);
}
