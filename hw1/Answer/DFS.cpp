# include <iostream>
# include <vector>
# include <fstream>

using namespace std;

vector<int>res; // 全局数组

// 递归求解以first_digit数字开头的所有可行解
void Recursion(int first_digit, int n, int K)
{
    if (1 == n) // N位数已取得
    {
        res.push_back(first_digit); 
        return; 
    }

    // 当前数值的末位上的数字
    int unit_digit = first_digit % 10; 

    //如果个位数和差值之差不小于0，则添加一位数，位数减1 
    if (unit_digit - K >= 0)              
        Recursion(10 * first_digit + unit_digit - K, n - 1, K); 
     // 如果个位数和差值之和不大于9，则添加一位数，位数减1
    if (K!=0 && unit_digit + K <= 9) //由于K=0的情况在上式已经考虑，为避免重复加入K！=0的条件  
        Recursion(10 * first_digit + unit_digit + K, n - 1 , K);
}

 // 遍历递归求解
vector<int> dfs(int N, int K) {
    if (1 == N)  // 若N=1，则返回空数组
        return vector<int>{};

    // 遍历递归求解分别以{1,2,3,4,5,6,7,8,9}开头的可行解
    for (int i = 1; i <= 9; i++)
        Recursion(i, N, K);
    return res;
}

int main()
{
    int N, K;
    cin >> N >> K;

    ofstream outFile;
    outFile.open("1951976_perf_case_2.txt");

    vector<int> resSet;
    // 返回计算结果
    resSet = dfs(N, K);
    
    // 打印结果
    outFile << "Case 2 :" << endl;
    if(resSet.empty())
        outFile << "[]" << endl;
    else
    {
        outFile << "[";
        
        for(vector<int>::iterator it=resSet.begin();it!=resSet.end();it++)
        {
            if (it != resSet.end() - 1)
                outFile <<*it<<", ";
            else
            {
                outFile << *it << "]" << endl;
            }
        
        }
    }

    return 0;
}





