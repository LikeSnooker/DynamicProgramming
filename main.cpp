//
//  main.cpp
//  DP
//
//  Created by 雨张 on 2018/9/3.
//  Copyright © 2018年 雨张. All rights reserved.
//

#include <iostream>

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
 * 格子取物,假设有N*M个格子,每个格子放有一定数量的苹果，从左上角的格子出发，每次只能向右或者向下移动
 * 一个格子，每移动一个格子就把格子里的苹果取出，--->最多能取到多少苹果
 */

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
 * 格子取物 升级版,从单趟变为三趟，左上到右下->回到左上->再去右下 其余依然不变
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
int main(int argc, const char * argv[]) {
// <!----------------------------------------------------------------------------------!>
    // insert code here...
    int coins[3] = {1,3,5};
//    minimumNumberCoins(11,coins, 3);
    printf("总币值为 11，分别有 1 3 5,最小币值数为:%d\n",minimumNumberCoins(11, coins, 3));
// <!----------------------------------------------------------------------------------!>
    
    int a[5] = {1,2,3,4,2};
    printf("最长非降序子序列的长度为:%d\n",lis(a,5));
// <!----------------------------------------------------------------------------------!>
    
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
// <!----------------------------------------------------------------------------------!>
    std::cout << "Hello, World!\n";
    return 0;
}
