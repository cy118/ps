#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

/*
 * problem ID : ZIMBABWE
 * from algospot.com
 *
 * 2017.01.16 TUE
 */

#define MOD 1000000007


string e; // e: current egg price
int price[15];
int len;
int m;  // m: submultiple of previous egg price

int cache[2][1 << 15][20];

/* 
 * calculate the number of possible egg prices,
 * when previously made number is equal(0), or smaller(1) than current egg price,
 * 'used' numbers are used,
 * previously calculated mod is 'mod',
 * and 'cnt' elements are defined
 */
int cal(bool isSmall, int used, int mod, int cnt) {
	if (cnt == len)
		return mod == 0 ? 1 : 0;

	int& ret = cache[isSmall][used][mod];
	if (ret != -1)  return ret;

	ret = 0;
	for (int next = 0; next < len; ++next) {
		if (used & (1 << next))  continue;

		if (next > 0 && price[next - 1] == price[next] &&
			(used & (1 << (next - 1))) == 0)  continue;
		
		int pn = price[next];
		char pnc = (char)(pn + '0');
		if (isSmall) {
			ret += cal(true, used + (1 << next), (mod*10 + pn) % m, cnt+1)%MOD;
		}	else if (pnc < e.at(cnt) || (pnc == e.at(cnt) && cnt != len-1)) {
			ret += cal(pnc != e.at(cnt), used + (1 << next), (mod*10 + pn) % m, cnt+1)%MOD;
		}	else {
			continue;
		}
		ret %= MOD;
	}
	return ret;
}

int main() {
	int cn;
	cin >> cn;

	while (cn-- > 0) {
		cin >> e >> m;

		len = e.length();
		/* calculate the len: length of e, and save e in price */
		for (int i = 0; i < len; ++i)
			price[i] = e.at(i) - '0';

		sort(price, price+len);;

		/* initialize the cache */
		for (int i = 0; i < 2; ++i)  for (int j = 0; j < (1 << 15); ++j)
			for (int k = 0; k < 20; ++k)
				cache[i][j][k] = -1;

		printf("%d\n", cal(false, 0<<len, 0, 0));
	}
}