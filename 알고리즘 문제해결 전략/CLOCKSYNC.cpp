#include <iostream>
#include <algorithm>

using namespace std;

/*
 * problem ID : CLOCKSYNC
 * from algospot.com
 *
 * 2017.12.26 TUE
 * this code uses brute-force search,
 * so it can be slow
 */

#define SWITCHES 10
#define CLOCKS 16
#define INF 987654

bool swtch[SWITCHES][CLOCKS]
= { {1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,1,0,0,0,1,0,1,0,1,0,0,0,0},
		{0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,1},
		{1,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,1,1,1,0,1,0,1,0,0,0},
		{1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,1},
		{0,0,0,0,1,1,0,1,0,0,0,0,0,0,1,1},
		{0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,1,1,1,0,0,0,1,0,0,0,1,0,0} };

int turnclk(int swt, int clocks[CLOCKS]) {
	if (swt == SWITCHES) {  // when all switch is handled
		/* check if all clk point 12h */
		bool is12 = true;
		for (int i = 0; i < CLOCKS; ++i)
			if (clocks[i] != 12) {
				is12 = false;
				break;
			}
		if (is12)  return 0;
		else return INF;
	}

	/* push the switch */
	int ret = INF;
	for (int num = 0; num < 4; ++num) {
		ret = min(ret, num + turnclk(swt + 1, clocks));
		for (int clk = 0; clk < CLOCKS; ++clk) {
			if (swtch[swt][clk]) {
				if (clocks[clk] == 12) clocks[clk] = 3;
				else clocks[clk] += 3;
			}
		}
	}
	return ret;
}

int main() {
	int casenum;
	cin >> casenum;

	while (casenum-- > 0) {
		/* get the times pointed by clocks */
		int clocks[CLOCKS];
		for (int clk = 0; clk < CLOCKS; ++clk)
			cin >> clocks[clk];
		int ret = turnclk(0, clocks);
		if (ret == INF) ret = -1;
		printf("%d\n", ret);
	}
}

