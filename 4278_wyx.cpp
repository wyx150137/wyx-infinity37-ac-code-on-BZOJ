
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;
typedef unsigned long long ull;
const int N = 2e5+5, seed = 31, inf = 0x3f3f3f3f;
int n, m;
int a[N], b[N];
ull f[N], g[N], pw[N];

inline char getc()
{
    static const int LEN = 1<<15;
    static char buf[LEN],*S=buf,*T=buf;
    if(S == T)
    {
        T = (S=buf)+fread(buf,1,LEN,stdin);
        if(S == T)return EOF;
    }
    return *S++;
}
 
inline int read()
{
    static char ch;
    static int D;
    while(!isdigit(ch=getc()));
    for(D=ch-'0'; isdigit(ch=getc());)
        D=(D<<3)+(D<<1)+(ch-'0');
    return D;
}
inline ull get1(int l,int r) {
	return f[r] - f[l-1]*pw[r-l+1];
}

inline ull get2(int l,int r) {
	return g[r] - g[l-1]*pw[r-l+1];
}

inline int ask(int x,int y) {
	int l = 1, r = min(n-x+1,m-y+1), mid, ans = 0;
	while(l<=r) {
		mid = (l+r) >> 1;
		if(get1(x,x+mid-1)==get2(y,y+mid-1)) l = (ans = mid) + 1;
		else r = mid - 1;
	}
	return ans;
}

int main (){
	pw[0] = 1;
	register int i,j; int k = 0;
	for(i=1;i<N;++i) pw[i] = pw[i-1] * seed;
	for(n=read(),i=1;i<=n;++i) a[i] = read(), f[i] = f[i-1] * seed + a[i];
	for(m=read(),i=1;i<=m;++i) b[i] = read(), g[i] = g[i-1] * seed + b[i];
	for(a[n+1] = b[m+1] = inf, i = j = 1; i <= n && j <= m; printf("%d ", a[i+k] < b[j+k] ? a[i++] : b[j++])) k = ask(i,j);
	for(;i<=n;++i) printf("%d ", a[i]);
	for(;j<=m;++j) printf("%d ", b[j]);
}
