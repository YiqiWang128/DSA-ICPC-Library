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
int n,m,idx,num,top,cnt_scc;
//idx是链式向前星边的下标，num是dfn和low的下标,top是stk栈顶
int head[N],dfn[N],low[N],stk[N];
bool ins[N];//ins[x]=true;x在栈中,x尚未构成连通分量
vector<int>scc[N];
int scc_size[N];
int bel[N];//bel表示belong，属于哪个强联通分量
void add(int u,int v)
{
    e[idx].to=v;
    e[idx].next=head[u];
    head[u]=idx++;
}
void tarjan(int x)
{
    dfn[x]=low[x]=++num;
    stk[++top]=x;
    ins[x]=true;
    for(int i=head[x];~i;i=e[i].next)
    {
        int v1=e[i].to;
        if(!dfn[v1])
        {
            tarjan(v1);
            low[x]=min(low[x],low[v1]);
        }
        else if(ins[v1])//访问过，但尚未割掉
            low[x]=min(low[x],dfn[v1]);
    }
    if(dfn[x]==low[x])
    {
        cnt_scc++;
        int t;
        while(1)
        {
            t=stk[top--],ins[t]=false;
            bel[t]=cnt_scc;
            scc[cnt_scc].push_back(t);
            scc_size[cnt_scc]++;
            if(x==t)
                break;
        }
    }
}
int main()
{
    memset(head,-1,sizeof(head));
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        int u,v;
        cin>>u>>v;
        add(u,v);
    }
    for(int i=1;i<=n;i++)
        if(!dfn[i])
            tarjan(i);




    int out[M]={0};
    for(int i=1;i<=n;i++)
        for(int j=head[i];~j;j=e[j].next)
        {
            int v1=e[j].to;
            if(bel[i]!=bel[v1])
                out[bel[i]]++;
        }
    int cnt_zero=0,ans_dot;
    for(int i=1;i<=cnt_scc;i++)
        if(out[i]==0)
        {
            cnt_zero++;
            ans_dot=i;
        }
    if(cnt_zero==1)
        printf("%d",scc_size[ans_dot]);
    else
        printf("0");
}
