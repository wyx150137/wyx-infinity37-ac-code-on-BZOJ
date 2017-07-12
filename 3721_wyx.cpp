
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1e6+5;
using namespace std;
typedef long long LL;

inline bool cmp(const int &a,const int &b) {
	return a > b;
}

int a[N],b,t;
LL sum[N];
LL pre0[N], pre1[N], suf0[N], suf1[N];

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int main () {
	int n = read();
	for(int i=1;i<=n;++i) a[i] = read();
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;++i) sum[i] = sum[i-1] + a[i];
	pre0[0] = pre1[0] = -1;
	for(int i=1;i<=n;++i) {
		if(a[i] & 1) pre0[i] = pre0[i-1], pre1[i] = a[i];
		else pre1[i] = pre1[i-1] , pre0[i] = a[i];
	}
	suf0[n+1] = suf1[n+1] = -1;	
	for(int i=n;i;--i) {
		if(a[i] & 1) suf0[i] = suf0[i+1], suf1[i] = a[i];
		else suf1[i] = suf1[i+1] , suf0[i] = a[i];
	}
	int T = read();
	while(T -- ) {
		int k = read();
		if(sum[k] & 1) printf("%lld\n",sum[k]);
		else {
			LL ans = -1;
			if(~pre0[k] && ~suf1[k+1]) ans = max(ans,sum[k]-pre0[k]+suf1[k+1]);
			if(~pre1[k] && ~suf0[k+1]) ans = max(ans,sum[k]-pre1[k]+suf0[k+1]);
			printf("%lld\n",ans);
		}
	}
}
