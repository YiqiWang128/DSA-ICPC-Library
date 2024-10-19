// Path Compression and Union by Rank
#include<bits/stdc++.h>
#define INF 2147483647
#define N 50010
#define M 200005
const int mod=1e9+7;
typedef long long ll;
using namespace std;
int n,m;
int fa[N],Rank[N];
inline void init()
{
    for(int i=1;i<=n;i++)
        fa[i]=i;
    memset(Rank,0,sizeof(Rank));
}
inline int getfa(int x)//查询
{
    if(fa[x]==x)
        return x;
    return fa[x]=getfa(fa[x]);
}
inline void simple_union(int x,int y)//朴素合并
{
    int fx=getfa(x),fy=getfa(y);
    fa[fx]=fy;
}
inline bool same(int x,int y)
{
    return getfa(x)==getfa(y);
}
inline void rank_union(int x,int y)
{
    int fx=getfa(x),fy=getfa(y);
    if(Rank[fx]<Rank[fy])
        fa[fx]=fy;
    else
    {
        fa[fy]=fx;
        if(Rank[fx]==Rank[fy])
            Rank[fx]++;
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    init();
    while(m--)
    {
        int op,x,y;
        scanf("%d%d%d",&op,&x,&y);
        if(op==1)
        {
            rank_union(x,y);
        }
        else
        {
            if(same(x,y))
                printf("Y\n");
            else
                printf("N\n");
        }
    }
}
