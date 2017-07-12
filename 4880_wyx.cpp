
#include <cmath>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 1e6+5;
using namespace std;
typedef double f2;
typedef long long LL;
const f2 eps = 1e-7;

struct poi {
	int x, y, z;
	double o;
	poi () {}
	poi (int _x,int _y,int _z)
	:x(_x),y(_y),z(_z),o(atan2(y,x)) {}
	bool operator < (const poi &z) const {
		return o < z.o;
	}
	LL operator * (const poi &z) const {
		return x * z.y - y * z.x;
	}
} a[N], b[N];

int s[N];

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int main() {
//	freopen("tt.in","r",stdin);
	int n = read();
	int X = read(), Y = read();
	int atcenter = 0;
	int top = 0;
	for(int i=2;i<=n;++i) {
		int x = read(), y = read();
		if(x == X && y == Y) {
			atcenter ++;
			continue;
		}
		a[++top] = poi(x-X,y-Y,1);
		a[++top] = poi(X-x,Y-y,0); 
	}
	if(top == 0) {
		printf("%d %d\n", 1, ++atcenter);
		return 0;
	}
	sort(a+1,a+top+1);
	int newcnt = 0;
	register int i, j;
	for(i = 1; i <= top; i = j) {
		int sum = 0;
		for(j = i; j <= top && a[i].x * a[j].y == a[j].x * a[i].y && fabs(a[i].o - a[j].o) < eps; ++j) sum += a[j].z;
		b[++newcnt] = poi(a[i].x, a[i].y, sum);
	}
	for(i = 1; i <= newcnt; ++i) b[i+newcnt] = b[i];
	for(i = 1; i <= newcnt + newcnt; ++i) s[i] = s[i-1] + b[i].z;
	int Min, Max;
	Min = N, Max = 0;
	int ina, onl;
	for(i = j = 1; i <= newcnt; ++i) {
		if(j < i) j = i;
		while(j + 1 < i + newcnt && (b[i] * b[j+1]) >= 0) ++j;
		if(b[i].x < 0 || b[i].y > 0) continue;
		ina = s[j] - s[i-1];
		onl = b[i].z;
		if(i < j && (b[i] * b[j] == 0)) onl += b[j].z;
		ina -= onl;
		onl += atcenter;
		Min = min(Min, ina+1);
		Max = max(Max, ina + onl + 1);
	}
	cout << Min << ' ' << Max << endl;
}
