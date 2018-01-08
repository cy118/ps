#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

/*
 * problem ID : PACKING
 * from algospot.com
 *
 * 2017.01.08 MON
 */

int n;  // the # of the stuffs
int w;  // capacity of the carrier
int vol[100]; int need[100];
int cache[1001][101];
int picked[100]; int pickednum;

int pick(int left, int last);

/* saves the picked suffs to picked array */
void reconstruct(int volu, int item) {
	if (item == n)  return;
	
	if (pick(volu, item) == pick(volu, item + 1))
		reconstruct(volu, item + 1);
	else {
		picked[pickednum++] = item;
		reconstruct(volu - vol[item], item+1);
	}
}

/*
 * return the sum of the needs,
 * when the carrier capacity is 'left'
 * and stuff are selected up to number 'last' item
 */
int pick(int left, int last) {
	if (last == n)  return 0;

	int& ret = cache[left][last];
	if (ret != -1)  return ret;

	ret = pick(left, last+1);
	if (vol[last] <= left)
		ret = max(ret, need[last] + pick(left - vol[last], last+1));
	return ret;
}

int main() {
	int casenum;
	cin >> casenum;

	while (casenum-- > 0) {
		string name[100];
		cin >> n >> w;
		for (int i = 0; i < n; ++i)
			cin >> name[i] >> vol[i] >> need[i];
		for (int i = 0; i < 1001; ++i) for (int j = 0; j < 101; ++j)
			cache[i][j] = -1;
		pickednum = 0;
		printf("%d ", pick(w, 0));
		reconstruct(w, 0);
		printf("%d\n", pickednum);
		for (int i = 0; i < pickednum; ++i)
			cout << name[picked[i]] << "\n";
	}
}
