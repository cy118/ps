#include <iostream>
#include <algorithm>

using namespace std;

/*
* problem ID : TRIPATHCNT
* from algospot.com
*
* 2017.01.07 SUN
*/

int n;
int tri[100][100];
int cache[100][100];

/* calculate the max path start at (y,x) */
int maxpath(int y, int x);

/* count the number of max paths */
int cntpath(int y, int x) {
	if (y == n-1)  return 1;

	int& ret = cache[y][x];
	if (ret != -1)  return ret;

	ret = 0;
	if (maxpath(y + 1, x) >= maxpath(y + 1, x + 1))
		ret += cntpath(y + 1, x);
	if (maxpath(y + 1, x) <= maxpath(y + 1, x + 1))
		ret += cntpath(y + 1, x + 1);
	return ret;
}

int tricache[100][100];
int maxpath(int y, int x) {
	if (y == n-1 && x == n-1)  return tri[y][x];
	if (y >= n || x >= n)  return 0;

	int& ret = tricache[y][x];
	if (ret != -1)  return ret;

	ret = tri[y][x];
	return ret += max(maxpath(y+1, x), maxpath(y+1, x+1));
}

int main() {
	int casenum;

	cin >> casenum;

	while (casenum-- > 0) {
		cin >> n;
		for (int i = 0; i < n; ++i) for (int j = 0; j <= i; ++j) {
			cin >> tri[i][j];
			tricache[i][j] = -1;
			cache[i][j] = -1;
		}
		printf("%d\n", cntpath(0, 0));
	}
}
