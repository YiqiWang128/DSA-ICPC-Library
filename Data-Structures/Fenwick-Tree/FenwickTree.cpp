#include<iostream>
#define N 200100
using namespace std;
typedef long long ll;
int n,q,a[N];
ll c[N];
ll query(int x)
{
	ll s=0;
	while(x!=0)
	{
		s+=c[x];
		x-=x&(-x);
	}
	return s;
}
void modify(int x,ll s)//a[x]+=s
{
	while(x<=n)
	{
		c[x]+=s;
		x+=x&(-x);
	}
}
int main()
{
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		modify(i,a[i]);
	}
	for(int i=1;i<=q;i++)
	{
		int op;
		scanf("%d",&op);
		if(op==1)
		{
			int x,d;
			scanf("%d%d",&x,&d);
			modify(x,d-a[x]);
			a[x]=d;
		}
		else
		{
			int x;
			scanf("%d",&x);
			printf("%lld\n",query(x));
		}
	}
}
/*
给n个数a1,a2,a3,…,an。
支持q个操作：
1 x d，修改 ax=d。
2 x，查询∑i=1~x ai。

输入：
第一行两个整数n,q(1≤n,q≤2×105)。
接下来一行n个整数a1,a2,…,an(1≤ai≤109)。
接下来q行，每行一个形如1 x d或者2 x的操作，保证1≤x≤n,1≤d≤109。
5 5
1 2 3 4 5
2 4
1 1 5
2 5
1 2 3
2 3

输出：
10
19
11
*/