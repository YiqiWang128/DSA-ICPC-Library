#include<bits/stdc++.h>
#define INF 2147483647
#define N 3500100
#define M 500100
const int mod=1e9+7;
typedef long long ll;
using namespace std;
int inv[N];
void find_inv(int n,int p)
{
    inv[1]=1;
    for(int i=2;i<=n;i++)
        inv[i]=(ll)(p-p/i)*inv[p%i]%p;//开long long!
}
int main()
{
    int n,p;
    scanf("%d%d",&n,&p);
    find_inv(n,p);
    for(int i=1;i<=n;i++)
        printf("%d\n",inv[i]);
    return 0;
}
