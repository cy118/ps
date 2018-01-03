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

int cache[500];

/* find the lis with time complexity O(n^2) */
int lis(int start) {
	if (start == n-1)  return 1;

	int& ret = cache[start];
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
		int maxret = 0;
		for (int i = -1; i < n; ++i)
			maxret = max(maxret, lis(i));
		printf("%d\n", maxret);
	}
}