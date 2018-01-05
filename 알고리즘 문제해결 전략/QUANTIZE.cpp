#include <iostream>
#include <algorithm>

using namespace std;

/*
* problem ID : QUANTIZE
* from algospot.com
*
* 2018.01.05 FRI
*/

#define INF 100000000

int n, s;  // n: the length of progression, s: the # of signature
int seq[100];
int cache[101][11];

int minsum(int start, int end);  // find the signature that makes least deviation

/* do quantization which makes minimum deviation */
int quantization(int start, int sub) {
	if (start == n)  return 0;
	if (sub == 0)  return INF;

	int& ret = cache[start][sub];
	if (ret != -1)  return ret;

	ret = INF;

	for (int i = 1; i < n - start + 1; ++i)
		ret = min(ret, minsum(start, start + i - 1) + quantization(start + i, sub - 1));

	return ret;
}

/* calculate the minimum deviation */
/* you can do it much faster than this code using average */
int minsum(int start, int end) {
	int sum = INF;
	for (int i = seq[start]; i < seq[end] + 1; ++i) {
		int tmpsum = 0;
		for (int j = start; j < end + 1; ++j) {
			tmpsum += (i - seq[j])*(i - seq[j]);
		}
		sum = min(sum, tmpsum);
	}
	return sum;
}

int main() {
	int casenum;

	cin >> casenum;

	while (casenum-- > 0) {
		cin >> n >> s;
		if (s > n)  s = n;

		for (int i = 0; i < n; ++i)  cin >> seq[i];
		sort(seq, seq + n);
		for (int i = 0; i < n; ++i)  for (int j = 0; j < s+1; ++j)  cache[i][j] = -1;
		printf("%d\n", quantization(0, s));
	}
}