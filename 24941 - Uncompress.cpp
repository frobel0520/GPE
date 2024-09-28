#include <iostream>
#include <vector>
using namespace std;

string s;  // �Ψ��x�s�C���J
vector <string> v;  // �Ψ��x�s��X������A��{ LRU�]�̪�̤֨ϥΡ^������C��
string word = "";  // �Ȧs��e���bŪ�����r���զ������
int num = 0;  // �ΨӼȦsŪ���쪺�Ʀr�A��ܻݭn���^��������Ǹ�

// moveList ��ƱN�s��������J�����C���̫e���A�ñN��L����Ჾ
void moveList(string w) {
    v.push_back(v.back());  // �N�C��̫�@�Ӥ����ƻs�A�X�R�C�����
    for (int i = v.size()-2; i > 0; i--) {  // �q�˼ƲĤG�Ӥ����}�l�V�Ჾ��
        v[i] = v[i-1];  // �N�C�ӳ���V�Ჾ�ʤ@�Ӧ�m
    }
    v[0] = w;  // �N�s�������b�̫e��
}

// printWord ��ƭt�d��X����A�ñN��[�J����C��
void printWord() {
    cout << word;  // ��X�Ȧs�����
    if (v.empty()) {  // �p�G����C��O�Ū�
        v.push_back(word);  // �N��e����[�J�C��
    } else moveList(word);  // �p�G�C���šA�N�������C��̫e��
    word = "";  // �M�ŷ�e����Ȧs
}

// printNum ��ƭt�d��X�ھڼƦr���^������A�ç�s����C����
void printNum() {
    string w = v[num-1];  // �ھڼƦr���^���������
    cout << w;  // ��X�ӳ��
    for (int i = num-1; i > 0; i--) {  // �N�ӳ���e��������V�Ჾ
        v[i] = v[i-1];  // �V�Ჾ�ʳ��
    }
    v[0] = w;  // �N���X���������C��̫e��
    num = 0;  // ���m�Ʀr�Ȧs
}

int main() {
    while (getline(cin, s))  // �q�зǿ�JŪ���@���
    {
        if (s == "0") break;  // �p�GŪ�� "0"�A�����{��
        s += "\n";  // �b�C���J��[�W����Ÿ��A��K��X�B�z
        for (int i = 0; i < s.size(); i++)  // �M���C�檺�C�Ӧr��
        {
            if (isalpha(s[i]))  // �p�G�r���O�r��
            {
                word += s[i];  // �N�r���s�������Ȧs
            } 
            else if (isdigit(s[i]))  // �p�G�r���O�Ʀr
            {
                num *= 10;  // �N���eŪ�쪺�Ʀr�����@��]��10�^
                num += s[i] - '0';  // �N��e�Ʀr�[�� num ��
            } 
            else  // �p�G�r���O��L�r�š]�p�Ů�B���I�Ÿ����^
            {
                if (num) printNum();  // �p�G�w�gŪ��Ʀr�A�ھڼƦr��X���
                if (word != "") printWord();  // �p�G�w�gŪ�����A��X���
                cout << s[i];  // ��X��e���D�r���μƦr�r��
            }
        }
    }
    return 0;  // �{������
}

