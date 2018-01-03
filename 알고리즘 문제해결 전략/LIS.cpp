#include <iostream>
#include <algorithm>

using namespace std;

/*
 * problem ID : LIS
 * from algospot.com
 *
 * 2018.01.03 WED
 * although it is possible to find the longest increasing sequence in O(nlgn) time,
 * this code just use O(n^2) algorithm
 */

int num[500], n; // the # of integers

int cache[501];

/* find the lis with time complexity O(n^2) */
int lis(int start) {
	int& ret = cache[start+1];
	if (ret != -1)  return ret;

	ret = 1;
	for (int next = start+1; next < n; ++next) {
		if (num[start] < num[next] || start == -1)
			ret = max(ret, 1 + lis(next));
	}
	return ret;
}

int main() {
	int casenum;

	cin >> casenum;

	while (casenum-- > 0) {
		cin >> n;
		for (int i = 0; i < n; ++i) {
			cache[i] = -1;
			cin >> num[i];
		}
		cache[n] = -1;
		printf("%d\n", lis(-1)-1);
	}
}