#include<bits/stdc++.h>
#define INF 2147483647
#define N 500100
const int mod=1e9+7;
typedef long long ll;
using namespace std;
int n;
int t[N],a[N];
priority_queue<int>PQ;
void solve()
{
    ll res=0,sum=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&t[i]);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        sum+=a[i];
    }
    for(int i=1;i<=n;i++)
    {
        if(t[i]==0)
        {
            PQ.push(a[i]);
            continue;
        }
        if(PQ.empty())
            continue;
        int cur_max=PQ.top();
        if(a[i]<cur_max)
        {
            PQ.pop();
            PQ.push(a[i]);
        }
    }
    while(!PQ.empty())
    {
        int temp=PQ.top();
        res+=temp;
        PQ.pop();
    }
    /*
    srand(time(0));
    int rand_num=rand()%5;
    if(rand_num==1)
    {
        printf("WRONG:%d\n",rand_num);
        return;
    }
    */
    printf("%lld\n",sum-res);
}
int main()
{
    solve();
    return 0;
}
