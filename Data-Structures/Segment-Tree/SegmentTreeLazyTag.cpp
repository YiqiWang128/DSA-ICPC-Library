#include<bits/stdc++.h>
#define INF 2147483647
#define N 100010
#define M 1000005
const int mod=1e9+7;
typedef long long ll;
using namespace std;
int n,m;
int w[N];
struct Node
{
    int l,r;
    ll sum,add;//add：已经加过本区间，之后要加到所有正下方的后代区间上
}tr[N*4];
void pushup(int u)
{
    tr[u].sum=tr[u<<1].sum+tr[u<<1|1].sum;
}
//首先要理解add：一个节点上有add表明它的sum已经加过add，它的所有后代(不包括自己)都应加上add，但暂时没加
//pushdown：将u节点的add标记下传到儿子上，儿子改sum加add
void pushdown(int u)
{
    auto &root=tr[u],&left=tr[u<<1],&right=tr[u<<1|1];
    if(root.add)
    {
        left.add+=root.add,left.sum+=(ll)(left.r-left.l+1)*root.add;
        right.add+=root.add,right.sum+=(ll)(right.r-right.l+1)*root.add;
        root.add=0;//最后清空
    }
}
//建立一颗编号为u，根节点区间为[l,r]的一整棵线段树，划分区间并赋初始值
void build(int u,int l,int r)
{
    if(l==r)
        tr[u]={l,r,w[r],0};
    else
    {
        tr[u]={l,r};
        int mid=(l+r)/2;
        build(u<<1,l,mid);
        build(u<<1|1,mid+1,r);
        pushup(u);
    }
}
ll query(int u,int l,int r)
{
    //务必先排除节点区间包含于查询区间return的情况，如果先写pushdown(u)，可能会导致RE
    //RE原因，叶子结点上有add标记，pushdown就会访问不存在的空间
    //线段树代码可以保证，访问到一个节点，该节点必定与查询区间有交集，因此叶子结点直接返回作为贡献
    if(tr[u].l>=l && tr[u].r<=r)//节点的区间包含于查询区间，则直接return，作为答案的一部分贡献
        return tr[u].sum;
    pushdown(u);//本区间早已改对，此处改直接儿子的sum
    int mid=(tr[u].l+tr[u].r)>>1;
    ll sum=0;
    if(l<=mid)
        sum=query(u<<1,l,r);//如果与左儿子有交集，累计左sum
    if(r>mid)
        sum+=query(u<<1|1,l,r);//如果与有儿子有交集，累计右sum
    return sum;
}
//建树的区间分裂一开始就定死了，线段树的思想是不断按照最初定死的分裂建树区间的方式分裂下去，直到当前节点的区间是查询区间的一部分
//u是标识递归状态的参数，l,r,d是固定的全局参数
void modify(int u,int l,int r,int d)//在分裂出的某些完整的树节点区间上改sum，加add
{
    //节点的区间包含于修改区间，则直接改sum加add，不再向下递归
    if(tr[u].l>=l && tr[u].r<=r)
    {
        tr[u].sum+=(ll)(tr[u].r-tr[u].l+1)*d;//改sum
        tr[u].add+=d;//加add标记
    }
    else//当前树节点的区间太大了，要分裂，add必须作用于整个树节点的区间，不能一段+10，一段+15
    {
        //更新儿子的值在递归调用之前，更新自己的值在递归调用之后
        pushdown(u);//将自己的add标记下传给直接儿子
        int mid=(tr[u].l+tr[u].r)>>1;
        if(l<=mid)
            modify(u<<1,l,r,d);//如果与左儿子有交集，modify左儿子
        if(r>mid)
            modify(u<<1|1,l,r,d);//如果与右儿子有交集，modify右儿子
        pushup(u);//用儿子更新父亲
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",&w[i]);
    build(1,1,n);
    int op,l,r,d;
    while(m--)
    {
        scanf("%d%d%d",&op,&l,&r);
        if(op==1)
        {
            scanf("%d",&d);
            modify(1,l,r,d);
        }
        else
            printf("%lld\n",query(1,l,r));
    }
    return 0;
}
