// 2^20 < 2*1000*1000，所以数组大小开2e6
const int N = 2e6+10;

int q[N];

class Solution {
public:
    int n,cnt,goal,res;

    void dfs1(vector<int>& nums,int idx,int sum)
    {
        // 找到一个可行解
        if(idx==(n+1)/2)// n向上取整，前半部分为[0,n/2]
        {
            q[cnt++]=sum;
            return;
        }
        // 枚举两种情况，一种是选上第idx个元素，另一种是不选第idx个元素
        dfs1(nums,idx+1,sum);
        dfs1(nums,idx+1,sum+nums[idx]);
    } 

    void dfs2(vector<int>& nums,int idx,int sum)
    {
        // 找到一个可行解
        if(idx==n)// 后半部分为[n/2+1,n-1]
        {
            int l=0,r=cnt-1;
            // 二分查找<=goal 的最大位置
            while(l<r)
            {
                // 向上取整，避免 left 取不到 right 造成死循环
                int mid=(l+r+1)>>1;
                if(q[mid]+sum<=goal)l=mid;// mid满足check，向右逼近，mid可能就是目标值，所以l=mid
                else r=mid-1;// mid不满足check，向左逼近，mid不可能为目标值，所以r=mid-1
            }
            // 最后找到的元素为最接近goal的
            res=min(res,abs(q[r]+sum-goal));
            // 若r有下一个元素，那么我们最近goal的元素要么在 <=goal 的最大位置产生，要么在 >goal 的最小位置产生
            // 所以每次更新res时，注意这两个位置
            if(r+1<cnt)
                res=min(res,abs(q[r+1]+sum-goal));
            return;
        }
        // 枚举两种情况，一种是选上第idx个元素，另一种是不选第idx个元素
        dfs2(nums,idx+1,sum);
        dfs2(nums,idx+1,sum+nums[idx]);
    }
    
    // 题解：双向dfs，dfs1枚举2^20中选法，然后排序前半段得到的子序列和数组，然后再枚举后半段的子序列，二分前半段的子序列和数组，使得前半段的子序列和与后半段的子序列和相加的结果接近goal
    int minAbsDifference(vector<int>& nums, int _goal) {
        n=nums.size(),cnt=0,goal=_goal,res=INT_MAX;
        // 先搜索前一半，给搜索完的数组排个序，便于在搜索后一半数组的时候进行二分
        dfs1(nums,0,0);
        sort(q,q+cnt);
        // 搜索后一半
        dfs2(nums,(n+1)/2,0);
        return res;
    }
};

作者：yfnupup
链接：https://leetcode.cn/problems/closest-subsequence-sum/solution/cshuang-xiang-dfs-by-xiaoneng-et83/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。