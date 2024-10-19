//关键还是降阶：如果ai≠bi，则最长公共子序列的最后一组匹配必与ai和bi其中之一无关
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int a=text1.length();
        int b=text2.length();
        vector<vector<int>>dp(a+1,vector<int>(b+1,0));
        for(int i=1;i<=a;i++)
            if(text2[0]==text1[i-1])
            {
                dp[i][1]=1;
                for(;i<=a;i++)
                    dp[i][1]=1;
                break;
            }
        for(int j=1;j<=b;j++)
            if(text1[0]==text2[j-1])
            {
                dp[1][j]=1;
                for(;j<=b;j++)
                    dp[1][j]=1;
                break;
            }
        for(int i=2;i<=a;i++)
            for(int j=2;j<=b;j++)
            {
                if(text1[i-1]==text2[j-1])
                    dp[i][j]=dp[i-1][j-1]+1;
                else
                    dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
            }
            return dp[a][b];
    }
};