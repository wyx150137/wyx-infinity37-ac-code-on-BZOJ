
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 5e5+5;

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

LL ans[N];
int tot;
int n, q;

struct data {
	int f, x, y;
	data (int _f=0,int _x=0,int _y=0):f(_f),x(_x),y(_y) {}
	bool operator < (const data &z) const {return x < z.x;}
} line[N];

int main() {
//	freopen("tt.in","r",stdin);
	char str[10];
	n = read(), q = read();
	int c = 0;
	int last = 0;
	for(int i=1;i<=n;++i) {
		scanf("%s", str);
		int t = read(), k = read();
		line[++tot] = data(1, c, t - last); last = t;
		if(str[0] == '+') c += k;
		else c -= k;
	}
	for(int i=1;i<=q;++i) {
		int k = read();
		if(-k > c) ans[i] = -1;
		else line[++tot] = data(2, -k, i);
	}
	sort(line+1,line+tot+1);
	line[0].x = line[1].x;
	LL all = 0, temp = 0;
	for(int i=1;i<=tot;++i) {
		all += (LL) temp * (line[i].x - line[i-1].x);
		if(line[i].f == 1) temp += line[i].y;
		else ans[line[i].y] = all;
	}
	for(int i=1;i<=q;++i) {
		if(~ans[i]) printf("%lld\n", ans[i]);
		else puts("INFINITY");
	}
}
