
#include <cmath>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 600 * 600 * 4;
typedef double f2;
const f2 PI = acos(-1);
struct cp {
	f2 a, b;
	cp (f2 _a = 0, f2 _b = 0) :a(_a), b(_b){}
	cp operator + (const cp &z) const {return cp(a+z.a,b+z.b);}
	cp operator - (const cp &z) const {return cp(a-z.a,b-z.b);}
	cp operator * (const cp &z) const {return cp(a*z.a-b*z.b,a*z.b+b*z.a);}
} a[N], b[N], c[N], A[N], x, y;

int rev[N];
int dig[50], n, len;

inline void init(int x) {
	for(n=1,len=0;n<=x<<1;n<<=1,len++) ;
	for(int i=0,l=0;i<n;++i,l=0) {
		for(int j=i;j;j>>=1) dig[l++] = j & 1;
		for(int j=0;j<len;++j)rev[i] = (rev[i]<<1)|dig[j];
	}
}

inline void FFT(cp *a,int type) {
	for(int i=0;i<n;++i) A[i] = a[rev[i]];
	for(int i=0;i<n;++i) a[i] = A[i];
	for(int i=2;i<=n;i<<=1) {
		cp wn(cos(2*PI/i), type*sin(2*PI/i));
		for(int j=0;j<n;j+=i) {
			cp w(1,0);
			for(int k=j;k<j+(i>>1);++k, w = w * wn) {
				x = a[k], y = a[k+(i>>1)] * w;
				a[k] = x + y, a[k+(i>>1)] = x - y;
			}
		}
	}
	if(type == -1) 
		for(int i=0;i<n;++i) a[i].a /= n;
}

char s[600][600], s2[600][600];
int temp[N];
 
inline void read(char *s) {
	char c = getchar();
	while(c != 'G' && c != 'L') c = getchar();
	while(c == 'G' || c == 'L') *(s ++) = c, c = getchar();
}

int main() {
//	freopen("tt.in","r",stdin);
	int r, c, h, w;
	cin >> r >> c;
	for(int i=0;i<r;++i) read(s[i]);
	init(r*c+2);
	int all = r * c - 1;
	int testcases; cin >> testcases;
	for(int tt = 1; tt <= testcases ; ++ tt) {
		cin >> h >> w;
		for(int i=0;i<h;++i) read(s2[i]);
		for(int i=0;i<n;++i) a[i] = b[i] = cp();
		for(int i=0;i<r;++i)
			for(int j=0;j<c;++j)
				a[i*c+j] = cp(s[i][j] == 'G' ? 1 : -1);
		for(int i=0;i<h;++i)
			for(int j=0;j<w;++j)
				b[all-(i*c+j)] = cp(s2[i][j] == 'G' ? 1 : -1);
		FFT(a, 1);
		FFT(b, 1);
		for(int i=0;i<n;++i) ::c[i] = a[i] * b[i];
		FFT(::c, -1);
		for(int i=0;i<n-all;++i) temp[i] = (int) (::c[i+all].a + 0.5);
		int tx, ty, now = -1;
		for(int i=0;i<r-h;++i) 
			for(int j=0;j<=c-w;++j) {
				if(temp[i*c+j] > now) {
					now = temp[i*c+j];
					tx = i;
					ty = j;
				}
			}
		int temp1 = 0, temp2 = 0;
		for(int i=0;i<h;++i) {
			for(int j=0;j<w;++j) {
				if(s[tx+i][ty+j] == s2[i][j]) {
					if(s2[i][j] == 'G') temp1 ++;
					else temp2 ++;
				}
			}
		}
		printf("Case #%d: %d %d %d %d\n", tt, tx + 1, ty + 1, temp1, temp2);
	}
}
