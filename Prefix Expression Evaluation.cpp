#include <bits/stdc++.h>
using namespace std;

string evaluate_prefix(string str) 
{
    stack<int> stk;
    stringstream ss(str);
    vector<string> tokens;
    string token;
    
    while (ss >> token) 
	{
        tokens.push_back(token);
    }

    // from end to top
    for (int i=tokens.size()-1; i >= 0; i--) 
	{
        token = tokens[i];
        
        // digits
        if (isdigit(token[0]))
		{
			int val = atoi(token.c_str());
            stk.push(val);
        }
        // operators
        else if (token == "+" || token == "-" || token == "*" || token == "/" || token == "%") 
		{
            if (stk.size() < 2) return "illegal";  // not enough values
            
            int a = stk.top(); 
			stk.pop();
            int b = stk.top(); 
			stk.pop();
            
            if (token == "+") stk.push(a + b);
            else if (token == "-") stk.push(a - b);
            else if (token == "*") stk.push(a * b);
            else if (token == "/") 
			{
                if (b == 0) return "illegal";  // can't divide by 0
                stk.push(a / b);
            }
            else if (token == "%") 
			{
                if (b == 0) return "illegal";  // can't mod 0
                stk.push(a % b);
            }
        }
        else return "illegal";
    }

    if(stk.size() == 1) return to_string(stk.top());
    else return "illegal";
}

int main() 
{
    string str;
    while (getline(cin, str)) 
	{
        if (str == ".") break;
        cout << evaluate_prefix(str) << endl;
    }   
    return 0;
}

