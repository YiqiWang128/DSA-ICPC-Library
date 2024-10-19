#include<bits/stdc++.h>
#define INF 2147483647
#define N 500100
const int mod=1e9+7;
using namespace std;
typedef long long ll;
int son[N][26],cnt[N],idx;
char str[N];
void insert(char *str)
{
    int p=0;
    for(int i=0;str[i];i++)
    {
        int u=str[i]-'a';
        if(!son[p][u])
            son[p][u]=++idx;//没有就创建
        p=son[p][u];//走过去
    }
    cnt[p]++;
}
int query(char *str)
{
    int p=0;
    for(int i=0;str[i];i++)
    {
        int u=str[i]-'a';
        if(!son[p][u])
            return 0;
        p=son[p][u];
    }
    return cnt[p];
}
int main()
{
    int n;
    scanf("%d",&n);
    while(n--)
    {
        char op[2];
        scanf("%s%s",op,str);
        if(*op=='I')
            insert(str);
        else
            printf("%d\n",query(str));
    }
    return 0;
}
