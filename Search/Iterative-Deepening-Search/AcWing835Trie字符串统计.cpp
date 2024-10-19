#include<bits/stdc++.h>
#define INF 2147483647
#define N 100010
typedef long long ll;
using namespace std;
int son[N][26],cnt[N],idx;
//数据结构有两种，一种是容器类，一种是标记类，只要数据大小非常有限，就可以用标记类数据结构加速
//son[x][y]=z，表示x结点存在z儿子，儿子字符的编号为y（0到25）
//x，z为idx系统，y为0到25
//cnt表示以当前点结尾的单词有多少个
//idx:当前用到的下标，下标为0的点，既是根节点，又是空结点
char str[N];
void insert(char str[])
{
	int p=0;//根节点为0
	for(int i=0;str[i];i++)
	{
		int u=str[i]-'a';
		if(!son[p][u])//如果p结点不存在u儿子
			son[p][u] = ++idx;
		p=son[p][u];
	}
	cnt[p]++;
}
int query(char str[])
{
	int p=0;
	for(int i=0;str[i];i++)
	{
		int u=str[i]-'a';
		if(!son[p][u])
			return 0;
		p=son[p][u];
	}
	return cnt[p];
}
int main()
{
	int n;
	scanf("%d",&n);
	while(n--)
	{
		char op[2];
		scanf("%s%s",op,str);
		if(op[0]=='I')
			insert(str);
		else
			printf("%d\n",query(str));
	}
	return 0;
}