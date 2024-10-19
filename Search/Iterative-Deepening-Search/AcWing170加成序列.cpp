#include<bits/stdc++.h>
#define INF 2147483647
#define N 110
typedef long long ll;
using namespace std;
int n;
int path[N];
//u为当前层数，depth为最大层数
bool dfs(int u,int depth)//已填好前u层（0到u-1），填到设定的层数depth为止，返回能否搜到结果
{
    if(u>depth)
        return false;
    if(path[u-1]==n)//path[n-1]为当前数列的尾元素，已枚举到的最后一个元素
        return true;
    bool st[2*N]={0};//排除等效冗余
    for(int i=u-1;i>=0;i--)
        for(int j=i;j>=0;j--)
        {
            int s=path[i]+path[j];//枚举可能的和,此处为组合数
            if( s>n || s<=path[u-1] || st[s] )
                continue;
            st[s]=true;
            path[u]=s;
            if(dfs(u+1,depth))
                return true;
        }
    return false;
}
int main()
{
    path[0]=1;//第一个数一定是1
    while(cin>>n,n)//读入数据，到0为止
    {
        int depth=1;
        while(!dfs(1,depth))
            depth++;//迭代加深核心调用代码
        for(int i=0;i<depth;i++)
            cout<<path[i]<<" ";
        cout<<endl;
    }
    return 0;
}
