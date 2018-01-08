#include <iostream>

using namespace std;

/*
 * problem ID : SNAIL
 * from algospot.com
 *
 * 2017.01.08 MON
 */

int depth, days;
double cache[2000][1000];

/*
 * calculate the possibility that
 * snail reach the ground in (days-'left') days 
 * starting at (depth-'dep')
 * defining dep as the location where snail is in causes serious problem in cache
 */
double calp(int dep, int left) {
	if (left == days && dep >=depth)  return 1;
	if (left == days)  return 0;

	double& ret = cache[dep][left];
	if (ret != -1)  return ret;

	return ret = 0.75*calp(dep + 2, left + 1) + 0.25*calp(dep + 1, left + 1);
}

int main() {
	int casenum;

	cin >> casenum;

	while (casenum-- > 0) {
		cin >> depth >> days;
		for (int i = 0; i < 2000; ++i) for (int j = 0; j < 1000; ++j)  cache[i][j] = -1;
		printf("%.8f\n", calp(0, 0));
	}
}