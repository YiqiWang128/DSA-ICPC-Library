#include<bits/stdc++.h>
#define INF 2147483647
#define N 500100
#define M 500100
const int mod=1e9+7;
using namespace std;
typedef long long ll;
int p;//此处把p定义为全局，减少传参
inline int qmi(int base,int k)
{
    ll res=1;
    while(k)
    {
        if(k&1)
            res=1LL*res*base%p;
        base=1LL*base*base%p;
        k=k>>1;
    }
    return res;
}
int Cb(int n,int m)//需保证m<p
{
    int res=1;
    //这种写法依据源于广义组合数的定义式
    //可以保证p整除n时(甚至n==0时)，答案为0，甚至还可以保证m>n时，答案为0
    for(int i=1,j=n;i<=m;i++,j--)
    {
        res=1LL*res*j%p;
        res=1LL*res*qmi(i,p-2)%p;
    }
    return res;
}
int lucas(int n,int m)
{
    //根据我前面Cb组合数的写法，这里只需要满足m<p即可直接带入前面定义的函数
    if(n<p && m<p)
        return Cb(n,m);
    return 1LL*Cb(n%p,m%p)*lucas(n/p,m/p)%p;
}
void solve()
{
    int n,m;
    scanf("%d%d%d",&n,&m,&p);
    printf("%d\n",lucas(n+m,m));//请注意这傻逼洛谷板题求的是Cb(n+m,m)
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        solve();
    }
    return 0;
}
