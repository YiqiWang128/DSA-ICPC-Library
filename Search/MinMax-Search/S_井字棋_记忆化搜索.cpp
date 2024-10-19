#include<bits/stdc++.h>
#define INF 2147483647
#define N 3936700 //39367==39366+1
typedef long long ll;
using namespace std;
int ans[N][2];//1-O-01-max，0-X-10-min
int ADC(char c[3][3])// 00为空，01位O，10位X，11舍弃。1-O-01-max，0-X-10-min
{
    int res=0;
    for(int i=0;i<=2;i++)
        for(int j=0;j<=2;j++)
        {
            int t=i*3+j;//转为0到8
            if(c[i][j]=='O')
            {
                res=res | ( 1<<(2*t) );
                //printf("res: %d\n",res);
            }
            
            if(c[i][j]=='X')
                res=res | ( 2<<(2*t) );
        }
    return res;
}
int jg(int state,int pos)//pos取0到8
{
    //printf("T4:%d\n",( state>>(2*pos) ) & 3);
    return ( ( state>>(2*pos) ) & 3 );//一次检查两位
}
int Result(int state,int a,int who)//这一步要下棋，a为0-8中的一个数，1-O-01，0-X-10
{
    int res=state;//18位
    if(who==1)
        res=res|(1<<(2*a));
    else if(who==0)
        res=res|(2<<(2*a));
    return res;
}
bool check_end(int state)//判断是否终局，终局返回true，还有空位返回false
{
    //printf("T5\n");
    for(int i=0;i<=8;i++)
        if(jg(state,i)==0)
            return false;
    //printf("T3\n");
    return true;
}
int check_grade(int state)//1-O-01，0-X-10
{
    int res=0;

    //1-O-01
    for(int i=0;i<=2;i++)
        if( jg(state,0+3*i)==1 && jg(state,1+3*i)==1 && jg(state,2+3*i)==1 )
            res++;
    for(int j=0;j<=2;j++)
        if( jg(state,0+j)==1 && jg(state,3+j)==1 && jg(state,6+j)==1 )
            res++;
    if( jg(state,0)==1 && jg(state,4)==1 && jg(state,8)==1 )
        res++;
    if( jg(state,2)==1 && jg(state,4)==1 && jg(state,6)==1 )
        res++;


    //0-X-10
    for(int i=0;i<=2;i++)
        if( jg(state,0+3*i)==2 && jg(state,1+3*i)==2 && jg(state,2+3*i)==2 )
            res--;
    for(int j=0;j<=2;j++)
        if( jg(state,0+j)==2 && jg(state,3+j)==2 && jg(state,6+j)==2 )
            res--;
    if( jg(state,0)==2 && jg(state,4)==2 && jg(state,8)==2 )
        res--;
    if( jg(state,2)==2 && jg(state,4)==2 && jg(state,6)==2 )
        res--;


    return res;
}
int dfs(int state,int who)//1-O-01-max，0-X-10-min
{
    if(who==1)//MaxSearch
    {
        if( ans[state][1]!=10 )
            return ans[state][1];
        if( check_end(state)==true )  
            return ans[state][1]=check_grade(state);
        int MaxRes=-9;
        for(int i=0;i<=8;i++)
            if(jg(state,i)==0)
                MaxRes=max( MaxRes,dfs( Result(state,i,1),0 ) );
        return ans[state][1]=MaxRes;
    }
    else//MinSearch
    {
        //printf("T2\n");
        //cout<<"T:"<<ans[state][1]<<endl;
        if( ans[state][0]!=10 )
            return ans[state][0];
        //printf("T6\n");
        if( check_end(state)==true )
        {
            //printf("T1:check_end\n");
            return ans[state][0]=check_grade(state);
        }
        int MinRes=9;
        for(int i=0;i<=8;i++)
            if(jg(state,i)==0)
                MinRes=min( MinRes,dfs( Result(state,i,0),1 ) );
        return ans[state][0]=MinRes;
    }
}
void solve()
{
    int who;
    string s[3];
    char c[3][3];
    cin>>who;
    for(int i=0;i<=2;i++)
        cin>>s[i];
    for(int i=0;i<=2;i++)
        for(int j=0;j<=2;j++)
            c[i][j]=s[i][j];
    /*
    for(int i=0;i<=2;i++)
    {
        for(int j=0;j<=2;j++)
            printf("%c ",c[i][j]);
        cout<<endl;
    }*/
    int data=ADC(c);
    //cout<<data<<endl;
    if(who==1)
        cout<<dfs(data,1)<<endl;
    else if(who==0)
        cout<<dfs(data,0)<<endl;
}
int main()
{
    for(int i=0;i<N;i++)
        ans[i][0]=ans[i][1]=10;
    int T;
    cin >> T;
    while(T--)
    {
        solve();
    }
    return 0;
}




/*
int MaxSearch(int state)//1-O-01-max，0-X-10-min
{
    if( ans[state][1]!=0x3f3f3f3f )
        return ans[state][1];
    if( check_end(state)==true )  
        return ans[state][1]=check_grade(state);
    int MaxRes=-9;
    for(int i=0;i<=8;i++)
        if(jg(state,i)==0)
            MaxRes=max( MaxRes,MinSearch( Result(state,i,0) ) );
    return ans[state][1]=MaxRes;
}
int MinSearch(int state)//1-O-01-max，0-X-10-min
{
    if( ans[state][0]!=0x3f3f3f3f )
        return ans[state][0];
    if( check_end(state)==true )
        return ans[state][0]=check_grade(state);
    int MinRes=9;
    for(int i=0;i<=8;i++)
        if(jg(state,i)==0)
            MinRes=min( MinRes,MaxSearch( Result(state,i,1) ) );
    return ans[state][0]=MinRes;
}
*/