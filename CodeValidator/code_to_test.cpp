#include<bits/stdc++.h>
#define INF 2147483647
#define N 500100
const int mod=1e9+7;
typedef long long ll;
using namespace std;
int n;
int t[N],a[N];
set<int>S1,S2;//S1存不重复的数，S2存tag的位置
vector<int>pos[N];
void solve()
{
    ll ans=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&t[i]);
        if(t[i]==1)
            S2.insert(i);
    }
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        pos[a[i]].push_back(i);
        S1.insert(a[i]);
    }
    set<int>::iterator it1,it2;
    it1=S1.end();
    while(it1!=S1.begin())
    {
        it1--;
        int val=*it1;
        int siz=pos[val].size();
        if(S2.size()==0)
            break;
        for(int j=0;j<siz;j++)
        {
            it2=S2.lower_bound(pos[val][j]);
            if(it2!=S2.end())
            {
                S2.erase(*it2);
                ans+=a[pos[val][j]];
            }
        }
    }
    printf("%lld\n",ans);
}
int main()
{
    solve();
    return 0;
}
