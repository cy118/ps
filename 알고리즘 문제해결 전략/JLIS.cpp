#include <iostream>
#include <algorithm>

using namespace std;

/*
 * problem ID : JLIS
 * from algospot.com
 *
 * 2018.01.03 WED
 */

#define NEGINF -10000000000

int a[100], b[100];
int n, m;  // each indicate the length of input string a and b 

int cache[101][101];

int jlis(int astart, int bstart) {
	int& ret = cache[astart+1][bstart+1];
	if (ret != -1)  return ret;

	ret = 2;
	
	long atmp = (astart == -1 ? NEGINF : a[astart]);
	long btmp = (bstart == -1 ? NEGINF : b[bstart]);
	long cmp = max(atmp, btmp);
	for (int anext = astart + 1; anext < n; ++anext)
		if (cmp < a[anext])
			ret = max(ret, 1 + jlis(anext, bstart));
	for (int bnext = bstart + 1; bnext < m; ++bnext)
		if (cmp < b[bnext])
			ret = max(ret, 1 + jlis(astart, bnext));
		return ret;
}

int main() {
	int casenum;

	cin >> casenum;

	while (casenum-- > 0) {
		cin >> n >> m;
		for (int i = 0; i < n; ++i)  cin >> a[i];
		for (int i = 0; i < m; ++i)  cin >> b[i];
		for (int i = 0; i < n+1; ++i) for (int j = 0; j < m+1; ++j)
			cache[i][j] = -1;
		printf("%d\n", jlis(-1, -1) - 2);

	}
}
