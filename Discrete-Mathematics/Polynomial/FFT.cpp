#include<bits/stdc++.h>
#define INF 2147483647
#define N 4000100
#define M 4000100//空间开几倍
const int mod=1e9+7;
const double PI=acos(-1);
using namespace std;
typedef long long ll;
int n,m;
int rev[N],bit,tot;
struct Complex
{
    double x,y;
    Complex operator+(const Complex &t)const{
        return {x+t.x,y+t.y};
    }
    Complex operator-(const Complex &t)const{
        return {x-t.x,y-t.y};
    }
    Complex operator*(const Complex &t)const{
        return {x*t.x-y*t.y,x*t.y+y*t.x};
    }
}a[N],b[N];
void printFFT()
{
    for(int i=0;i<=n;i++)
        printf("X[%-2d] = %-6.2f + j %-6.2f\n",i,a[i].x,a[i].y);
    printf("\n");
}
void divideByN()
{
    for(int i=0;i<=n;i++)
    {
        a[i].x=a[i].x/(n+1);
        a[i].y=a[i].y/(n+1);
    }
}
//进行FFT(name,1)得到输入分别为1,w^1,w^2,...,w^(n-1)的函数值，这是点表达式
//进行FFT(name,-1)得到输入分别为1,w^(-1),w^(-1)^2,...,w^(-1)^(n-1)的函数值，这把点表达式转为了系数表达式
void FFT(Complex a[],int inv)
{
    //进行蝴蝶变换，得到一个可以两两向上归并的序列
    //比如rev[001]=100,蝴蝶变换后位于001位置上的数应该为a[100],位于100位置上的数应该为a[001]
    for(int i=0;i<tot;i++)
        if(i<rev[i])
            swap(a[i],a[rev[i]]);//蝴蝶变换中只存在不动点和两者的相互交换，没有第三者掺杂
    for(int mid=1;mid<tot;mid<<=1)//mid表示待合并区间的长度，合并后长度为2*mid，n==2*mid（这里的n是指n次单位根）
    {
        //n次单位根（此处的n与输入的n不同）
        auto w1=Complex({cos(PI/mid),inv*sin(PI/mid)});//角度为2*PI/n，也就是PI/mid
        //进行一组两个长度为mid的区间归并为长度为2*mid的区间后，向右跳2*mid个单位长度
        // i 和 i+mid 是起点，k是这两个起点平移k个单位的结果
        for(int i=0;i<tot;i+=mid*2)
        {
            //n次单位根的k次方
            auto wk=Complex({1,0});
            for(int k=0;k<mid;k++,wk=wk*w1)
            {
                auto x=a[i+k];//左部
                auto y=wk*a[i+k+mid];//右部
                a[i+k]=x+y;
                a[i+k+mid]=x-y;
            }
        }
    }
    if(inv==-1)
        divideByN();
}
int main()
{
    /*
    scanf("%d%d",&n);
    for(int i=0;i<=n;i++)
        scanf("%lf",&a[i].x);
    */
    n=15;
    for(int i=0;i<=n;i++)
    {
        a[i].x=1;
        a[i].y=0;
    }
    //乘积最多是n+m次多项式，有n+m+1个系数，下标为0到n+m，tot>=n+m+1，则tot-1>=n+m，可以覆盖完所有的下标
    while( (1<<bit)<n+1 )
        bit++;
    tot=1<<bit;//2的方幂中大于等于n+m+1的最小数
    //rev[i]:bit位二进制字符串的翻转
    //参与蝴蝶变换的数的范围是[0,tot-1],这些二进制数一共有bit位
    for(int i=0;i<tot;i++)//bit位:全0到全1
        rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));
    printFFT();
    FFT(a,1);
    printFFT();
    FFT(a,-1);
    printFFT();
    return 0;
}
