# include<iostream>
# include <string.h>

using namespace std;

# define MAXN 1010      // 数字长度限制
# define INF 0x3f3f3f3f // 表示无穷大
char s1[MAXN], s2[MAXN]; // 字符串
int dp[MAXN][12][12];    // dp数组

int main()
{
    cin >> s1 >> s2;             // 以字符串形式读入
    int len = strlen(s1);
    memset(dp, INF, sizeof(dp)); // 求最小值，初始将所有值设为无穷大

    dp[0][0][0] = 0;             // base case

    for(int pos = 0; pos < len; pos++)
    {
        for(int i = 0; i < 10; i++)
        {
            for(int j = 0; j < 10; j++)
            {
                // 第pos位数字向上旋转到目标状态的步数
                int up = (s2[pos] - s1[pos] - i + 20)%10;
                // 第pos位数字向下旋转到目标状态的步数
                int down = 10 - up;  

                // 枚举向上旋转 —— 状态转移方程
                for(int p = 0; p < up  + 1; p++)
                    for(int q = 0; q < p + 1; q++)
                        dp[pos+1][(j+p)%10][q] = min(dp[pos+1][(j+p)%10][q], dp[pos][i][j] + up);
                        
                // 枚举向下旋转 —— 状态转移方程
                for(int p = 0; p < down + 1; p++)
                    for(int q = 0; q < p+1; q++)
                        dp[pos+1][(j-p+10)%10][(10-q)%10] = min(dp[pos+1][(j-p+10)%10][(10-q)%10], dp[pos][i][j] + down);                   
                }
            }
        }

    // 打印结果
    cout << dp[len][0][0] << endl;

    return 0;    
}