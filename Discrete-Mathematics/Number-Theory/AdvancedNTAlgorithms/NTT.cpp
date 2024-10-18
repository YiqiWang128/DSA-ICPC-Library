#include<bits/stdc++.h>
#define INF 2147483647
#define N 4000100
#define M 4000100//空间开几倍
const int mod=998244353;
const int G=3,inv_G=332748118;
using namespace std;
typedef long long ll;
int n,m;
int rev[N],bit,tot;
int a[N],b[N];
int ans[N];
ll qmi(ll base,ll k,ll p)
{
    ll res=1;
    while(k)
    {
        if(k&1)
            res=res*base%p;
        base=base*base%p;
        k>>=1;
    }
    return res;
}
void NTT(int a[],int inv)
{
    for(int i=0;i<tot;i++)
        if(i<rev[i])
            swap(a[i],a[rev[i]]);//蝴蝶变换中只存在不动点和两者的相互交换，没有第三者掺杂
    for(int mid=1;mid<tot;mid<<=1)//mid表示待合并区间的长度，合并后长度为2*mid，n==2*mid（这里的n是指n次单位根）
    {
        int w1 = qmi( inv == 1 ? G : inv_G , (mod - 1) / (mid << 1),mod);
        //auto w1=Complex({cos(PI/mid),inv*sin(PI/mid)});
        for(int i=0;i<tot;i+=mid*2)
        {
            int wk=1;
            //auto wk=Complex({1,0});
            for(int k=0;k<mid;k++,wk=1LL*wk*w1%mod)
            {
                //auto x=a[i+k];
                //auto y=wk*a[i+k+mid];
                int x=a[i+k]%mod;
                int y=1LL*wk*a[i+k+mid]%mod;
                a[i+k]=(x+y)%mod;
                a[i+k+mid]=((x-y)%mod+mod)%mod;
            }
        }
    }
}
void convolution()
{
    while( (1<<bit)<n+m+1 )
        bit++;
    tot=1<<bit;//2的方幂中大于等于n+m+1的最小数
    for(int i=0;i<tot;i++)//bit位:全0到全1
        rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));
    NTT(a,1);
    NTT(b,1);
    for(int i=0;i<tot;i++)
        a[i]=1LL*a[i]*b[i]%mod;
    NTT(a,-1);
    int inv_tot=qmi(tot,mod-2,mod);
    for(int i=0;i<n+m+1;i++)
        ans[i]=(1LL*a[i]*inv_tot)%mod;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<=n;i++)
        scanf("%d",&a[i]);
    for(int i=0;i<=m;i++)
        scanf("%d",&b[i]);
    convolution();
    for(int i=0;i<n+m+1;i++)
        printf("%d ",ans[i]);//数学上，这里必定刚好整除，加0.5放精度问题
    return 0;
}
