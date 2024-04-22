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
	sort(cnt, cnt + n); // 对数组进行排序
	int len = (int)log10(K); // K的位数减一
	int i;
	// 先从前往后拼接，前面的放在低位
	for (i = 0; i < n && (int)log10(cnt[i]) < len; i++)
	{
		// 在K中取低位
		int a = K % (int)pow(10, (int)(log10(cnt[i])) + 1);
		// 在K中取高位
		int b = K / (int)pow(10, (int)(log10(cnt[i])) + 1);
		// 如果低位大于等于待拼接的数，则要寻的高位可以找等于k的高位的数
		if (a >= cnt[i])
		{
			int vis = upper_bound(cnt + i + 1, cnt + n, b) - cnt - 1; // 在该范围内找第一个大于b的数，将地址减去一即是
			// 最后一个大于等于b的数
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
