#include<bits/stdc++.h>
#define INF 2147483647
#define N 800
#define M 500100
const int mod=1e9+7;
using namespace std;
typedef long long ll;
int n,m,s,t;
int dis[N][N],w[N],ord[N];
bool added[N],ins[N];
//算法即将执行第x轮，此时图中还剩n-x+1个点
int Minimum_Cut_Phase(int x)
{
    memset(ins,0,sizeof(ins));//清空集合，集合是每一轮的集合
    memset(w,0,sizeof(w));
    w[0]=-1;
    for(int i=1;i<=n-x+1;i++)
    {
        int mx=0;//到集合的紧密度最大的点的编号
        for(int j=1;j<=n;j++)
        {
            if(!added[j] && !ins[j] && w[j]>w[mx])
                mx=j;
        }
        ins[mx]=1;//mx是新找到的到集合的紧密度最大的点，将其加入集合
        ord[i]=mx;//第i次加入集合的点是mx
        for(int j=1;j<=n;j++)
        {
            //没有被合并的，并且在集合外的（新图中，集合外的点）
            if(!added[j] && !ins[j])
                w[j]+=dis[mx][j];
        }
    }
    s=ord[n-x];
    t=ord[n-x+1];
    return w[t];
}
int Minimum_Cut_Global()
{
    int res=INF;
    for(int i=1;i<=n-1;i++)//缩点n-1次
    {
        res=min(res,Minimum_Cut_Phase(i));
        added[t]=1;//阶段最小割算法中最后一个加入集合的点被合并到倒数第二个加入集合的点中了
        for(int j=1;j<=n;j++)
        {
            dis[s][j]+=dis[t][j];
            dis[j][s]+=dis[j][t];
        }
    }
    return res;
}
void solve()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        dis[u][v]+=w;
        dis[v][u]+=w;
    }
    printf("%d\n",Minimum_Cut_Global());
}
int main()
{
    solve();
    return 0;
}
