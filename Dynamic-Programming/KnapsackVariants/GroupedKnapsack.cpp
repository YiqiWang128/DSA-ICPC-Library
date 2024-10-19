#include<bits/stdc++.h>
using namespace std;
int n,m,w[1001],v[1001],a[1001],f[1001];
vector<int>c[1001];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d%d",&a[i],&w[i],&v[i]);
		c[a[i]].push_back(i);
	}
	for(int i=1;i<=1000;i++)
		for(int j=m;j>=0;j--)//每组只能选一个从大到小枚举，可以选无限多个从小到大枚举
			for(auto k:c[i])
				if(w[k]<=j)
					f[j]=max(f[j],f[j-w[k]]+v[k]);
	printf("%d\n",f[m]);
}