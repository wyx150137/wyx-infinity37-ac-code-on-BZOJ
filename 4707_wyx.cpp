
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 512+5;
const int inf = 1e9;

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int w[N][N], g[N][N], f[N][N], h[N][N];


int main() {
	int K = read(), n = 1 << K;
	int i,j,m=1,temp,l,r,mid,k;
	for(i=0;i<n;++i) for(j=0;j<n;++j) w[i][j] = read();
	while(K--) {
		temp = m; m <<= 1;
		for(l=0;l<n;l+=m) {
			r = l + m, mid = l + temp;
			for(i=l;i<mid;++i) for(j=mid;j<r;++j) {
				g[i][j] = inf;
				for(k=l;k<mid;++k) g[i][j] = min(g[i][j], f[i][k]+w[k][j]);
			}
			for(i=mid;i<r;++i) for(j=l;j<mid;++j) {
				g[i][j] = inf;
				for(k=mid;k<r;++k) g[i][j] = min(g[i][j], f[i][k]+w[k][j]);
			}
			for(i=l;i<mid;++i) for(j=mid;j<r;++j) {
				h[i][j] = inf;
				for(k=mid;k<r;++k) h[i][j] = min(h[i][j], g[i][k]+f[k][j]);
			}
			for(i=mid;i<r;++i) for(j=l;j<mid;++j) {
				h[i][j] = inf;
				for(k=l;k<mid;++k) h[i][j] = min(h[i][j], g[i][k]+f[k][j]);
			}
			for(i=l;i<r;++i) for(j=l;j<r;++j) f[i][j] = inf;
			for(i=l;i<mid;++i) for(j=mid;j<r;++j) f[i][j] = h[i][j];
			for(i=mid;i<r;++i) for(j=l;j<mid;++j) f[i][j] = h[i][j];
				/*
			for(i=l;i<r;++i)  {
				for(j=l;j<r;++j) 
					cout << i << ' ' << j << ' ' << f[i][j] << endl;
			}*/
		}
	}
	int ans = inf;
	for(i=0;i<n;++i) for(j=0;j<n;++j) ans = min(ans, f[i][j]);
	cout << ans << endl;
}
