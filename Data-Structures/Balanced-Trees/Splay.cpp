#include<bits/stdc++.h>
#define INF 2147483647
#define N 500100
#define M 500100
const int mod=1e9+7;
using namespace std;
typedef long long ll;
int n,m;
int a[N];
struct Node
{
    int s[2],p,v;//左右儿子，副节点，编号
    int size,flag;//子树大小，是否翻转
    void init(int _v,int _p)
    {
        v=_v;
        p=_p;
        size=1;
    }
}tr[N];
int root,idx;
void pushup(int x)
{
    tr[x].size=tr[tr[x].s[0]].size+tr[tr[x].s[1]].size+1;
}
void pushdown(int x)
{
    if(tr[x].flag)
    {
        swap(tr[x].s[0],tr[x].s[1]);
        tr[tr[x].s[0]].flag^=1;
        tr[tr[x].s[1]].flag^=1;
        tr[x].flag=0;
    }
}
void rotate(int x)
{
    //printf("T2\n");
    int y=tr[x].p,z=tr[y].p;//x的父节点是y,y的父节点是z
    // k=0表示x是y的左儿子；k=1表示x是y的右儿子
    int k=(tr[y].s[1]==x);
    //一共要变三条边的关系：x与根，x与y，y与y的其中一个儿子
    tr[z].s[tr[z].s[1]==y]=x;
    tr[x].p=z;
    tr[y].s[k]=tr[x].s[k^1];
    tr[tr[x].s[k^1]].p=y;
    tr[x].s[k^1]=y;
    tr[y].p=x;
    pushup(y);
    pushup(x);
}
void splay(int x,int k)
{
    //printf("T1\n");
    while(tr[x].p!=k)
    {
        int y=tr[x].p,z=tr[y].p;
        if(z!=k)
        {
            if( (tr[y].s[1]==x) ^ (tr[z].s[1]==y) )
                rotate(x);
            else
                rotate(y);
        }
        rotate(x);
    }
    if(!k)
        root=x;
}
void insert(int v)
{
    int u=root,p=0;
    while(u)
    {
        p=u;
        u=tr[u].s[v>tr[u].v];//v小于当前值插入左儿子，否则插入右儿子   
    }
    u=++idx;//新分配一个点
    if(p)
        tr[p].s[v>tr[p].v]=u;
    tr[u].init(v,p);
    splay(u,0);//最后将当前点转到根
}
//找第k大的数
int get_k(int k)
{
    int u=root;
    while(1)
    {
        pushdown(u);
        if(tr[tr[u].s[0]].size>=k)
            u=tr[u].s[0];
        else if(tr[tr[u].s[0]].size+1==k)
            return u;
        else
        {
            k-=(tr[tr[u].s[0]].size+1);
            u=tr[u].s[1];
        }
    }
    return -1;
}
void output(int u)
{
    pushdown(u);
    if(tr[u].s[0])
        output(tr[u].s[0]);
    //如果当前点不是哨兵，则输出当前点
    if(tr[u].v>=1 && tr[u].v<=n)
        printf("%d ",tr[u].v);
    if(tr[u].s[1])
        output(tr[u].s[1]);
}
void solve()
{
    scanf("%d%d",&n,&m);
    //为了防止边界，习惯性加哨兵，（操作中会取操作序列端点的前一个点和后一个点）
    for(int i=0;i<=n+1;i++)
        insert(i);
    for(int i=1;i<=m;i++)
    {
        int l,r;
        scanf("%d%d",&l,&r);//读入左右端点
        l=get_k(l);//l-1是第l个数
        r=get_k(r+2);//r+1是第r+2个数
        //printf("T4\n");
        splay(l,0);//将左端点转到根
        splay(r,l);//将右端点转到左端点下面
        tr[tr[r].s[0]].flag^=1;//要做的就是将左子树翻转
    }
    //printf("T3\n");
    output(root);//输出中序遍历
}
int main()
{
    solve();
    return 0;
}
