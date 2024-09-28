#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;  // �w�q�@�ӫ��O ii�A��ܤ@�Ӿ�ƹ� (first: �`�I�s��, second: �䪺����)

bool dirty;  // �ΨӼаO��J�O�_�]�t�ƾڡ]�ΨӧP�_�O�_�ݭn�B�z�ÿ�X���G�^
vector<ii> g[11111];  // �إߤ@�ӾF���� g�A�j�p�� 11111�A�̭��s�� pair�A��ܸ`�I��������M�䪺����

int dfs(int u, int p, int &ans)  // �`���u���j���]DFS�^��ơAu �O��e�`�I�Ap �O���`�I�Aans �O��e��쪺�̤j�Z��
{
    int mx = 0;  // �O���H u ���ڮɡA�̪����媺����
    for (auto v : g[u]) {  // �M���`�I u ���Ҧ��F���`�I v
        if (v.first == p)  // �p�G�F���`�I v �O���`�I p�A�h���L�A�קK�j��
            continue;
        int cur = dfs(v.first, u, ans) + v.second;  // ���j�i�� DFS�A�p���l�`�I v �����|���� cur
        ans = max(ans, cur + mx);  // ��s�̤j���|���סA�i��O��Ӥ��P�l�`�I���|���`�M
        mx = max(mx, cur);  // ��s u �g�L���̪���@���|���סA�N���^�����`�I
    }

    return mx;  // ��^�H u ���ڪ��̪��媺����
}

void solve()  // �B�z��J����ơA�p��ÿ�X�𪺪��|
{
    int ans = 0;  // ��l�Ƴ̪����|���׬� 0
    dfs(0, -1, ans);  // �q�`�I 0 �}�l�i�� DFS�A-1 ��ܵL���`�I�]�ڸ`�I�^

    for (int i = 0; i < 11111; i++)  // �N�F����M�šA���U�@�����եΨҰ��ǳ�
        g[i].clear();

    printf("%d\n", ans);  // ��X�̤j���|���ס]�𪺪��|�^
}
 
int main()
{
    char inp[111];  // �ΨӦs�x�C���J���r��
    dirty = false;  // ��l�� dirty �аO�� false
    while (fgets(inp, 111, stdin) != NULL) 
	{  // Ū����J���� EOF�A�C��Ū���@��
        if (inp[0] == '\n' || inp[0] == '\r') 
		{  // �p�GŪ��Ŧ�A��ܳo�@�տ�J����
            solve();  // �I�s solve() �p��ÿ�X���G
            continue;  // ���L��U�@��Ū��
        }

        dirty = true;  // ���ƾڿ�J�A�N dirty �]�� true
        int u, v, w;  // �w�q�`�I u, v �M�䪺���� w
        sscanf(inp, "%d %d %d", &u, &v, &w);  // �ѪR��J�AŪ���`�I u, v �H�Υ��̤�������� w
        u--;  // �N�`�I�s���ഫ�� 0-based index
        v--;  // �P�˱N v �ഫ�� 0-based index
        g[u].push_back(ii(v, w));  // �N�� (u, v, w) �[�J��F���� g ��
        g[v].push_back(ii(u, w));  // �]���O�L�V�ϡA�P�ɥ[�W (v, u, w)
    }

    if (dirty)  // �p�G���ƾڿ�J�L
        solve();  // �I�s solve() �p��ÿ�X���G

    return 0;  // �D�{������
}

