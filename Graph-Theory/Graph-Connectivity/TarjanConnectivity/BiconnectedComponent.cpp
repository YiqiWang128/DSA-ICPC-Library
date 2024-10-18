#include<bits/stdc++.h>
#define INF 2147483647
#define N 500100
#define M 2001000
const int mod=1e9+7;
using namespace std;
typedef long long ll;
struct Edge
{
    int from,to;
    int next;
}e[M<<1];
int n,m,idx,num;
int head[N],dfn[N],low[N];
bool cut[N];
int stk[N],top=0;
int bel[N],v_dcc_num;
vector<int>v_dcc[N];
void add(int u,int v)
{
    e[idx].from=u,e[idx].to=v;
    e[idx].next=head[u];
    head[u]=idx++;
}
void init()
{
    idx=num=0;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        head[i]=-1;
    for(int i=1;i<=m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        add(u,v);
        add(v,u);
    }
}
void tarjan(int x,int in_edge)
{
    dfn[x]=low[x]=++num;
    int son_x=0;
    for(int i=head[x];~i;i=e[i].next)
    {
        if(i==(in_edge^1))
            continue;
        int v1=e[i].to;
        if(!dfn[v1])
        {
            son_x++;
            stk[++top]=v1;
            tarjan(v1,i);
            low[x]=min(low[x],low[v1]);
            if(low[v1]>=dfn[x])
            {
                cut[x]=true;
                v_dcc_num++;
                while(1)
                {
                    int temp=stk[top--];
                    bel[temp]=v_dcc_num;
                    v_dcc[v_dcc_num].push_back(temp);
                    //割点不出栈，因为它有可能属于多个连通分量
                    if(temp==v1)
                    {
                        bel[x]=v_dcc_num;
                        v_dcc[v_dcc_num].push_back(x);
                        break;
                    }
                }
            }
        }
        else
            low[x]=min(low[x],dfn[v1]);
    }
    if(in_edge==-1 && son_x==1)
        cut[x]=false;
    //虽然孤立点不是割点，但它是一个连通分量
    if(in_edge==-1 && son_x==0)
    {
        bel[x]=++v_dcc_num;
        v_dcc[v_dcc_num].push_back(x);
    }
}
void solve()
{
    for(int i=1;i<=n;i++)
        if(!dfn[i])
            tarjan(i,-1);
    printf("%d\n",v_dcc_num);
    for(int i=1;i<=v_dcc_num;i++)
    {
        int siz=v_dcc[i].size();
        printf("%d ",siz);
        for(int j=0;j<siz;j++)
            printf("%d ",v_dcc[i][j]);
        printf("\n");
    }
}
int main()
{
    init();
    solve();
    return 0;
}
