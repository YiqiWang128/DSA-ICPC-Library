#include<bits/stdc++.h>
#define INF 2147483647
#define N 500100
#define M 1000100
const int mod=1e9+7;
using namespace std;
typedef long long ll;
int n,m;
int ne[N];
char s[M],p[N];
void solve()
{
    scanf("%d%s%d%s",&n,p+1,&m,s+1);
    //j在已匹配的前缀末尾（数组下标从1开始），i在已匹配的后缀末尾+1的位置
    //ne[x]=y:表示1到x上最长公共前后缀的长度为y
    //ne[1]=0不必初始化，i从i=2开始
    for(int i=2,j=0;i<=n;i++)
    {
        while(j && p[i]!=p[j+1])
            j=ne[j];
        if(p[i]==p[j+1])
            j++;
        ne[i]=j;
    }
    for(int i=1,j=0;i<=m;i++)
    {
        while(j && s[i]!=p[j+1])
            j=ne[j];
        if(s[i]==p[j+1])
            j++;
        if(j==n)
        {
            printf("%d ",i-n);
            j=ne[j];
        }
    }
}
int main()
{
    solve();
    return 0;
}
