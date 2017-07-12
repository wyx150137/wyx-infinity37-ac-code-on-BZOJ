
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 10;
const int all = 59049;
const int mod = 1e9+7;
inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int dig[1<<N], n, F[2][all];

int main() {
	int n = read();
	for(int i=1;i<(1<<N);++i) dig[i] = 3 * dig[i>>1] + (i&1);
	F[0][0] = 1;
	for(int i=0;i<n;++i) {
		int x = read();
		x ^= (1<<N)-1;
		int c = i & 1;
		memset(F[!c], 0, sizeof F[!c]);
		for (int s = 0; s < (1 << N); ++s) {
			for (int t = s;; t = (t - 1) & s) {
				const int cur = F[c][dig[s] + dig[t]];
				(F[!c][dig[s] + dig[t]] += cur) %= mod;
				if ((x & s) != x) {
					(F[!c][dig[s | x] + dig[t & ~x]] += cur) %= mod;
					(F[!c][dig[s | x] + dig[(t & ~x) | (x & ~s)]] -= cur) %= mod;
				}
				if (!t) break;
			}
		}
	}
	cout << F[n&1][dig[(1<<N)-1]] << endl;
}

