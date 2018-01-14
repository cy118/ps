#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

/*
 * problem ID : KLIS
 * from algospot.com
 *
 * 2017.01.14 SUN
 */

int n;  // number of elements in a sequence
double k;  // index that has to be found
int seq[500];
int cache[501];
double cntcache[501];

int lis(int last);  // calculate the LIS
double cntlis(int last);  // count the number of LIS

/* find the k-th LIS */
void klis(double skip, int last, vector<int>& lisk) {
	if (last != -1)  lisk.push_back(seq[last]);

	vector<pair<int, int>> next;
	for (int idx = last + 1; idx < n; ++idx) {
		if ((last == -1 || seq[last] < seq[idx]) && lis(last) - 1 == lis(idx))
			next.push_back(make_pair(seq[idx], idx));
	}
	sort(next.begin(), next.end());

	for (int i = 0; i < next.size(); ++i) {
		double pass = cntlis(next.at(i).second);
		if (skip > pass)
			skip -= pass;
		else {
			klis(skip, next.at(i).second, lisk);
			break;
		}
	}
}

/* count the number of LIS */
double cntlis(int last) {
	if (lis(last) == 1)  return 1;
	double& ret = cntcache[last + 1];
	if (ret != -1)  return ret;

	ret = 0;
	for (int next = last + 1; next < n; ++next) {
		if (lis(last) - 1 == lis(next) && (seq[last] < seq[next] || last == -1))
			ret += cntlis(next);
	}
	return ret;
}

/* calculate the LIS */
int lis(int last) {
	int& ret = cache[last+1];
	if (ret != -1)  return ret;

	ret = 1;
	for (int next = last + 1; next < n; ++next) {
		if (seq[next] > seq[last] || last == -1)
			ret = max(ret, 1 + lis(next));
	}
	return ret;
}

int main() {
	int cn;
	cin >> cn;

	while (cn-- > 0) {
		cin >> n >> k;
		for (int i = 0; i < n; ++i)  cin >> seq[i];
		for (int i = 0; i < 501; ++i) {
			cache[i] = -1;
			cntcache[i] = -1;
		}

		printf("%d\n", lis(-1) - 1);
		vector<int> lisk;
		lisk.clear();
		klis(k, -1, lisk);
		for (int i = 0; i < lisk.size(); ++i) {
			printf("%d ", lisk.at(i));
		}
		printf("\n");
	}
}