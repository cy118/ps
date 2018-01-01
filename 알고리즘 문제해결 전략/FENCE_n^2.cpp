#include <iostream>
#include <algorithm>

using namespace std;

/*
 * problem ID : FENCE
 * from algospot.com
 *
 * 2018.01.01 MON
 * this code uses brute-force search,
 * which have time complexity O(n^2)
 */

int boards[20000];
int brdnum;

/* find the largest rectangle */
int bigrec(int cur) {
	/* if there's no more board, return the height of current board */
	if (cur == brdnum-1)
		return boards[cur];

	/* find the largest rectangle start from current board */
	int area, minh;
	area = minh = boards[cur];
	for (int next = cur+1; next < brdnum; ++next) {
		minh = min(minh, boards[next]);
		area = max(area, minh*(next - cur + 1));
	}

	/* compare the calculated are with the largest rectangle start from current + 1 board */
	return max(area, bigrec(cur + 1));
}

int main() {
	int casenum;
	cin >> casenum;

	while (casenum-- > 0) {
		cin >> brdnum;
		for (int i = 0; i < brdnum; ++i)
			cin >> boards[i];
		printf("%d\n", bigrec(0));
	}
}