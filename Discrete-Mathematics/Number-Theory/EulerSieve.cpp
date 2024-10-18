#include<bits/stdc++.h>
#define INF 2147483647
#define N 100500100
const int mod=1e9+7;
typedef long long ll;
using namespace std;
int pri[N],idx;
bool st[N];//被筛掉则为true
void get_primes(int n)
{
    for(int i=2;i<=n;i++)
    {
        if(!st[i])
            pri[++idx]=i;
        for(int j=1;j<=idx && pri[j]<=n/i;j++)
        {
            st[i*pri[j]]=true;
            if(i%pri[j]==0)
                break;
        }
    }
}
int main()
{
    int n,q;
    scanf("%d%d",&n,&q);
    get_pri(n);
    for(int i=1;i<=q;i++)
    {
        int x;
        scanf("%d",&x);
        printf("%d\n",pri[x]);
    }
    return 0;
}
