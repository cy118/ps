#include <iostream>

using namespace std;

/*
 * problem ID : ASYMTILING
 * from algospot.com
 *
 * 2017.01.08 MON
 */

#define MOD 1000000007
int cache[101];

int cnttiling(int n);

/* count the asymmetric tiling using cnttiling */
int asym(int n) {
	if (n % 2 == 1)
		return (cnttiling(n) - cnttiling(n / 2) + MOD) % MOD;
	int ret = (cnttiling(n) - cnttiling(n / 2) + MOD) % MOD;
	return ret = (ret - cnttiling(n / 2 - 1) + MOD) % MOD;
}

/* count the number of possible tiling, when the block size is 2*n */
int cnttiling(int n) {
	if (n == 1 || n == 0)  return 1;
	if (n < 0)  return 0;

	int& ret = cache[n];
	if (ret != -1)  return ret;

	return ret = (cnttiling(n - 2) + cnttiling(n - 1)) % MOD;
}

int main() {
	int casenum;

	cin >> casenum;
	
	for (int i = 0; i < 101; ++i)  cache[i] = -1;
	while (casenum-- > 0) {
		int n;
		cin >> n;
		printf("%d\n", asym(n));
	}
}