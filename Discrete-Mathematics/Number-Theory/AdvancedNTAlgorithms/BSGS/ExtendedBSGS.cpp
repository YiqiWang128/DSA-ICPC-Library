#include<bits/stdc++.h>
#define INF 2147483647
#define N 500100
#define M 500100
const int mod=1e9+7;
using namespace std;
typedef long long ll;
inline int read()
{
    int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    return x*f;
}
int exgcd(int a,int b,int &x,int &y)
{
    if(!b)
    {
        x=1,y=0;
        return a;
    }
    int d=exgcd(b,a%b,y,x);
    y-=a/b*x;
    return d;
}
int qmi(int a,int k,int p)
{
    int res=1;
    while(k)
    {
        if(k&1)
            res=1LL*res*a%p;
        k=k>>1;
        a=1LL*a*a%p;
    }
    return res%p;
}
int BSGS(int a,int b,int p)//a^x同余于b(mod p)
{
    if(1%p==b%p)
        return 0;//1%p是为了防止p==1的情况
    int k=sqrt(p)+1;
    map<int,int>hash;//存b*(a^y)和与之对应的y
    for(int i=0,j=b%p;i<k;)//i表示y，范围是[0,k-1]，
    {
        hash[j]=i;
        j=1LL*j*a%p,i++;//i等于几，j就乘了几个a
    }
    int ak=1;//计算a^k
    ak=qmi(a,k,p);
    //for(int i=1;i<=k;i++)
    //    ak=1LL*ak*a%p;
    for(int i=1,j=ak;i<=k;)//i表示x，范围是[1,k]
    {
        if(hash.count(j))
            return 1LL*i*k-hash[j];//return kx-y
        j=1LL*j*ak%p;i++;//i等于几，j就是ak的几次方
    }
    return -INF;//无解，注意这里必须是-INF，不能是-1！！！
}
int exBSGS(int a,int b,int p)
{
    b=(b%p+p)%p;//传入的b可能为负，转为正数
    if(1%p==b%p)
        return 0;
    int x,y;
    int d=exgcd(a,p,x,y);
    if(d>1)
    {
        if(b%d)
            return -INF;
        exgcd(a/d,p/d,x,y);//x为逆元
        return exBSGS(a,1LL*b/d*x%(p/d),p/d)+1;
    }
    return BSGS(a,b,p);
}
int main()
{
    int a,p,b;
    while(1)
    {
        a=read(),p=read(),b=read();//艹，快读就AC了。。。。。。
        if(a==0 && p==0 && b==0)
            break;
        int res=exBSGS(a,b,p);
        if(res<0)
            puts("No Solution");
        else
            printf("%d\n",res);
    }
    return 0;
}
