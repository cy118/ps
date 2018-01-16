#include <iostream>
#include <math.h>
#include <string>
#include <cassert>
#include <algorithm>

using namespace std;

/*
 * problem ID : DRAGON
 * from algospot.com
 *
 * 2017.01.16 TUE
 */
int leng[51];
void getn();  // get the length of string of n-th generation

char dragon(string& curve, int skip, int n) {
//	cout << "curve = " << curve << " skip = " << skip << " n = " << n << "\n";
	string x = "X+YF";
	string y = "FX-Y";

	if (n == 0) {
		assert(skip < curve.size());
		return curve[skip];
	}

	for (int i = 0; i < curve.length(); ++i) {
		if (curve[i] == 'X' || curve[i] == 'Y') {
			if (skip >= leng[n])
				skip -= leng[n];
			else if (curve[i] == 'X')
				return dragon(x, skip, n - 1);
			else
				return dragon(y, skip, n - 1);
		}	else if (skip > 0) {
			skip--;
		}	else {
			return curve[i];
		}
	}
	return 'x';
}

void getn() {
	int MAX = 1000000000;
	leng[0] = 1;
	for (int i = 1; i <= 50; ++i)
		leng[i] = min(MAX, 2 + 2 * leng[i - 1]);
}

int main() {
	int cn;
	cin >> cn;
	getn();

	while (cn-- > 0) {
		int n, p, l;
		cin >> n >> p >> l;
		string init = "FX";
		for (int i = 0; i < l; ++i)
			printf("%c", dragon(init, p-1+i, n));
		printf("\n");
	}
}