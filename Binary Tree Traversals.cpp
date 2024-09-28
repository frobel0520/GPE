#include <bits/stdc++.h>
using namespace std;

string inorder, preorder;

void BuildPostorder(int preStart, int inStart, int inEnd, bool &first)
{
	if(inStart > inEnd) return;
	
	char root = preorder[preStart];
	int rootIdx = inorder.find(root, inStart);
	BuildPostorder(preStart+1, inStart, rootIdx-1, first);
	BuildPostorder(preStart+1 + rootIdx - inStart, rootIdx+1, inEnd, first);

	if(first == false) cout << " ";
	cout << root;
	first = false;
}

int main()
{
	int cases;
	cin >> cases;
	
	while(cases--)
	{
		int N;
		cin >> N;
		inorder = "";
		preorder = "";
		
		cin.ignore();
		getline(cin, preorder);
		getline(cin, inorder);
		
		preorder.erase(remove(preorder.begin(), preorder.end(), ' '), preorder.end());
		inorder.erase(remove(inorder.begin(), inorder.end(), ' '), inorder.end());
		
		bool first = true;
		BuildPostorder(0, 0, N-1, first);
		cout << endl;
	}
	return 0;
}
