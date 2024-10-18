#include<bits/stdc++.h>
#define INF 2147483647
#define N 2001000
#define M 2001000
const int mod=1e9+7;
typedef long long ll;
using namespace std;
struct Edge
{
    int to;
    int next;
}e[M<<1];
int n,m,idx,num;//2*n个点，m个限制
//idx是链式向前星边的下标，num是dfn和low的下标
int head[N],dfn[N],low[N],stk[N],top;
bool ins[N];//ins[x]=true;x在栈中,x尚未构成连通分量
int bel[N],cnt_scc;//bel表示belong，属于哪个强联通分量
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
            if(x==t)
                break;
        }
    }
}
void init()
{
    idx=0;
    scanf("%d%d",&n,&m);
    memset(head,-1,sizeof(head));
    //for(int i=1;i<=2*n;i++)
    //    head[i]=-1;
    for(int k=1;k<=m;k++)
    {
        int i,j,a,b;//xi为a或xj为b
        scanf("%d%d%d%d",&i,&a,&j,&b);
        //xi需要在i和n+i中二选一，表示它为0还是它为1，[1,n]表示0，[n+1,2n]表示1
        //一个不满足，则另一个必定满足
        if(a==0 && b==0)
        {
            add(i+n,j);//xi为1 ==> xj为0
            add(j+n,i);//xj为1 ==> xi为0
        }
        else if(a==0 && b==1)
        {
            add(i+n,j+n);
            add(j,i);
        }
        else if(a==1 && b==0)
        {
            add(i,j);
            add(j+n,i+n);
        }
        else if(a==1 && b==1)
        {
            add(i,j+n);
            add(j,i+n);
        }
    }
}
void solve()
{
    for(int i=1;i<=2*n;i++)
        if(!dfn[i])
            tarjan(i);
    for(int i=1;i<=n;i++)
    {
        if(bel[i]==bel[i+n])
        {
            printf("IMPOSSIBLE\n");
            return;
        }
    }
    printf("POSSIBLE\n");
    for(int i=1;i<=n;i++)
    {
        if(bel[i]>bel[i+n])
            printf("1 ");
        else
            printf("0 ");
    }
    printf("\n");
}
int main()
{
    init();
    solve();
}