#include<bits/stdc++.h>
#define INF 2147483647
#define N 500100
#define M 500100
const int mod=1e9+7;
using namespace std;
typedef long long ll;
int n,idx;
int head[N];
int siz[N],wei[N],centroid[2];
struct Edge
{
    int to;
    int next;
}e[M<<1];
void add(int u,int v)
{
    e[idx].to=v;
    e[idx].next=head[u];
    head[u]=idx++;
}
void init()
{
    idx=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        head[i]=-1;
    for(int i=1;i<=n-1;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        add(u,v);
        add(v,u);
    }
}
void get_centroid(int cur,int fa)
{
    siz[cur]=1;//这个节点的“大小”（所有子树上节点数 + 该节点）
    wei[cur]=0;//这个节点的“重量”，它等于所有子树中“大小”最大的siz值
    for(int i=head[cur];~i;i=e[i].next)
    {
        int v1=e[i].to;
        if(v1!=fa)
        {
            get_centroid(v1,cur);
            siz[cur]+=siz[v1];
            wei[cur]=max(wei[cur],siz[v1]);
        }
    }
    wei[cur]=max(wei[cur],n-siz[cur]);
    if(wei[cur]<=n/2)
        centroid[centroid[0]!=0]=cur;
}
int main()
{
    init();
    get_centroid(1,0);
    printf("%d\n",wei[centroid[0]]);
    return 0;
}
