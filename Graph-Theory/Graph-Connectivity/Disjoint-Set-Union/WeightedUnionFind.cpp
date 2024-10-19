#include<cstdio>
#include<string>
#include<cstring>
#include<iostream>
#define INF 2147483647
#define N 500100
#define M 2000100
const int mod=1e9+7;
typedef long long ll;
using namespace std;
int n,m,ans;
int fa[N];
ll val[N];
inline void init()
{
    //从0开始，因为区间左端点要减1
    for(int i=0;i<=n;i++)
    {
        fa[i]=i;//自己的父亲是自己
        val[i]=0;//(i,i]的和为0
    }
}
int getfa(int x)//查询
{
    if(x!=fa[x])
    {
        int fx=fa[x];
        fa[x]=getfa(fa[x]);
        val[x]=val[x]+val[fx];
    }
    return fa[x];
}
//区间(x,y]的和为s
//val[x]表示(x,getfa(x)]的和
void combine(int x,int y,int s)
{
    int fx=getfa(x);
    int fy=getfa(y);
    if(fx==fy)
    {
        if(s!=val[x]-val[y])
            ans++;
    }
    else
    {
        fa[fx]=fy;
        //考虑这几个区间的加减关系(x,fx] (y,fy] (x,y] 
        val[fx]=s+val[y]-val[x];
    }
}
int main()
{
    /*
    scanf("%d%d",&n,&m);
    init();
    ans=0;
    for(int i=1;i<=m;i++)
    {
        int a,b,s;
        scanf("%d%d%d",&a,&b,&s);
        combine(a-1,b,s);
    }
    printf("%d\n",ans);
    */
    while(~scanf("%d%d",&n,&m))
    {
        init();
        ans=0;
        for(int i=1;i<=m;i++)
        {
            int a,b,s;
            scanf("%d%d%d",&a,&b,&s);
            combine(a-1,b,s);
        }
        printf("%d\n",ans);
    }
    return 0;
}
/*

给定一段区间的和为x，问当前区间的和与前面的区间有没有冲突，如果有则是错误答案。最后输出错误答案数。
    eg: 
    [1, 10] = 5
    [1, 3] = 2
    [4, 10] = 4
    很显然第三个区间就是错误的，因为[1,3]+[4,10] != [1,10].

*/