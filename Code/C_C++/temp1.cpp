#include <bits/stdc++.h>
using namespace std;
long long cnt[100005];
int main()
{
	long long n, K;
	long long res = 0;
	cin >> n >> K;
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &cnt[i]);
	}
	sort(cnt, cnt + n); // �������������
	int len = (int)log10(K); // K��λ����һ
	int i;
	// �ȴ�ǰ����ƴ�ӣ�ǰ��ķ��ڵ�λ
	for (i = 0; i < n && (int)log10(cnt[i]) < len; i++)
	{
		// ��K��ȡ��λ
		int a = K % (int)pow(10, (int)(log10(cnt[i])) + 1);
		// ��K��ȡ��λ
		int b = K / (int)pow(10, (int)(log10(cnt[i])) + 1);
		// �����λ���ڵ��ڴ�ƴ�ӵ�������ҪѰ�ĸ�λ�����ҵ���k�ĸ�λ����
		if (a >= cnt[i])
		{
			int vis = upper_bound(cnt + i + 1, cnt + n, b) - cnt - 1; // �ڸ÷�Χ���ҵ�һ������b����������ַ��ȥһ����
			// ���һ�����ڵ���b����
			res += vis - i;
		}
		else
		{
			int vis = lower_bound(cnt + i + 1, cnt + n, b) - cnt - 1;
			res += vis - i;
		}
	}
	int tmp = i - 1;
	for (int j = tmp; j > 0; j--)
	{
		int a = K % (long long)pow(10, (int)(log10(cnt[j])) + 1);
		int b = K / (long long)pow(10, (int)(log10(cnt[j])) + 1);
		if (a >= cnt[j])
		{
			int vis = upper_bound(cnt, cnt + j, b) - cnt - 1;
			res += vis + 1;
		}
		else
		{
			int vis = lower_bound(cnt, cnt + j, b) - cnt - 1;
			res += vis + 1;
		}
	}
	cout << res << endl;
	return 0;
}
