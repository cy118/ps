#include <iostream>

using namespace std;

/*
* problem ID : TILING2
* from algospot.com
*
* 2018.01.05 FRI
*/

#define MOD 1000000007 

int n;  // the block size is 2*n

int cache[101];

int cnttile(int left) {
	if (left <= 1)  return 1;

	int& ret = cache[left];
	if (ret != -1) return ret;

	return ret = (cnttile(left - 1) + cnttile(left - 2)) % MOD;
}

int main() {
	int casenum;
	cin >> casenum;

	while (casenum-- > 0) {
		cin >> n;
		for (int i = 0; i < 101; ++i)  cache[i] = -1;
		printf("%d\n",cnttile(n));
	}
}