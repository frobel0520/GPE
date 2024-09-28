#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;  // 定義一個型別 ii，表示一個整數對 (first: 節點編號, second: 邊的長度)

bool dirty;  // 用來標記輸入是否包含數據（用來判斷是否需要處理並輸出結果）
vector<ii> g[11111];  // 建立一個鄰接表 g，大小為 11111，裡面存放 pair，表示節點之間的邊和邊的長度

int dfs(int u, int p, int &ans)  // 深度優先搜索（DFS）函數，u 是當前節點，p 是父節點，ans 是當前找到的最大距離
{
    int mx = 0;  // 記錄以 u 為根時，最長的鍊的長度
    for (auto v : g[u]) {  // 遍歷節點 u 的所有鄰接節點 v
        if (v.first == p)  // 如果鄰接節點 v 是父節點 p，則跳過，避免迴圈
            continue;
        int cur = dfs(v.first, u, ans) + v.second;  // 遞迴進行 DFS，計算到子節點 v 的路徑長度 cur
        ans = max(ans, cur + mx);  // 更新最大路徑長度，可能是兩個不同子節點路徑的總和
        mx = max(mx, cur);  // 更新 u 經過的最長單一路徑長度，將其返回給父節點
    }

    return mx;  // 返回以 u 為根的最長鍊的長度
}

void solve()  // 處理輸入的函數，計算並輸出樹的直徑
{
    int ans = 0;  // 初始化最長路徑長度為 0
    dfs(0, -1, ans);  // 從節點 0 開始進行 DFS，-1 表示無父節點（根節點）

    for (int i = 0; i < 11111; i++)  // 將鄰接表清空，為下一次測試用例做準備
        g[i].clear();

    printf("%d\n", ans);  // 輸出最大路徑長度（樹的直徑）
}
 
int main()
{
    char inp[111];  // 用來存儲每行輸入的字符
    dirty = false;  // 初始化 dirty 標記為 false
    while (fgets(inp, 111, stdin) != NULL) 
	{  // 讀取輸入直到 EOF，每次讀取一行
        if (inp[0] == '\n' || inp[0] == '\r') 
		{  // 如果讀到空行，表示這一組輸入結束
            solve();  // 呼叫 solve() 計算並輸出結果
            continue;  // 跳過到下一輪讀取
        }

        dirty = true;  // 有數據輸入，將 dirty 設為 true
        int u, v, w;  // 定義節點 u, v 和邊的長度 w
        sscanf(inp, "%d %d %d", &u, &v, &w);  // 解析輸入，讀取節點 u, v 以及它們之間的邊長 w
        u--;  // 將節點編號轉換為 0-based index
        v--;  // 同樣將 v 轉換為 0-based index
        g[u].push_back(ii(v, w));  // 將邊 (u, v, w) 加入到鄰接表 g 中
        g[v].push_back(ii(u, w));  // 因為是無向圖，同時加上 (v, u, w)
    }

    if (dirty)  // 如果有數據輸入過
        solve();  // 呼叫 solve() 計算並輸出結果

    return 0;  // 主程式結束
}

