#include <iostream>
#include <vector>
using namespace std;
const int maxn = 10000+5;  // 定義最大數值範圍，取 10005（防止邊界錯誤）
int p[maxn];  // 定義一個陣列來標記哪些數是質數（p[i] = 0 代表是質數，p[i] = 1 代表不是質數）
vector <int> v;  // 用來儲存找到的質數

int main() 
{
    // 1. 利用篩法生成質數列表
    for (int i = 2; i < maxn; i++)  // 從 2 開始檢查是否是質數
	{
        if (p[i] == 0)  // 如果 p[i] 為 0，表示 i 是質數
		{
            for (int j = i+i; j < maxn; j+=i)  // 將 i 的倍數標記為非質數
			{
                p[j] = 1;  // p[j] = 1，表示 j 不是質數
            }
            v.push_back(i);  // 將質數 i 加入質數列表 v 中
        }
    }

    // 2. 處理每個輸入的 n，計算用連續質數和等於 n 的方法數量
    int n;
    while (cin >> n)  // 持續讀取輸入，直到輸入為 0 結束
	{
        if (n == 0) break;  // 當輸入為 0 時結束程式
        int cnt = 0;  // 計算方法數量的變數，初始化為 0

        // 3. 遍歷質數列表，嘗試用連續質數和來組成 n
        for (int i = 0; v[i] <= n; i++)  // 從第一個質數開始
		{
            int sum = 0;  // 用來累加質數的和
            for (int j = i; sum < n; j++)  // 將從第 i 個質數開始連續加上後面的質數
			{
                sum += v[j];  // 累加質數
                if (sum == n)  // 如果累加的結果等於 n
				{
                    cnt++;  // 找到一種組成方法，計數器加 1
                    break;  // 結束這一輪內層迴圈，嘗試下一個質數起點
                }
            }
        }

        // 4. 輸出總共找到多少種方法
        cout << cnt << "\n";  // 輸出方法數量
    }

    return 0;  // 結束程式
}

