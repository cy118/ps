#include <iostream>

using namespace std;

/*
 * problem ID : POLY
 * from algospot.com
 *
 * 2017.01.08 MON
 */

#define MOD 10000000

int cache[101][101];

/* 
 * count the number of polyomino
 * when downstairs has 'down' blocks
 * and n blocks left
 */
int cntpoly(int down, int n) {
	if (n == 0)  return 1;

	int& ret = cache[down][n];
	if (ret != -1)  return ret;

	ret = 0;
	for (int i = 1; i <= n; ++i) {
		if (down == 0)  ret += cntpoly(i, n - i) % MOD;
		else ret += ((down+i-1)*cntpoly(i, n - i)) % MOD;
		ret %= MOD;
	}
	return ret;
}

int main() {
	int casenum;

	cin >> casenum;

	while (casenum-- > 0) {
		int n;
		cin >> n;
		for (int i = 0; i < 101; ++i) for (int j = 0; j < 101; ++j)  cache[i][j] = -1;
		printf("%d\n", cntpoly(0, n));
	}
}