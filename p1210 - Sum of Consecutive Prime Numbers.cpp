#include <iostream>
#include <vector>
using namespace std;
const int maxn = 10000+5;  // �w�q�̤j�ƭȽd��A�� 10005�]������ɿ��~�^
int p[maxn];  // �w�q�@�Ӱ}�C�ӼаO���ǼƬO��ơ]p[i] = 0 �N��O��ơAp[i] = 1 �N���O��ơ^
vector <int> v;  // �Ψ��x�s��쪺���

int main() 
{
    // 1. �Q�οz�k�ͦ���ƦC��
    for (int i = 2; i < maxn; i++)  // �q 2 �}�l�ˬd�O�_�O���
	{
        if (p[i] == 0)  // �p�G p[i] �� 0�A��� i �O���
		{
            for (int j = i+i; j < maxn; j+=i)  // �N i �����ƼаO���D���
			{
                p[j] = 1;  // p[j] = 1�A��� j ���O���
            }
            v.push_back(i);  // �N��� i �[�J��ƦC�� v ��
        }
    }

    // 2. �B�z�C�ӿ�J�� n�A�p��γs���ƩM���� n ����k�ƶq
    int n;
    while (cin >> n)  // ����Ū����J�A�����J�� 0 ����
	{
        if (n == 0) break;  // ���J�� 0 �ɵ����{��
        int cnt = 0;  // �p���k�ƶq���ܼơA��l�Ƭ� 0

        // 3. �M����ƦC��A���եγs���ƩM�Ӳզ� n
        for (int i = 0; v[i] <= n; i++)  // �q�Ĥ@�ӽ�ƶ}�l
		{
            int sum = 0;  // �ΨӲ֥[��ƪ��M
            for (int j = i; sum < n; j++)  // �N�q�� i �ӽ�ƶ}�l�s��[�W�᭱�����
			{
                sum += v[j];  // �֥[���
                if (sum == n)  // �p�G�֥[�����G���� n
				{
                    cnt++;  // ���@�زզ���k�A�p�ƾ��[ 1
                    break;  // �����o�@�����h�j��A���դU�@�ӽ�ư_�I
                }
            }
        }

        // 4. ��X�`�@���h�ֺؤ�k
        cout << cnt << "\n";  // ��X��k�ƶq
    }

    return 0;  // �����{��
}

