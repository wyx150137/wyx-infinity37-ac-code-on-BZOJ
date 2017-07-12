
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
const int inf = 0x7fffffff;
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
struct data{
	int w1,w2,h1,h2;
}a[N];

int n;

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int main() {
	int T; cin >> T;
	for(int testcases = 1; testcases <= T; ++testcases) {
		int n = read();
		int Min1 = inf, Max1 = -inf;
		int Min2 = inf, Max2 = -inf;
		for(int i=1;i<=n;++i) a[i].w1 = read(), a[i].w2 = read(), a[i].h1 = read(), a[i].h2 = read() ,
							  Min1 = min(Min1,a[i].w1), Max1 = max(Max1, a[i].w2), Min2 = min(Min2,a[i].h1), Max2 = max(Max2, a[i].h2);
		bool flag = false;
		for(int i=1;i<=n && !flag ;++i) if(a[i].w1 <= Min1 && a[i].w2 >= Max1 && a[i].h1 <= Min2 && a[i].h2 >= Max2) flag = true;
		if(flag) puts("TAK");
		else puts("NIE");
	}
}
