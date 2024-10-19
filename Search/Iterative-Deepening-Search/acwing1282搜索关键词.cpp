#include<bits/stdc++.h>
#define INF 2147483647
#define N 10010
#define S 55
#define M 1000010
typedef long long ll;
using namespace std;
int n;
int tr[N*S][26],cnt[N*S],idx;
char str[M];
int q[N*S],ne[N*S];
void insert()
{
    int p=0;
    for(int i=0;str[i];i++)
    {
        int t=str[i]-'a';
        if(!tr[p][t])
            tr[p][t]=++idx;
        p=tr[p][t];
    }
    cnt[p]++;
}
void build()
{
    int hh=0,tt=-1;
    for(int i=0;i<26;i++)
        if(tr[0][i])
            q[++tt]=tr[0][i];
    while(hh<=tt)
    {
        int t=q[hh++];
        for(int i=0;i<26;i++)
        {
            int c=tr[t][i];
            if(!c)
                continue;
            int j=ne[t];
            while(j && !tr[j][i])
                j=ne[j];
            if(tr[j][i])
                j=tr[j][i];
            ne[c]=j;
            q[++tt]=c;
        }
    }
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        memset(tr,0,sizeof(tr));
        memset(cnt,0,sizeof(cnt));
        memset(ne,0,sizeof(ne));
        idx=0;
        scanf("%d",&n);
        for(int i=0;i<n;i++)
        {
            scanf("%s",str);
            insert();
        }
        build();
        scanf("%s",str);
        int res=0;
        for(int i=0,j=0;str[i];i++)
        {
            int t=str[i]-'a';
            while(j && !tr[j][t])
                j=ne[j];
            if(tr[j][t])
                j=tr[j][t];
            int p=j;
            while(p)
            {
                res+=cnt[p];
                cnt[p]=0;
                p=ne[p];
            }
        }
        printf("%d\n",res);
    }
    return 0;
}