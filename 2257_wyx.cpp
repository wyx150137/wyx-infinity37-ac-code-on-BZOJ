
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1e7+5;

int fac[N], cnt;

inline void calc(int x) {
	int i;
	for(i=1;i*i<x;++i) if(x%i==0) fac[++cnt] = i, fac[++cnt] = x / i;
	if(i*i==x) fac[++cnt] = i;
}

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int main() {
	int n,k;
	cin >> n >> k;
	for(int i=1;i<=n;++i) calc(read());
	sort(fac+1,fac+cnt+1);
	int last = 0;
	int ans = 0;
	for(int i=1;i<=cnt+1;++i) {
		if(fac[i] != fac[i-1]) {
			if(last >= k)
				ans = max(ans,fac[i-1]);
			last = 1;
		}	
		else last ++;
	}
	cout << ans << endl;
}
