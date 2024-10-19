#include<bits/stdc++.h>
#define INF 2147483647
#define N 500100
#define M 500100
const int mod=1e9+7,P=131;
typedef long long ll;
typedef unsigned long long ULL;
using namespace std;
int n,m;
char str[N];
set<ULL>S;
ULL get_hash(int len,char str[])
{
    ULL sum=0;
    for(int i=0;i<len;i++)
        sum=sum*P+(ULL)str[i];
    return sum;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%s",str);
        int len=strlen(str);
        ULL hash_val=get_hash(len,str);
        S.insert(hash_val);
    }
    int ans=S.size();
    printf("%d\n",ans);
    return 0;
}
