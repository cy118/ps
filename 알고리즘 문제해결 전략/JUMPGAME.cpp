#include <iostream>

using namespace std;

/*
 * problem ID : JUMPGAME
 * from algospot.com
 *
 * 2018.01.02 TUE
 * 
 * although graph search is much simpler,
 * this code uses dynamic programming just for practice
 */

int board[100][100], n;
int cache[100][100];

int dogame(int y, int x) {
	if (y >= n || x >= n)  return 0;
	if (y == n-1 && x == n-1)  return 1;

	int& ret = cache[y][x];  // use memorization
	if (ret != -1)  return ret;

	return ret = dogame(y + board[y][x], x) || dogame(y, x + board[y][x]);
}

int main() {
	int casenum;

	cin >> casenum;

	while (casenum-- > 0) {
		cin >> n;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j)
				cin >> board[i][j];
		}
		for (int i = 0; i < 100; ++i) for (int j = 0; j < 100; ++j) cache[i][j] = -1;
		dogame(0, 0) == 1 ? printf("YES\n") : printf("NO\n");
	}
}