
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1e6+5;
typedef long long LL;	

inline LL read() {
	LL x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int n, q;
LL a[N];

int main() {
	LL sum = 0;
	n = read(), q = read();
	for(int i=0;i<n;++i) a[i] = read(), (sum += (a[i]*i))%=(n-1);
	if(sum) a[sum] --;
	for(int i=1;i<n;++i) a[i] = a[i] + a[i-1];
	LL tmp;
	for(int i=1;i<=q;++i) {
		tmp = read();
		int ans = upper_bound(a,a+n,tmp)-a;
		if(ans == n) puts("-1");
		else printf("%d\n",ans);
	}
}
