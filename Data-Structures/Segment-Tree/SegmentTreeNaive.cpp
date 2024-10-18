#include<bits/stdc++.h>
#define INF 2147483647
#define N 500010
#define M 1000005
const int mod=1e9+7;
typedef long long ll;
using namespace std;
int m,p;
struct Node
{
    int l,r;
    ll v;
}tr[N*4];//线段树开4倍空间
int a[N];
void pushup(int u)//用儿子更新自己
{
    tr[u].v=tr[u<<1].v+tr[u<<1|1].v;
}
//初始化:build(1,1,n);
void build(int u,int l,int r)//以编号u为根，建立区间为[l,r]的线段树（建树等价于划分区间+初始化）
{
    tr[u]={l,r};
    if(l==r)
    {
        tr[u].v=a[l];
        return;
    }
    int mid=(l+r)/2;
    build(u<<1,l,mid);
    build(u<<1|1,mid+1,r);
    pushup(u);
}
//区间查询:拆分、拼凑
//如果节点的区间包含于查询区间，则直接return，作为查询区间的一部分贡献
//否则一直将节点区间对半分，直到某个节点完全属于查询区间
//查询以编号u为根的子树的值对区间[l,r]的贡献
ll query(int u,int l,int r)//以编号u为根，查询区间[l,r]，调用函数时u默认设为1
{
    if(tr[u].l>=l && tr[u].r<=r)//树中节点，已经被完全包含在[l, r]中了
        return tr[u].v;
    ll sum=0;
    //当前节点的区间的中点(中左)，将左儿子[l,mid]，右儿子[mid+1,r]
    int mid=(tr[u].l+tr[u].r)>>1;
    //这两个if判断其实是一种剪枝
    if(l<=mid)//代表代表左子树与查询区间有交集
        sum+=query(u<<1,l,r);
    if(r>mid)//其实是r>=mid+1，代表右子树与查询区间有交集
        sum+=query(u<<1|1,l,r);
    return sum;
}
void modify(int u,int x,int v)//从以u节点开始往下找x的位置，然后把位置x上的值改成v
{
    if(tr[u].l==x && tr[u].r==x)
        tr[u].v=v;
    else
    {
        int mid=(tr[u].l+tr[u].r)>>1;
        //改儿子
        if(x<=mid)
            modify(u<<1,x,v);
        else
            modify(u<<1|1,x,v);
        pushup(u);//用儿子更新自己
    }
}
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    build(1,1,n);
    while(m--)
    {
        int op;
        scanf("%d",&op);
        if(op==1)
        {
            int x,k;
            scanf("%d%d",&x,&k);
            a[x]+=k;
            modify(1,x,a[x]); 
        }
        else
        {
            int x,y;
            scanf("%d%d",&x,&y);
            printf("%lld\n",query(1,x,y));
        }
    }
    return 0;
}
