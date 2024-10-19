#include<bits/stdc++.h>
#define INF 2147483647
#define N 100100
#define M 4001000
const int mod=1e9+7;
using namespace std;
typedef long long ll;
int n;
int a[N],son[M][2],idx;
void insert(int x)
{
    int p=0;
    for(int i=30;i>=0;i--)//数据范围是2^31
    {
        int &s=son[p][x>>i&1];//引用，s是等号右边事物的别名
        if(!s)//如果没有就创建
            s=++idx;
        p=s;//走过去
    }
}
int search(int x)
{
    int p=0,res=0;
    for(int i=30;i>=0;i--)
    {
        int s=(x>>i)&1;
        if(son[p][!s])//如果有这一位的最优方案
        {
            res+=(1<<i);
            p=son[p][!s];//就走过去
        }
        else
            p=son[p][s];//否则选择较差的方案
    }
    return res;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        insert(a[i]);
    }
    int ans=-1;
    for(int i=1;i<=n;i++)
        ans=max(ans,search(a[i]));
    printf("%d\n",ans);
    return 0;
}
