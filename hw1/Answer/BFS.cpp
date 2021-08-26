# include <iostream>
# include <vector>
# include <fstream>

using namespace std;

vector<int> bfs(int N, int K)
{
    // 初始化vector数组为{1,2,3,4,5,6,7,8,9}
    vector<int> res{1,2,3,4,5,6,7,8,9};

    // 预处理：如果N=1，则清空数组并返回
    if (1 == N)
    {
        res.clear();
        return res;
    }

    // BFS遍历求解
    int count = 1; // 计数器：对位数遍历计数
    while(count < N)   // 外层循环：位数遍历
    {
        int resSize = res.size();  // 获取当前数组的长度
        for (int i = 0; i < resSize; i++) // 内层循环：对当前数组中每一位数字遍历取个位数进行求解
        {
            int unit_digit = res[i] % 10; // 取末位数

            //如果个位数和差值之差不小于0，则说明可以再加一位数字
            if (unit_digit -K >= 0)
                res.push_back(res[i] * 10 + unit_digit - K);
            // 如果个位数和差值之和不大于9，则说明可以再加一位数字
            if (unit_digit + K <=9 && K != 0) //由于K=0的情况在上式已经考虑，为避免重复加入K！=0的条件
                res.push_back(res[i] * 10 + unit_digit + K);
        }

        // 更新数组中的值：删除原先的基数
        res.erase(res.begin(), res.begin() + resSize);
        count++;  // 完成一轮位数的添加
    }

    return res;
} 


int main()
{
    int N, K;
    cin >> N >> K;

    ofstream outFile;
    outFile.open("1951976_perf_case_1.txt");

    vector<int> resSet;
    // 返回计算结果
    resSet = bfs(N, K);
    
    // 打印结果
    outFile << "Case 1 :" << endl;
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