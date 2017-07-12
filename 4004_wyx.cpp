
#include <cmath>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long double f4;
const int N = 500+5;
const f4 eps = 1e-5;

int n, m;
f4 F[N][N];

struct data {
	int val;
	f4 s[N];
	bool operator < (const data&z) const {
		return val < z.val;
	}
} a[N], *b[N];

inline bool insert(data *d) {
	for(int i = 1; i <= m; ++i) {
		if(fabs(d -> s[i]) > eps) {
			if(fabs(F[i][i]) > eps) {
				f4 k = d -> s[i] / F[i][i];
				for(int j=i;j<=m;++j) {
					d -> s[j] -= F[i][j] * k;
				}
			}
			else {
				for(int j = i; j <= m ; ++ j) F[i][j] = d -> s[j];
				return true;
			}
		}
	}
	return false;
}

int main() {
//	freopen("tt.in", "r", stdin);
	cin >> n >> m;
	for(int i=1;i<=n;++i) for(int j=1;j<=m;++j) scanf("%Lf", &a[i].s[j]);
	for(int i=1;i<=n;++i) scanf("%d", &a[i].val);
	sort(a+1,a+n+1);
	for(int i=1;i<=n;++i) b[i] = a + i;
	int cnt = 0, ans = 0;
	for(int i=1;i<=n;++i) if(insert(b[i])) cnt ++, ans += b[i] -> val;
	cout << cnt << " " << ans << endl;
}
