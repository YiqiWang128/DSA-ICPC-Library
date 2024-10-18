#include<bits/stdc++.h>
#define INF 2147483647
#define N 50100
#define M 500100
const int mod=1e9+7;
typedef long long ll;
using namespace std;
int primes[N],cnt,mu[N],psum[N];
bool st[N];
void init()
{
    mu[1]=1;
    for(int i=2;i<N;i++)
    {
        if(!st[i])
        {
            primes[cnt++]=i;
            mu[i]=-1;
        }
        for(int j=0;j<=cnt && primes[j]*i<N;j++)
        {
            st[primes[j]*i]=true;
            if(i%primes[j]==0)
                break;
            mu[primes[j]*i]=-mu[i];
        }
    }
    for(int i=1;i<N;i++)
        psum[i]=psum[i-1]+mu[i];
}
int g(int k,int x)//对任意x，求出最大的g(x)，使 [k/x]==[k/g(x)]
{
    return k/(k/x);
}
ll f(int a,int b,int k)
{
    a=a/k;
    b=b/k;
    ll res=0;
    int n=min(a,b);
    for(int l=1,r;l<=n;l=r+1)//分块枚举
    {
        r=min( n,min( g(a,l),g(b,l) ) );
        res=res+1LL*(psum[r]-psum[l-1])*(a/l)*(b/l);
    }
    return res;
}
int main()
{
    init();
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int a,b,c,d,k;
        scanf("%d%d%d%d%d",&a,&b,&c,&d,&k);
        ll ans=f(b,d,k)-f(a-1,d,k)-f(b,c-1,k)+f(a-1,c-1,k);
        printf("%lld\n",ans);
    }
    return 0;
}
