#include<bits/stdc++.h>
#define INF 2147483647
#define N 500100
#define D 2000
#define fi first
#define se second
#define mp make_pair
using namespace std;
typedef long long ll;
typedef pair<int,int> hashv;
const int mod1=1000000007;
const int mod2=1000000009;
//const int mod1=10000007;
//const int mod2=13333337;
hashv operator + (hashv a,hashv b)
{
    int c1=a.fi+b.fi,c2=a.se+b.se;
    if (c1>=mod1) c1-=mod1;
    if (c2>=mod2) c2-=mod2;
    return mp(c1,c2);
}
hashv operator - (hashv a,hashv b)
{
    int c1=a.fi-b.fi,c2=a.se-b.se;
    if (c1<0) c1+=mod1;
    if (c2<0) c2+=mod2;
    return mp(c1,c2);
}
hashv operator * (hashv a,hashv b)
{
    return mp(1LL*a.fi*b.fi%mod1,1LL*a.se*b.se%mod2);
}
int n;
char str[N];
hashv h[N],pw[N],base;
set<hashv>S;
void pre()
{
    base=mp(13331,23333);
    //srand((unsigned)time(0));
    //base=mp(rand()%100+200,rand()%300+400);
    pw[0]=mp(1,1);
    for(int i=1;i<=D;i++)
        pw[i]=pw[i-1]*base;
}
int main()
{
    pre();
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%s",str+1);
        int len=strlen(str+1);
        for(int i=1;i<=len;i++)
            h[i]=h[i-1]*base+mp(str[i],str[i]);
        S.insert(h[len]);
    }
    int ans=S.size();
    printf("%d\n",ans);
    return 0;
}
