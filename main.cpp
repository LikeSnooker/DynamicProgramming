//
//  main.cpp
//  DP
//
//  Created by 雨张 on 2018/9/3.
//  Copyright © 2018年 雨张. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;
void printArr(int ** _arr,int _r,int _c)
{
    for(int r = 0; r < _r;r++)
    {
        for(int c = 0; c < _c;c++)
        {
            printf("%d ",_arr[r][c]);
        }
        printf("\n");
    }
}

void printList(int * _l,int _len)
{
    for(int i = 0;i < _len;i++ )
    {
        printf("%d ",_l[i]);
    }
    printf("\n");
}
/*
 * 1 : 硬币分割,给定数值 以及 硬币面值，求使用硬币最少的分割方案
 *     比如 总额11，币值分别是 1 3 5，最少要三枚硬币 1 5 5
 */

using std::max;

int minimumNumberCoins(int _total, int _coins[],int _len)
{
    if(_total <= 0)
        return 0;
    int result = 99999;
    for(int i  = 0; i < _len;i++)
    {
        if(_total >= _coins[i])
        {
            int coin_c = 1 + minimumNumberCoins(_total-_coins[i], _coins, _len);
            if(coin_c < result)
                result = coin_c;
        }
    }
    return result;
}

// <!----------------------------------------------------------------------------------!>

/*
 * 2 LIS : (longest increasing subsequence)
 *         最长非降序子序列
 */

// 解题思路
int lis(int _a[],int _len)
{
    if(_len <= 0)
        return 0;
    if(_len == 1)
        return 1;
    if(_len == 2)
        return _a[1] >= _a[0] ? 2:1;
    int sub = 99999;
    for(int i = 0;i<_len;i++)
    {
        int * _new_a = new int[_len -1];
        for(int j = 0; j < _len;j++)
        {
            if(j < i)
            {
                _new_a[j]   = _a[j];
            }
            else if (j > i)
            {
                _new_a[j-1] = _a[j];
            }
            int temp = lis(_new_a, _len -1);
            if(temp < sub)
                sub = temp;
        }
        delete []_new_a;
        
    }
    return sub + 1;
}
// <!----------------------------------------------------------------------------------!>
/*
 * 3 格子取物,假设有N*M个格子,每个格子放有一定数量的苹果，从左上角的格子出发，每次只能向右或者向下移动
 * 一个格子，每移动一个格子就把格子里的苹果取出，--->最多能取到多少苹果
 */

// 解题思路 : 因为只能向下和想右移动 ,所以任何一个状态 只可能是左边或上面两个状态转移而来,
// 状态转移方程为 MAX_APPLES(x,y) = max(MAX_APPLES(x-1,y),MAX_APPLES(x,y-1))
int maxApples(int **_apples,int _n,int _m)
{
    if(_n == 0 && _m == 0)
        return _apples[0][0];
    if(_n == 0)
        return _apples[0][_m]  + maxApples(_apples, 0, _m -1);
    if(_m == 0)
        return _apples[_n][0]  + maxApples(_apples, _n-1, 0);
    
    int left = _apples[_n][_m] + maxApples(_apples, _n -1 , _m);
    int up   = _apples[_n][_m] + maxApples(_apples, _n, _m - 1);
    return max(left,up);
}
// <!----------------------------------------------------------------------------------!>

/*
 * 4 格子取物 升级版,从单趟变为三趟，左上到右下->回到左上->再去右下 其余依然不变
 */

int maxApplesEx(int ** _apples,int _x1,int _x2,int _x3,int _y,int _rows_c,int _columns_c)
{
    if(_y == 0)
    {
        int sum = 0;
        for(int c = 0; c <= _x3;c++)
            sum += _apples[0][c];
        return sum;
    }
    if(_y == _rows_c -1)
    {
        int result = 0;
        for(int _up_x1 = 0;_up_x1 < _columns_c-2;_up_x1++)
        {
            for(int _up_x2 = _up_x1+1;_up_x2 < _columns_c-1;_up_x2++)
            {
                for(int _up_x3 = _up_x2+1;_up_x3 < _columns_c;_up_x3++)
                {
                    int temp = maxApplesEx(_apples,_up_x1, _up_x2, _up_x3,_y -1, _rows_c, _columns_c);
                    int sum_of_y =0;
                    for(int c = _up_x1;c < _columns_c;c++)
                        sum_of_y += _apples[_y][c];
                    
                    if(temp + sum_of_y > result)
                        result = temp + sum_of_y;
                }
            }
        }
        return result;
    }
    int result = 0;
    for(int _up_x1 = 0;_up_x1 <= _x1;_up_x1++)
    {
        for(int _up_x2 = _x1 + 1 ; _up_x2 <= _x2 ; _up_x2++)
        {
            for(int _up_x3 = _x2 + 1 ;_up_x3 <= _x3 ; _up_x3++)
            {
                int left_s = 0,mid_s = 0,right_s = 0;
                
                int sub = maxApplesEx(_apples, _up_x1, _up_x2, _up_x3, _y -1,_rows_c,_columns_c);
                for(int l = _up_x1;l <= _x1;l ++)
                {
                    left_s += _apples[_y][l];
                }
                
                for(int m = _up_x2;m <= _x2;m ++)
                {
                    mid_s  += _apples[_y][m];
                }
                for(int r = _up_x3;r <= _x3;r ++)
                {
                    right_s += _apples[_y][r];
                }
                
                int temp = sub + left_s + mid_s + right_s;
                if(temp > result)
                    result = temp;
            }
        }
    }
    return result;
}
/*
 * 5 完美洗牌法 : 题目详情：有个长度为2n的数组{a1,a2,a3,...,an,b1,b2,b3,...,bn}，希望排序
 *   后{a1,b1,a2,b2,....,an,bn}，请考虑有无时间复杂度o(n)，空间复杂度o(1)的解法。
 *
 */
// 解题思路 : 容易想到的就是这种粗暴的解决办法,复制一个新排队，依次把这些牌放到该放的位置
void shuffleDeck(int *_decks,int _len)
{
    int * new_decks = new int[_len];
    for(int i = 0;i < _len;i++)
    {
        new_decks[i] = _decks[i];
    }
    for(int l = 0;l < _len;l++)
    {
        _decks[l] = l & 1 ? new_decks[(l>>1) + (_len>>1)]:new_decks[l >> 1];
    }
    delete []new_decks;
}
// 鉴于 题目要求 空间复杂度必须为o(1),所以我们定下解题的基调:每次只将一个数放到它该呆的位置(这个位置是很好计算的),
// 然后这个位置上的数再放到它该去的位置 依次类推

void perfectShuffle(int *_decks,int _len)
{
    int origi_pos = 1;
    int temp      = 0;
    int half_len  = _len >> 1;
    for(int i = 1; i < _len - 1;i++)
    {
        
        int correct_pos     = origi_pos < half_len ? origi_pos << 1 : ( (origi_pos - half_len) << 1)+ 1;
        
        temp                = _decks[correct_pos];
        _decks[correct_pos] = _decks[1];
        _decks[1]           = temp;
        origi_pos           = correct_pos;
    }
}

/*
 * 6 给定一个一维数组,有正有负 求它所有子段中数字和最大的值
 */

int maxSegementDp(int *_data,int _len)
{
    int sum = 0;
    int max = 1 << 31;
    for(int i = 0; i < _len ;i ++)
    {
        sum += _data[i];
        if(sum < 0)
            sum = 0;
        else
            if(sum > max)
                max = sum;
    }
    return max;
}
/*
 * 7 给定一个二维数组,有正有负 求它的所有子矩形构成的数组中数字和的最大值
 */

// 结题思路,二维无从下手,试图将其转化成一维数组问题,这就是降维
// 假设有个数组 dp[i][c1][c2],表示的是 第i行 ,c1列 到 c2列 各数字之和
//
long maxSubMatrix(vector<vector<long>> & matrix)
{
    long d1 = matrix.size();
    if(d1 == 0)
        return 0;
    long d2 = matrix[0].size();
    if(d2 == 0)
        return 0;
    
    vector<vector<vector<long>>> sums_d1_d21_d22 = vector<vector<vector<long>>>( d1,vector<vector<long>>(d2,vector<long>(d2,0)));
    
    for(int d1_ix = 0;d1_ix < d1;d1_ix++)
    {
        //
        for(int d2_ix1 = 0; d2_ix1 < d2;d2_ix1++)
        {
            for(int d2_ix2 = d2_ix1;d2_ix2 < d2;d2_ix2++)
            {
                if(d2_ix1 == d2_ix2)
                    sums_d1_d21_d22[d1_ix][d2_ix1][d2_ix2] = matrix[d1_ix][d2_ix1];
                else
                    sums_d1_d21_d22[d1_ix][d2_ix1][d2_ix2] = sums_d1_d21_d22[d1_ix][d2_ix1][d2_ix2-1] + matrix[d1_ix][d2_ix2];
            }
        }
    }
    
    long max = 0;
    for(int d2_ix1 = 0;d2_ix1 < d2;d2_ix1++)
    {
        for(int d2_ix2 = d2_ix1;d2_ix2 < d2;d2_ix2++)
        {
            long sum = 0;
            for(int d1_ix = 0; d1_ix < d1;d1_ix++)
            {
                sum += sums_d1_d21_d22[d1_ix][d2_ix1][d2_ix2];
                if(sum < 0)
                    sum = 0;
                else
                    if(sum > max)
                        max = sum;
            }
        }
    }
    return max;
}

/*
 * 8  假设一个数的因子只有2 or 3 or 5，我们称这样的数为丑数
 *    例如 1 2 3 4 5 6 8 9 10 ...
 *    参数 n,给出第n 个丑数
 */
class Solution {
public:
    /**
     * param n, An integer
     * return: the nth prime number as description.
     */
    // 用动态规划的思路求解
    // 考虑到一个ugly number可以通过对另一个ugly number乘上2、3、5获得,我们可以维系一个保存了
    // ugly  number 的队列,将队列中的某个数乘上2、3、5 并添加到队列中
    int nthUglyNumber(int n) {
        vector<int> ugly_nums;
        ugly_nums.push_back(1);
        
        int num2_ix = 0;
        int num3_ix = 0;
        int num5_ix = 0;
        
        int nth = 1;
        while(nth < n)
        {
            int num2 = ugly_nums[num2_ix] * 2;
            int num3 = ugly_nums[num3_ix] * 3;
            int num5 = ugly_nums[num5_ix] * 5;
            int temp  = num2 < num3 ? num2 : num3;
            int min   = temp < num5 ? temp : num5;
            ugly_nums.push_back(min);
            
            if(ugly_nums[num2_ix] * 2 <= ugly_nums.back())
                num2_ix ++;
            if(ugly_nums[num3_ix] * 3 <= ugly_nums.back())
                num3_ix ++;
            if(ugly_nums[num5_ix] * 5 <= ugly_nums.back())
                num5_ix ++;
            
            nth ++;
        }
        return ugly_nums.back();
    }
};
/*
 * 9 钢条切割 已知不同长度钢条的价值 p[k] , 求一根长度为n的钢条如何切割收益最大
 */
// 自顶向下的递归
    int cutRod(vector<int> & p,int n)
    {
        if(n == 0)
            return 0;
        if(n == 1)
            return p[0];
        int most   = -1;
        int income = 0;
        for(int i = 1; i <= n;i++)
        {
            income = p[i-1] + cutRod(p, n-i);
            if(income > most)
                most = income;
        }
        return most;
    }

// 自底向上 表格法 动态规划
    int cutRod2(vector<int> & p,int n)
    {
        vector<int> r = vector<int>(n+1,0);
        r[1] = p[0];
        int max = -1;
        for(int i = 2;i <= n;i++)
        {
            max = -1;
            for(int j = 1; j <= i;j++)
            {
                if(r[i-j] + p[j-1] > max)
                    max = r[i-j] + p[j-1];
            }
            r[i] = max;
        }
        return r[n];
    }

/*
 * 10 矩阵链最优分割
 */
//自顶向下的递归
    int optimalDivision(vector<int> & p,int s,int e)
    {
        if(s >= e)
            return 0;
        if(s + 1 == e)
            return p[s-1] * p[s] * p[s+1];
        
        int optimal = 9999999;
        for(int k = s;k < e;k++)
        {
            int left  = optimalDivision(p, s, k);
            
            int right = optimalDivision(p, k+1,e);
            
            int total = left + right + p[s-1] * p[k] * p[e];
            if(total < optimal)
                optimal = total;
        }
        return optimal;
    }

    int dp2(vector<int> p)// m0 {p0,p1} m1{p1,p2}
    {
        vector<vector<int>> dp = vector<vector<int>>(p.size(),vector<int>(p.size(),0));
        for(int l = 1;l < p.size();l++)
        {
            for(int s = 0; s < p.size() - l;s++)
            {
                if(l == 1)
                    dp[s][s] = 0;
                else if(l == 2)
                    dp[s][s+1] = p[s] * p[s+1] * p[s+2];
                else
                {
                    int min = 99999;
                    
                    for(int k = 1;k < l ;k++)
                    {
                        int total = dp[s][s+k-1] + dp[s+k][s+l-1] + p[s]*p[s+k]* p[s+l];
                        if(total < min)
                            min = total;
                    }
                    dp[s][s+l-1] = min;
                }
                
            }
        }
        return dp[0][p.size()-2];
    }
int main(int argc, const char * argv[]) {
    // <!-------------------------------------第一题------------------------------------------!>
    // insert code here...
    int coins[3] = {1,3,5};
    //    minimumNumberCoins(11,coins, 3);
    printf("总币值为 11，分别有 1 3 5,最小币值数为:%d\n",minimumNumberCoins(11, coins, 3));
    // <!-------------------------------------第二题------------------------------------------!>
    
    int a[5] = {1,2,3,4,2};
    printf("最长非降序子序列的长度为:%d\n",lis(a,5));
    // <!-------------------------------------第三题------------------------------------------!>
    
    int **apples = new int* [5];
    for(int i = 0; i < 5;i++)
    {
        apples[i] = new int[4];
    }
    
    apples[0][0] = 1;
    apples[0][1] = 2;
    apples[0][2] = 3;
    apples[0][3] = 4;
    
    apples[1][0] = 1;
    apples[1][1] = 2;
    apples[1][2] = 3;
    apples[1][3] = 4;
    
    apples[2][0] = 1;
    apples[2][1] = 2;
    apples[2][2] = 3;
    apples[2][3] = 4;
    
    apples[3][0] = 1;
    apples[3][1] = 2;
    apples[3][2] = 3;
    apples[3][3] = 4;
    
    apples[4][0] = 1;
    apples[4][1] = 2;
    apples[4][2] = 3;
    apples[4][3] = 4;
    printArr(apples, 4, 4);
    printf("最多能取到%d个苹果\n",maxApples(apples, 3, 3));
    
    printf("三趟最多能取到%d个苹果\n",maxApplesEx(apples, 3,3,3,3,4,4));
    // <!-------------------------------------第五题------------------------------------------!>
    int arr[20] = {1,3,5,7,9,11,13,15,17,19,2,4,6,8,10,12,14,16,18,20};
    
    perfectShuffle(arr, 20);
    
    printList(arr, 20);
    // <!-------------------------------------第六题------------------------------------------!>
    int arr6[10]   = {1,-2,3,-4,5,-6,7,-8,9,-10};
    
    printf("最大子串和为: %d\n",maxSegementDp(arr6, 10));
    // <!-------------------------------------第七题------------------------------------------!>
    vector<vector<long>> matrix = {{0,-2,-7,0},
        {9,2,-6,2},
        {-4,1,-4,1},
        {-1,8,0,-2}};
    
    long max_sum = maxSubMatrix(matrix);
    printf("最大子数组和为%ld\n",max_sum);
    // <!-------------------------------------第八题------------------------------------------!>
    Solution s = Solution();
    int nth = 10;
    cout << nth << "th ugly number is : "<<s.nthUglyNumber(nth) <<endl;
    std::cout << "Hello, World!\n";
    return 0;
}

