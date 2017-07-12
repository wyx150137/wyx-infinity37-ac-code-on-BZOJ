
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;
const int inf = 301;
const int N = 100;
int f[N][N], dp[N], w[N], c[N], n, a, b;
int main()
{
	cin >> n >> a >> b;
	for(int i=1;i<=n;++i) cin >> w[i];
	for(int i=1;i<=n;++i) f[i][i] = a;
	for(int len = 2; len <= n; ++ len) {
		for(int i=1;i+len-1<=n;++i) {
			int j = i + len - 1;
			int Max = 0, Min = inf;
			for(int k=i;k<=j;++k) {
				Max = max(Max,w[k]);
				Min = min(Min,w[k]);
			}
			f[i][j] = a + b * (Max - Min) * (Max - Min);
			for(int x = i; x <= j; ++ x) {
				for(int y = i; y <= j; ++y) {
					if(w[x] >= w[y]) {
						int temp = b * (w[x]-w[y]) * (w[x]-w[y]) + a;
						int tot = 0;
						for(int p = i; p <= j; ++ p) 
							if(w[p] > w[x] || w[p] < w[y]) c[++tot] = p;
						for(int p = 1; p <= tot; ++ p) {
							dp[p] = f[c[1]][c[p]];
							for(int o = 1; o <= p; ++ o) {
								dp[p] = min(dp[p], dp[o-1]+f[c[o]][c[p]]);
							}
						}
						temp += dp[tot];
						f[i][j] = min(f[i][j], temp);
					}
				}
			}
		}	
	}
	cout << f[1][n] << endl;
	return 0;
}
