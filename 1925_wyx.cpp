
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 5000+5;

int n,mod,F[2][N];

int main(){ register int i,j;
	cin >> n >> mod;
	F[1][1] = 1;
	for(i=2;i<=n;++i) {
		int o = i & 1, op = (i+1) & 1;
		for(j=1;j<=n;++j)
			F[o][j] = (F[o][j-1] + F[op][i-j]) % mod;
	}
	printf("%d\n", n == 1 ? 1 : (F[n&1][n]<<1)%mod);
}
