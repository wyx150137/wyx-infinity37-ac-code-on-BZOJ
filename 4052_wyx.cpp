
#include <cmath>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 100000+5;

inline LL read() {
	LL x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

LL F[N][18], a[N];

inline LL calc(int x,int y) {
	int len = y - x + 1, tt = (int)log2(len);
	return __gcd(F[x][tt],F[y-(1<<tt)+1][tt]);
}

int main() {//freopen("tt.in","r",stdin);
	int T = read();
	while(T-- ){
		int n = read();
		for(int i=1;i<=n;++i) a[i] = read();
		for(int i=1;i<=n;++i) F[i][0] = a[i];
		for(int i=n;i;--i) for(int j=1;j<=17;++j) 
			if(i+(1<<j)-1<=n) F[i][j] = __gcd(F[i][j-1],F[i+(1<<(j-1))][j-1]);
		LL ans = 0;
		for(int i=1;i<=n;++i) {
			int last = i-1, l, r;
			LL lastg = a[i];
			while(last != n) {
				l = last + 1, r = n + 1;
				while(l<r) {
					int mid = (l+r) >> 1;
					if(calc(i,mid) == lastg) l = mid + 1;
					else r = mid;
				}
				l --;
				ans = max(ans,lastg*(l-i+1));
				last = l; lastg = __gcd(lastg,a[l+1]);
			}
		}
		printf("%lld\n", ans);
	}
}
