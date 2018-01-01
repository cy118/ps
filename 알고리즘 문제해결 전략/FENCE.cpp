#include <iostream>
#include <algorithm>

using namespace std;

/*
 * problem ID : FENCE
 * from algospot.com
 *
 * 2018.01.01 MON
 * this code uses divide and conquer,
 * so the time complexity is O(nlgn)
 */

int boards[20000];
int brdnum;

/* find the largest rectangle */
int bigrec(int left, int right) {
	if (left == right)  return boards[left];
	if (left < 0)  return 0;
	if (right >= brdnum)  return 0;

	/* whole board figure is like below */
	/* left - ... - leftm - rightm - ... - right */
	int rightm = (left + right + 1) / 2;
	int leftm = rightm - 1;

	/* find the largest rectangle that consists leftm and rightm */
	int minh = min(boards[leftm], boards[rightm]);
	int lefte, righte;
	for (lefte = leftm - 1; lefte >= 0; --lefte) {
		if (boards[lefte] < minh) break;
	}
	lefte++;
	for (righte = rightm + 1; righte < brdnum; ++righte) {
		if (boards[righte] < minh) break;
	}
	righte--;
	int area = max(area, (righte - lefte + 1) * minh);

	/* compare the area with left part and right part */
	area = max(area, bigrec(left, leftm));
	area = max(area, bigrec(rightm, right));

	return area;
}

int main() {
	int casenum;
	cin >> casenum;

	while (casenum-- > 0) {
		cin >> brdnum;
		for (int i = 0; i < brdnum; ++i)
			cin >> boards[i];
		printf("%d\n", bigrec(0, brdnum-1));
	}
}