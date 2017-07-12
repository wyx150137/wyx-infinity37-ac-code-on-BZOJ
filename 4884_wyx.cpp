
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
typedef long long LL;
const LL inf = 1e18;
const int N = 1e5+5;
using namespace std;
int n;
int a[N], b[N], c[N];
LL F[N][2];
inline void up(LL &x,LL y) {if(x > y) x = y;}
int main() {
	cin >> n;
	for(int i=1;i<=n;++i) scanf("%d", a+i);
	for(int i=1;i<=n;++i) scanf("%d", b+i), c[i] = a[i] - b[i];
	for(int i=2;i<=n;++i) {
		if(b[i] >= a[i-1] || b[i-1] >= a[i]) return 0 * puts("-1");
	}
	for(int i=1;i<=n;++i) F[i][0] = F[i][1] = inf;
	F[1][0] = 0;
	for(int i=1;i<=n;++i) {
		if(i > 1) {
			if(a[i-1] <= a[i]) up(F[i][1], F[i-1][1]);
			if(b[i-1] >= b[i]) up(F[i][0], F[i-1][0]);
		}
		up(F[i][0], F[i][1] + c[i]);
		up(F[i][1], F[i][0] + c[i]);
	}
	if(F[n][0] >= inf) F[n][0] = -1;
	cout << F[n][0] << endl;
}
