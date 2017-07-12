
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;  
typedef long long LL;
const int N = 1e5+5;

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int n,m,k;
int g[N];
LL F[N][30];
  
bool DFS(int t,int x,int tmp) {
	if(!x) return tmp == n;
	x --;
	while(1) {
		if(t + x > m) return false;
		if(F[t][x] > n || F[t][x]*tmp > n) return false;
		if(DFS(t+1,x,tmp*g[t])) return true;
		t ++;
	}
}  

int main () {
	int Q; cin >> Q; while(Q --) {
		cin >> n >> k;
		if((n == 1 &&  k >= 2 )|| (n >= 3 && k >= n)) { puts("NIE"); continue; }
		if(k <= 2) { puts("TAK");  continue; }
		int t; m = 0;
		for(t=1;t*t<n;++t) if(n%t==0) g[++m] = t, g[++m] = n/t;
		if(t*t==n) g[++m] = t; sort(g+1,g+m+1);
		LL tmp = 1;
		for(int i=1;i<=m;++i,tmp=1) for(int j=0;j<k && i+j<=m;F[i][j++] = tmp)  if(tmp <= n) tmp *= g[i+j];
		if(DFS(1,k,1)) puts("TAK");
		else puts("NIE");
	}
}
