#include <iostream>

using namespace std;

/*
 * problem ID : NUMB3RS
 * from algospot.com
 *
 * 2017.01.08 MON
 */

int connect[50][50];
double cache[51][101];
int p; // a village where jail is in
int vilnum;  // the # of village
int vilcon[50];  // the # of connected villages

/* 
 * calculate the possibility of finding him
 * when 'day' days passed and he is in 'last' village yesterday
 */
double calp(int last, int day) {
	if (day == 0)  return (last == p ? 1.0 : 0.0);

	double& ret = cache[last][day];
	if (ret > -0.5)  return ret;

	ret = 0.0;
	for (int i = 0; i < vilnum; ++i) {
		if (connect[i][last])  ret += 1.0/vilcon[i]*calp(i, day - 1);
	}
	return ret;
}

int main() {
	int casenum;

	cin >> casenum;

	while (casenum-- > 0) {
		int d; // the # of days passed
		int t; // the # of vilage to calculate
		int vil;  // the village number that has to be checked
		cin >> vilnum >> d >> p;

		/* get connection information */
		for (int i = 0; i < vilnum; ++i) {
			int num = 0;
			for (int j = 0; j < vilnum; ++j) {
				cin >> connect[i][j];
				if (connect[i][j] == 1) num++;
			}
			vilcon[i] = num;
		}

		/* get requests */
		for (int k = 0; k < 51; ++k) for (int j = 0; j < 101; ++j) cache[k][j] = -1;
		cin >> t;
		for (int i = 0; i < t; ++i) {
			cin >> vil;
			printf("%.8f ", calp(vil, d));
		}
		printf("\n");
	}
}