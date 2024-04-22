// 题目 1069: 二级C语言-寻找矩阵最值
#include <iostream>
#include <vector>
using namespace std;
// 用于保存最大值的行和列
struct Pos
{
    int x;
    int y;
};
int main()
{
    vector<vector<int>> arr; // 建立二维数组
    int maxAbs = 0;          // 最大值
    Pos max;                 // 最大值的坐标
    int val = 0;             // 每次输入的矩阵元素
    int n = 0;               // 矩阵阶数
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        vector<int> temp; // 一维矩阵，临时保存数据
        for (int j = 0; j < n; ++j)
        {
            cin >> val;
            temp.push_back(val);
            // 更新最大值及其下标
            if (abs(val) > abs(maxAbs))
            {
                maxAbs = val;
                max.x = i + 1;
                max.y = j + 1;
            }
        }
        arr.push_back(temp); // 把一维矩阵放进二维矩阵
    }
    cout << maxAbs << " " << max.x << " " << max.y << endl;
    return 0;
}
