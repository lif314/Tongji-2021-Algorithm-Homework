# include<iostream>
# include <string.h>

using namespace std;

# define MAXN 1010      // 数字长度限制
# define INF 0x3f3f3f3f // 表示无穷大
char s1[MAXN], s2[MAXN]; // 字符串
int dp[MAXN][MAXN];    // dp数组

int main()
{
    // 为了方便表示，开始坐标为1
    cin >> s1+1 >> s2+1;
    
    int len = strlen(s1 + 1);   // 字符串长度

    // 将后两个数字扩展为三位数，添加‘0’，并以0结尾
    s1[len + 1] = s1[len + 2] = s1[len + 3] = s2[len + 1] = s2[len + 2] = s2[len + 3] ='0';
    s1[len + 4] = s2[len + 4] = 0;
    len += 3;

    // 求最小值，初始将所有值设为无穷大
    memset(dp, INF, sizeof(dp));

    // 起始三位数
    int start = (s1[1] - '0') * 100 + (s1[2] - '0') * 10 + s1[3] - '0';
    
    dp[1][start] = 0; // base case

    for(int pos = 1; pos <= len - 3 + 1; pos ++)
    {
        for(int current = 0; current <= 999; current ++)
        {
            // 锁定三位数字
            if(dp[pos][current] == INF) continue;

            // 获取三位数j的个、十、百位上的数字
            int hun = current / 100;
            int ten = (current - hun * 100) / 10;
            int num = current - hun * 100 - ten * 10;

            // 获取下一个三位数的末尾数字
            int next_end = s1[pos + 3] - '0';
            
            // 第pos位数字向上旋转到目标状态的步数
            int up = (s2[pos] -'0'+ 10 - hun)% 10; 
            // 第pos位数字向下旋转到目标状态的步数
            int down = 10 - up; 
            
            // 枚举向上旋转 —— 状态转移方程
            for (int p = 0; p < up + 1; p ++) // may change the second
                for (int q = 0; q < p + 1; q ++) // third change
                {
                    // 获取pos+1位置上对应的三位数
                    int next = 100 * (ten + p > 9 ? ten + p - 10:ten + p) + 10 * (num + q > 9 ? num + q - 10:num + q) + next_end;
                    // 状态转移方程
                    dp[pos + 1][next] = min(dp[pos + 1][next],dp[pos][current] + up);
                }

            // 枚举向下旋转 —— 状态转移方程
            for(int p = 0;p < down + 1;p ++)
                for(int q = 0;q < p + 1;q ++)
                {
                    // 获取pos+1位置上对应的三位数
                    int next = 100 * (ten - p < 0 ? ten - p + 10:ten - p) + 10 * (num - q < 0 ? num - q + 10:num - q) + next_end;
                    // 状态转移方程
                    dp[pos + 1][next] = min(dp[pos + 1][next],dp[pos][current] + down);
                }
        }
    }

    // 最后一个有效位上获得最优解
    int end = (s2[len - 2] - '0')* 100 + (s2[len - 1] - '0') * 10 + s2[len] - '0';
    // 打印结果
    cout << dp[len - 3 + 1][end] << endl;
    
    return 0;
}