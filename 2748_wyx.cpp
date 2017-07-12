
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1000+5;
int n,m,x;

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int a[N];
bool F[52][N];

int main() {
	n = read(), x = read(), m = read();
	for(int i=1;i<=n;++i) a[i] = read();
	int i; register int j;
	F[0][x] = 1;
	for(i=1;i<=n;++i) 
		for(j=0;j<=m;++j) {
			if(j + a[i] <= m) F[i][j] |= F[i-1][j+a[i]];
			if(j - a[i] >= 0) F[i][j] |= F[i-1][j-a[i]];
		}
	for(i=m;~i;--i) if(F[n][i]) {
		cout << i << endl;
		return 0;
	}
	puts("-1");
}
