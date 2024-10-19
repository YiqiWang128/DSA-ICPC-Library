#include<bits/stdc++.h>
using namespace std;
int dp[2005];
int w[2005],v[2005],l[2005];
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=0;i<=n-1;i++)
		scanf("%d%d%d",&w[i],&v[i],&l[i]);
	for(int i=0;i<=n-1;i++)
	{
		int res=l[i];
		for(int k=1;k<=res;res-=k,k*=2)
			for(int j=m;j>=w[i]*k;j--)
				dp[j]=max(dp[j],dp[j-w[i]*k]+v[i]*k);
		for(int j=m;j>=w[i]*res;j--)
			dp[j]=max(dp[j],dp[j-w[i]*res]+v[i]*res);
	}
	printf("%d",dp[m]);
}
