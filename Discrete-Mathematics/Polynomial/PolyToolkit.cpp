#include<bits/stdc++.h>
#define INF 2147483647
#define N 4000100
#define M 4000100//空间开几倍
const int mod=998244353;
const int G=3,invG=332748118;
//const int G=3,invG=334845270;//mod=1004535809
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> PII;
int n,m;
int rev[N],bit,tot;
inline int add(int a,int b)
{
    int r=a+b;
    return r<mod? r : r-mod;
}
inline int sub(int a,int b)
{
    int r=a-b;
    return r<0? r+mod : r;
}
inline int mul(ll a,ll b)
{
    return a*b%mod;
}
inline int inv(int a)
{
    if(a==1)
        return 1;
    return mul(inv(mod%a),mod-mod/a);
}
inline int qmi(ll base,ll k)
{
    int res=1;
    while(k)
    {
        if(k&1)
            res=mul(res,base);
        base=mul(base,base);
        k>>=1;
    }
    return res;
}
inline PII mul(PII a,PII b,int t)
{
    return { add( mul(a.first,b.first),mul(t,mul(a.second,b.second)) ),add( mul(a.first,b.second),mul(a.second,b.first) ) };
}
inline int qmi_cipolla(PII base,int k,int t)
{
    PII res={1,0};
    while(k)
    {
        if(k&1)
            res=mul(res,base,t);
        k=k>>1;
        base=mul(base,base,t);
    }
    return res.first;
}
int Cipolla(int n)
{
    n=n%mod;
    if(n==0)
        return 0;
    if(mod==2)
        return n;
    if(qmi(n,(mod-1)/2)==mod-1)
        return -1;
    if(mod%4==3)
        return qmi(n,(mod+1)/4);
    int a=2,w;
    while(1)
    {
        w=sub(mul(a,a),n);
        if( qmi(w,(mod-1)/2)==mod-1 )
            break;
        a++;
    }
    PII temp={a,1};
    int ans=qmi_cipolla(temp,(mod+1)/2,w);
    return min(ans,mod-ans);
}
inline void init(int n)
{
    bit=0,tot=1;
    while(tot<n)
    {
        tot<<=1;
        bit++;
    }
    for(int i=0;i<tot;i++)
        rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));
}
inline void NTT(ll *a,int inv)
{
    for(int i=0;i<tot;i++)
        if(i<rev[i])
            swap(a[i],a[rev[i]]);//蝴蝶变换中只存在不动点和两者的相互交换，没有第三者掺杂
    for(int mid=1;mid<tot;mid<<=1)//mid表示待合并区间的长度，合并后长度为2*mid，n==2*mid（这里的n是指n次单位根）
    {
        int w1 = qmi( inv == 1 ? G : invG , (mod - 1) / (mid << 1));
        //auto w1=Complex({cos(PI/mid),inv*sin(PI/mid)});
        for(int i=0;i<tot;i+=(mid<<1))
        {
            int wk=1;
            //auto wk=Complex({1,0});
            for(int k=0;k<mid;k++,wk=mul(wk,w1))
            {
                //auto x=a[i+k];
                //auto y=wk*a[i+k+mid];
                ll x=a[i+k];
                ll y=mul(wk,a[i+k+mid]);
                a[i+k]=add(x,y);
                a[i+k+mid]=sub(x,y);
            }
        }
    }
    if(inv!=1)
    {
        ll inv_tot=qmi(tot,mod-2);
        for(int i=0;i<tot;i++)
            a[i]=a[i]*inv_tot%mod;
    }
}
ll px[N],py[N];
vi add(const vi& p1,const vi& p2)
{
    int n3=max(p1.size(),p2.size());
    vi p3=p1;
    p3.resize(n3,0);//如果短就补零，否则不变
    for(int i=0;i<(int)p2.size();i++)
        p3[i]=add(p3[i],p2[i]);
    return p3;
}
vi sub(const vi& p1,const vi& p2)
{
    int n3=max(p1.size(),p2.size());
    vi p3=p1;
    p3.resize(n3,0);
    for(int i=0;i<(int)p2.size();i++)
        p3[i]=sub(p3[i],p2[i]);
    return p3;
}
vi mul(const vi& p1,const vi &p2,int n=0)//mod x^n
{
    int n1=p1.size(),n2=p2.size(),n3=n1+n2-1;
    init(n3);
    if(n>0 && n1>n)
        n1=n;
    if(n>0 && n2>n)
        n2=n;
    copy_n(p1.begin(),n1,px);
    copy_n(p2.begin(),n2,py);
    fill(px+n1,px+tot,0);
    fill(py+n2,py+tot,0);
    NTT(px,1);
    NTT(py,1);
    for(int i=0;i<tot;i++)
        px[i]=mul(px[i],py[i]);
    NTT(px,-1);
    vi p3(n3);
    copy_n(px,n3,p3.begin());
    if(n>0 && n3>n)
        p3.resize(n);
    return p3;
}
vi mul(const vi& p1,ll k)
{
    int n1=p1.size();
    vi p2(n1);
    for(int i=0;i<n1;i++)
        p2[i]=mul(p1[i],k);
    return p2;
}
vi poly_inv(const vi& p1)
{
    int n1=p1.size(),n2=(n1+1)>>1;
    if(n1==1)
        return {inv(p1[0])};
    vi p2=poly_inv( vi(p1.begin(),p1.begin()+n2) );
    init((n1+1)<<2);
    copy_n(p1.begin(),n1,px);
    copy_n(p2.begin(),n2,py);
    fill(px+n1,px+tot,0);
    fill(py+n2,py+tot,0);
    NTT(px,1);
    NTT(py,1);
    for(int i=0;i<tot;i++)
        py[i]=mul( sub( 2,mul(px[i],py[i]) ),py[i] );
    NTT(py,-1);
    vi p3(n1);
    copy_n(py,n1,p3.begin());
    return p3;
}
pair<vi,vi> div(const vi& p1,const vi& p2)
{
    int n1=p1.size(),n2=p2.size(),n3=n1-n2+1;
    if(n3<=0)
        return {{0},p1};
    vi p1r=p1,p2r=p2;
    reverse(p1r.begin(),p1r.end());
    reverse(p2r.begin(),p2r.end());
    p1r.resize(n3,0);
    p2r.resize(n3,0);//取模与补位
    vi p3=mul(p1r,poly_inv(p2r),n3);
    reverse(p3.begin(),p3.end());
    vi p4=sub(p1,mul(p2,p3));
    return {p3,p4};
}
vi MOD(const vi& p1,const vi& p2)
{
    int n1=p1.size(),n2=p2.size(),n3=n1-n2+1;
    if(n3<=0)
        return p1;
    vi p1r=p1,p2r=p2;
    reverse(p1r.begin(),p1r.end());
    reverse(p2r.begin(),p2r.end());
    p1r.resize(n3,0);
    p2r.resize(n3,0);//取模与补位
    vi p3=mul(p1r,poly_inv(p2r),n3);
    reverse(p3.begin(),p3.end());
    vi p4=sub(p1,mul(p2,p3));
    return p4;
}
vi WeiFen(const vi& p1)
{
    int n1=p1.size(),n2=n1-1;
    vi p2(n2);
    for(int i=1;i<n1;i++)
        p2[i-1]=mul(i,p1[i]);
    return p2;
}
vi JiFen(const vi& p1)
{
    int n1=p1.size(),n2=n1+1;
    vi p2(n2,0);
    for(int i=0;i<n1;i++)
        p2[i+1]=mul( p1[i],qmi(i+1,mod-2) );
    return p2;
}
vi log(const vi& p1)
{
    return JiFen( mul( WeiFen(p1),poly_inv(p1),p1.size()-1 ) );
}
vi exp(const vi& p1)//必须保证p1[0]==0！！！
{
    if(p1.size()==1)
        return {1};
    int n1=p1.size(),n2=(n1+1)>>1;
    vi p2=exp({p1.begin(),p1.begin()+n2});
    p2.resize(n1,0);
    return mul( p2,add( sub( {1},log(p2) ),p1 ) );
}

vi poly_qmi(const vi& p1,int k)//这里认为k<mod，所以不用区分%mod还是%(mod-1)
{
    int n1=p1.size(),n2=n1;
    if(p1[0]==1)//单独处理减少常数
    {
        vi p2=exp( mul(log(p1),k) );
        p2.resize(n2);
        return p2;
    }
    if(k==0)
    {
        vi p2=vi(n1,0);
        p2[0]=1;
        return p2;
    }
    while(n2 && !p1[n1-n2])
        n2--;
    int n3=max(n1-1LL*(n1-n2)*k,0ll);
    if(!n2 || !n3)
        return vi(n1,0);
    vi p2(p1.begin()+n1-n2,p1.begin()+n1-n2+n3);
    ll c=p2[0];
    int inv_c=qmi(c,mod-2);
    p2=mul( exp( mul( log(mul(p2,inv_c)),k )  ),qmi(c,k) );
    p2.resize(n3);
    p2.resize(n1);
    rotate(p2.begin(),p2.begin()+n3,p2.end());
    return p2;
}

vi conv(const vi& g)// f[i] = \sum f[i-j]g[j]，初始化g[0]=0
{
    return poly_inv(sub({1},g));
}
vi poly_sqrt(const vi& p1)
{
    int n1=p1.size(),n2=(n1+1)>>1;
    if(n1==1)
        return { Cipolla(p1[0]) };
    vi p2=poly_sqrt(vi(p1.begin(),p1.begin()+n2));
    vi p3=mul(p2,2);
    p3.resize(n1);
    return mul( add(mul(p2,p2,n1),p1),poly_inv(p3),n1 );
}

//单点求值，秦九韶，O(N)
int eval(const vi& p,int x)
{
    ll res=0;
    for(int i=(int)p.size()-1;i>=0;i--)
        res=add( p[i],mul(res,x) );
    return res;
}

//多点求值
//est[0]用于存最终答案，est[i](i>=1)用于存线段树上标号为i的结点所覆盖的区间的多项式之积
vi est[N];
void eval0(const vi& x,int k,int lb,int rb)
{
    if(lb+1==rb)//左闭右开的区间
    {
        est[k]={sub(0,x[lb]),1};
        return;
    }
    int mid=(lb+rb)>>1;
    eval0(x,k<<1,lb,mid);
    eval0(x,k<<1|1,mid,rb);
    est[k]=mul(est[k<<1],est[k<<1|1]);
}
void eval1(const vi& p1,const vi x,int k,int lb,int rb)
{
    vi r=MOD(p1,est[k]);
    if(lb+50>=rb)
    {
        for(int i=lb;i<rb;i++)
            est[0][i]=eval(r,x[i]);
    }
    else
    {
        int mid=(lb+rb)>>1;
        eval1(r,x,k<<1,lb,mid);
        eval1(r,x,k<<1|1,mid,rb);
    }
}
vi eval(const vi& p,const vi& x)
{
    eval0(x,1,0,x.size());
    est[0].resize(x.size());//预分配内存，因为要给est[0][i]赋值
    eval1(p,x,1,0,x.size());
    return est[0];
}