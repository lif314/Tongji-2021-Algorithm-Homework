# include <iostream>
# include <vector>
# include <string>
# include <sstream>
# include <list>
# include <algorithm>

using namespace std;

//Interval结构体
struct Interval
{
    int start; /*左端点*/
    int end;   /*右端点*/
};

// 提取数字
vector<Interval> string2Interval(string str) 
{
    char numarr[] = {'0','1','2','3','4','5','6','7','8','9',};
	list<int> numlist;
	int startIndex = 0;
 
	while (startIndex != -1)
	{
		vector<char> tempnum;
 
		startIndex = -1;
 
		for (size_t i = 0; i < str.length(); i++)
		{
			for (size_t j = 0; j < (sizeof(numarr) / sizeof(numarr[0])); j++)
			{
				if (str[i] == numarr[j])
				{
					startIndex = i;
					break;
				}
			}
 
			if (startIndex != -1)
			{
				tempnum.push_back(str[startIndex]);
				int tempindex = 0;
 
				//向下查找数据
				char tempchar = str[startIndex + (tempindex += 1)];
 
				//表示为数字
				while (int(tempchar - 48) >= 0 && int(tempchar - 48) <= 9)
				{
					tempnum.push_back(tempchar);
					tempchar = str[startIndex + (tempindex += 1)];
				}
 
				//删除查询到的数据
				str.erase(startIndex, tempindex);
				break;
			}
		}
		
		if (!tempnum.empty()) {
			//cout << "tempnum : " << string(tempnum.begin(), tempnum.end()) << endl;
			numlist.push_back(stoi(string(tempnum.begin(), tempnum.end())));
		}
	}

    /*将list转换为Interval*/
    vector<Interval> Intervals;
    Interval tmp;  /*临时Interval结构体*/
    int count = 0;
    for (list<int>::iterator it = numlist.begin(); it != numlist.end(); it++)
		{
            if(count % 2 == 0)
            {
                tmp.start = *it;
                count++;
            }
            else
            {
                tmp.end = *it;
                Intervals.push_back(tmp);
                count++;
            }
            
			//cout << *it << endl;
		}
 
	return Intervals;
}



// 按右端点值升序排序排序
bool endLessSort(Interval a, Interval b)
{
    return a.end < b.end;
}

// 主算法
int nonOverlappingIntervals(vector<Interval> intervals)
{
	/*按右断点值从小到达排序*/
    sort(intervals.begin(), intervals.end(), endLessSort);
	int len = intervals.size();

	/*记录重复区间个数*/
	int count = 0;

	/*定义end，表示当前连续不重叠区间的最右端*/
	int end = intervals[0].end;
	for (int i = 1; i < len; ++i)
	{
		/*没有重叠，需要更新不重叠区间的右端点*/
		if (end <= intervals[i].start)
			end = intervals[i].end;
		/*如果重叠，则count++*/
		else
			count++;
	}
	return count;
}

// main函数
int main()
{
	/*输入字符串，形式为[[1,2],[3,4],[12,45]]*/
    string s;
    cin >> s;
    cout << nonOverlappingIntervals(string2Interval(s)) << endl;
    return 0;
}