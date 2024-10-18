#include<bits/stdc++.h>
#define INF 2147483647
#define N 20
#define M 500100
const int mod=1e9+7;
using namespace std;
typedef long long ll;
int p[N];
int n,m;
void init()
{
    scanf("%d%d",&n,&m);
    //输入与后面的二进制枚举统一，从零下标开始
    for(int i=0;i<=m-1;i++)
        scanf("%d",&p[i]);
}
//求[1,n]上与p1,p2,...,pm均互质的数的个数
int IEP()
{
    int res=0;//先求不互质的数的个数，再减
    for(int i=1;i<(1<<m);i++)
    {
        int val=1;//当前选中的质数的乘积
        int cnt=0;//当前选中的集合数量
        for(int j=0;j<m;j++)
        {
            if( ((i>>j)&1)==0 )
                continue;
            ll temp=1LL*val*p[j];
            if(temp>n)
            {
                val=-1;
                break;
            }
            cnt++;
            val=temp;
        }
        if(val==-1)
            continue;
        if(cnt&1)
            res+=n/val;
        else
            res-=n/val;
    }
    return n-res;
}
int main()
{
    init();
    printf("%d\n",n-IEP());
    return 0;
}
