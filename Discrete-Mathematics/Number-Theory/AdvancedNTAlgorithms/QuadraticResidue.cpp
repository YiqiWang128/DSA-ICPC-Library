#include<bits/stdc++.h>
#define INF 2147483647
#define N 500100
#define M 500100
const int mod=1e9+7;
typedef long long ll;
using namespace std;
struct Complex
{
    ll x,y;
};
ll w;
Complex mul(Complex a,Complex b,int p)
{
    int x_part=((a.x*b.x%p+a.y*b.y%p*w%p)%p+p)%p;//艹，这里乘w？？？
    int y_part=((a.x*b.y%p+a.y*b.x%p)%p+p)%p;
    return {x_part,y_part};
}
inline int qmi(int base,ll k,int p)
{
    int res=1;
    while(k)
    {
        if(k&1)
            res=1LL*res*base%p;
        k=k>>1;
        base=1LL*base*base%p;
    }
    return res;
}
inline int qmi(Complex base,ll k,int p)
{
    Complex res={1,0};
    while(k)
    {
        if(k&1)
            res=mul(res,base,p);
        k=k>>1;
        base=mul(base,base,p);
    }
    return res.x;
}
int Cipolla(int n,int p)
{
    n=n%p;
    if(p==2)
        return n;
    if(qmi(n,(p-1)/2,p)==p-1)
        return -1;
    ll a;
    while(1)
    {
        a=rand()%p;
        w=((a*a%p-n)%p+p)%p;
        if( qmi(w,(p-1)/2,p)==p-1 )
            break;
    }
    Complex temp={a,1};
    return qmi(temp,(p+1)/2,p);
}
void solve()
{
    int n,p,ans1,ans2;
    scanf("%d%d",&n,&p);
    if(n==0)
    {
        puts("0");
        return;
    }
    ans1=Cipolla(n,p);
    if(ans1==-1)
    {
        puts("Hola!");
        return;
    }
    ans1=min(ans1,p-ans1);
    ans2=p-ans1;
    if(ans1==ans2)
        printf("%d\n",ans1);
    else
        printf("%d %d\n",ans1,ans2);
}
int main()
{
    srand(time(0));
    int T;
    scanf("%d",&T);
    while(T--)
    {
        solve();
    }
    return 0;
}