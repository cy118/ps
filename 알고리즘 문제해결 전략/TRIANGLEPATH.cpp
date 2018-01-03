#include <iostream>
#include <algorithm>

using namespace std;

/*
 * problem ID : TRIANGLEPATH
 * from algospot.com
 *
 * 2018.01.03 WED
 */

int tri[100][100], n;// size of triangle

int cache[100][100];

/* find the maximum sum of triangular path start at tri[y][x] */
int maxsum(int y, int x) {
	if (y == n-1 && x == n-1)  return tri[y][x];
	if ((y < n && x == n) || (y == n && x < n))  return 0;

	int& ret = cache[y][x];
	if (ret != -1)  return ret;

	ret = tri[y][x];
	ret += max(maxsum(y+1, x), maxsum(y+1, x+1));
	return ret;
}

int main() {
	int casenum;

	cin >> casenum;

	while (casenum-- > 0) {
		cin >> n;

		// initialize the cache and get the triangle
		for (int y = 0; y < n; ++y) for (int x = 0; x <= y; ++x) {
			cache[y][x] = -1;
			cin >> tri[y][x];
		}
		printf("%d\n", maxsum(0, 0));
	}
}