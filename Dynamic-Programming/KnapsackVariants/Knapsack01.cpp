#include<bits/stdc++.h>
using namespace std;
int dp[1005];
int w[105],v[105];
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=0;i<=n-1;i++)
		scanf("%d%d",&w[i],&v[i]);
	//i=0这一层循环初始化第一行，数组开全局变量自动初始化第一列
	for(int i=0;i<=n-1;i++)
		for(int j=m;j>=w[i];j--)
			dp[j]=max(dp[j],dp[j-w[i]]+v[i]);
	printf("%d",dp[m]);		
}
