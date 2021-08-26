# include <iostream>
# include <vector>
using namespace std;

// 动态规划
int CountUniqueDigits_dpTable(int n)
{
    /*备忘录*/
    vector<int> memo(n+1,9);
    /*边界条件*/
    memo[0] = 1;
    /*填充备忘录*/
    for(int i = 2 ; i <= n; i++)
    {
        for(int j = 9; j >= 9-i+2; j--)
        {
            memo[i] *= j;
        }
    }

    int res = 0;
    for (int i = 0; i <=n; i++)
    {
        res += memo[i];
    }
    
    return res;
}

// 动态规划+状态压缩 
int CountUniqueDigits_dp(int n)
{
    /*边界条件*/
    if (n == 0)
        return 1;
    if (n == 1)
        return 10;

    /*计算*/
    int res = 10;
    int tmp = 9;  /*第i位数的情况*/
    for(int i = 2; i <= n; i++)
    {
        tmp = tmp * (9-i+2);
        res += tmp;
    }     
    return res;
}



int main()
{
    int n;
    cin >> n;
    cout << "dpTable: " << CountUniqueDigits_dpTable(n) << endl;
    cout << "dp: " << CountUniqueDigits_dp(n) << endl;
    return 0; 
}