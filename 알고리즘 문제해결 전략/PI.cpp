#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

/*
* problem ID : PI
* from algospot.com
*
* 2018.01.05 FRI
*/

#define INF 100000

string memorize;
int cache[10000];

int difficulty(int start, int len);

/* calculate the miminal difficulty */
int makeeasy(int start) {
	if (start == memorize.size())  return 0;
	if (start+3 > memorize.size())  return INF;

	int& ret = cache[start];
	if (ret != -1)  return ret;

	ret = INF;
	ret = min(ret, difficulty(start, 3) + makeeasy(start+3));
	if (start+4 <= memorize.size()) ret = min(ret, difficulty(start, 4) + makeeasy(start+4));
	if (start+5 <= memorize.size()) ret = min(ret, difficulty(start, 5) + makeeasy(start+5));
	return ret;
}

/* calculate the sub-difficulty when sub string length is 'len' and start at 'start' */
int difficulty(int start, int len) {
	int diff[5] = { 1, 2, 4, 5, 10 };
	int dif = 0;
	int sub = memorize.at(start + 1) - memorize.at(start);
	int end = start + len - 1;

	for (int i = start; i < end; ++i) {
		switch (dif) {
		case 0:
			if (memorize.at(i) != memorize.at(i + 1)) {
				dif++; i = start + 1;
			}
			else break;
		case 1:
			if ((sub != 1 && sub != -1) || memorize.at(i + 1) - memorize.at(i) != sub) {
				dif++;
				i = start;
				end = start + len - 2;
			}
			else break;
		case 2:
			if (memorize.at(i) != memorize.at(i+2)) {
				dif++; i = start + 1;
				end = start + len - 1;
			}
			else break;
		case 3:
			if (memorize.at(i + 1) - memorize.at(i) != sub)
				dif++;
			else break;
		case 4: return diff[dif];
		}
	}
	return diff[dif];
}

int main() {
	int casenum;
	cin >> casenum;

	while (casenum-- > 0) {
		cin >> memorize;
		for (int i = 0; i < 10000; ++i)  cache[i] = -1;
		printf("%d\n", makeeasy(0));
	}
}