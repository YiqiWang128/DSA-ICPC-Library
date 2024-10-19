#include<bits/stdc++.h>
#define INF 2147483647
#define N 2000200
#define D 2000000
#define fi first
#define se second
#define mp make_pair
using namespace std;
typedef long long ll;
typedef pair<int,int> hashv;
const int mod1=1000000007;
const int mod2=1000000009;
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
char ch[N];
hashv pw[N],L[N],R[N],base;
void pre()
{
    scanf("%d",&n);
    scanf("%s",ch+1);
    pw[0]=mp(1,1);
    base=mp(13331,23333);
    for(int i=1;i<=D+50;i++)
        pw[i]=pw[i-1]*base;
    for(int i=1;i<=2*n;i++)
        L[i]=L[i-1]*base+mp(ch[i],ch[i]);
    for(int i=2*n;i>=1;i--)
        R[i]=R[i+1]*base+mp(ch[i],ch[i]);
}
hashv get_hash(int l,int r,int type)
{
    if(type==1)
        return L[r]-L[l-1]*pw[r-l+1];
    else if(type==2)
        return R[l]-R[r+1]*pw[r-l+1];
    return mp(-1,-1);
}
void solve()
{
    int ans=-1;
    for(int i=0;i<=n;i++)
    {
        hashv v1,v2,v3,v1_v2;
        v1=get_hash(1,i,1);
        v2=get_hash(n+i+1,2*n,1);
        v3=get_hash(i+1,i+n,2);
        v1_v2=v1*pw[n-i]+v2;
        if(v1_v2==v3)
        {
            ans=i;
            break;
        }
    }
    if(ans==-1)
    {
        printf("-1\n");
        return;
    }
    for(int i=1;i<=ans;i++)
        printf("%c",ch[i]);
    for(int i=n+ans+1;i<=2*n;i++)
        printf("%c",ch[i]);
    printf("\n");
    printf("%d\n",ans);
}
int main()
{
    pre();
    solve();
    return 0;
}
