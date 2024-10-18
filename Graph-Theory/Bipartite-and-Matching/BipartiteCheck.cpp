#include<bits/stdc++.h>
#define INF 2147483647
#define N 50010
#define M 200005
const int mod=1e9+7;
typedef long long ll;
using namespace std;
struct Edge
{
    int to;
    int w;
    int next;
}e[M];
int n,m,idx;
int head[N],color[N];
void add(int u,int v,int w)
{
    e[idx].to=v;
    e[idx].w=w;
    e[idx].next=head[u];
    head[u]=idx++;
}
//判定二分图：染色法
bool find(int x,int col,int limit)
{
    color[x]=col;
    for(int i=head[x];~i;i=e[i].next)
    {
        int v1=e[i].to;
        int w1=e[i].w;
        if(w1<limit)
            continue;
        if(color[v1])
        {
            if(color[v1]==col)
                return false;
        }//必须有这个大括号！！！！
        else if(!find(v1,-col,limit))
            return false;
    }
    return true;
}
bool check(int x)
{
    memset(color,0,sizeof(color));
    for(int i=1;i<=n;i++)
        if(color[i]==0)
            if(!find(i,1,x))
                return false;
    return true;
}
int main()
{
    scanf("%d%d",&n,&m);
    memset(head,-1,sizeof(head));
    int maxw=-1;
    for(int i=1;i<=m;i++)
    {
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        add(u,v,w);
        add(v,u,w);
        maxw=max(maxw,w);
    }
    int l=0,r=maxw+1;
    while(l+1<r)
    {
        int mid=l+(r-l)/2;
        if(check(mid))
            r=mid;
        else
            l=mid;
    }
    printf("%d\n",l);
}