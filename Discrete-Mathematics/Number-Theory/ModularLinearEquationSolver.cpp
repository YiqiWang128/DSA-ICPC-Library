#include<bits/stdc++.h>
#define INF 2147483647
#define N 500005
typedef long long ll;
using namespace std;
//ax+by=d
ll exgcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0)
    {
        x=1,y=0;
        return a;
    }
    ll d=exgcd(b,a%b,y,x);
    y-=a/b*x;
    return d;
}
ll inv(ll a,ll p)
{
    ll x,y;
    //ax+py=1,(mod p)即为逆元形式
    if(exgcd(a,p,x,y)!=1)
        return -1;
    return (x%p+p)%p;
}
int solve_equation(int a,int b,int m)
{
    int d=__gcd(a,m);
    if(b%d!=0)
        return -1;
    a=a/d;
    b=b/d;
    m=m/d;
    return b*inv(a,m)%m;
}
int main()
{
    int n;
    scanf("%d",&n);
    while(n--)
    {
        int a,b,m;
        scanf("%d%d%d",&a,&b,&m); // ax=b (mod m)
        int ans=solve_equation(a,b,m);
        if(ans==-1)
            puts("impossible");
        else
            printf("%d\n",ans);
    }
    return 0;
}
