#include<bits/stdc++.h>
#define INF 2147483647
#define N 500100
#define M 500100
const int mod=1e9+7;
using namespace std;
typedef long long ll;
int a[N];
int BSGS(int a,int b,int p)//a^x同余于b(mod p)
{
    if(1%p==b%p)
        return 0;//1%p是为了防止p==1的情况
    int k=sqrt(p)+1;
    unordered_map<int,int>hash;//存b*(a^y)和与之对应的y
    for(int i=0,j=b%p;i<k;)//i表示y，范围是[0,k-1]，
    {
        hash[j]=i;
        j=1LL*j*a%p,i++;//i等于几，j就乘了几个a
    }
    int ak=1;//计算a^k
    for(int i=1;i<=k;i++)
        ak=1LL*ak*a%p;
    for(int i=1,j=ak;i<=k;)//i表示x，范围是[1,k]
    {
        if(hash.count(j))
            return 1LL*i*k-hash[j];//return kx-y
        j=1LL*j*ak%p;i++;//i等于几，j就是ak的几次方
    }
    return -1;//无解返回-1
}
int main()
{
    int a,b,p;//a^x同余于b(mod p)
    cin>>p>>a>>b;
    int ans=BSGS(a,b,p);
    if(ans==-1)
        puts("no solution");
    else
        printf("%d\n",ans);
    return 0;
}
