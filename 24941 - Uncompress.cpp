#include <iostream>
#include <vector>
using namespace std;

string s;  // 用來儲存每行輸入
vector <string> v;  // 用來儲存輸出的單詞，實現 LRU（最近最少使用）的單詞列表
string word = "";  // 暫存當前正在讀取的字母組成的單詞
int num = 0;  // 用來暫存讀取到的數字，表示需要取回的單詞的序號

// moveList 函數將新的單詞插入到單詞列表的最前面，並將其他單詞後移
void moveList(string w) {
    v.push_back(v.back());  // 將列表最後一個元素複製，擴充列表長度
    for (int i = v.size()-2; i > 0; i--) {  // 從倒數第二個元素開始向後移動
        v[i] = v[i-1];  // 將每個單詞向後移動一個位置
    }
    v[0] = w;  // 將新的單詞放在最前面
}

// printWord 函數負責輸出單詞，並將其加入單詞列表
void printWord() {
    cout << word;  // 輸出暫存的單詞
    if (v.empty()) {  // 如果單詞列表是空的
        v.push_back(word);  // 將當前單詞加入列表
    } else moveList(word);  // 如果列表不空，將單詞移到列表最前面
    word = "";  // 清空當前單詞暫存
}

// printNum 函數負責輸出根據數字取回的單詞，並更新單詞列表順序
void printNum() {
    string w = v[num-1];  // 根據數字取回對應的單詞
    cout << w;  // 輸出該單詞
    for (int i = num-1; i > 0; i--) {  // 將該單詞前面的單詞向後移
        v[i] = v[i-1];  // 向後移動單詞
    }
    v[0] = w;  // 將取出的單詞移到列表最前面
    num = 0;  // 重置數字暫存
}

int main() {
    while (getline(cin, s))  // 從標準輸入讀取一整行
    {
        if (s == "0") break;  // 如果讀到 "0"，結束程式
        s += "\n";  // 在每行輸入後加上換行符號，方便輸出處理
        for (int i = 0; i < s.size(); i++)  // 遍歷每行的每個字元
        {
            if (isalpha(s[i]))  // 如果字元是字母
            {
                word += s[i];  // 將字母連接到單詞暫存
            } 
            else if (isdigit(s[i]))  // 如果字元是數字
            {
                num *= 10;  // 將之前讀到的數字左移一位（乘10）
                num += s[i] - '0';  // 將當前數字加到 num 中
            } 
            else  // 如果字元是其他字符（如空格、標點符號等）
            {
                if (num) printNum();  // 如果已經讀到數字，根據數字輸出單詞
                if (word != "") printWord();  // 如果已經讀到單詞，輸出單詞
                cout << s[i];  // 輸出當前的非字母或數字字符
            }
        }
    }
    return 0;  // 程式結束
}

