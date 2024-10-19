#include<bits/stdc++.h>
#define N 500100
#define D 500000
#define D1 1000000000
using namespace std;
int n;
int t[N],a[N];
int main()
{
    srand(time(0));
    //n=(rand()%D+D/2+D/3)%D;
    //n=500000;
    //n=40;
    n=rand()%D;
    for(int i=1;i<=n;i++)
        t[i]=rand()%2;
    for(int i=1;i<=n;i++)
        a[i]=rand()%D;
        //a[i]=(rand()+D1/2)%D1;
    printf("%d\n",n);
    for(int i=1;i<=n;i++)
        printf("%d ",t[i]);
    printf("\n");
    for(int i=1;i<=n;i++)
        printf("%d ",a[i]);
    printf("\n");
    return 0;
}
