
#include <queue>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <iostream>
const int N = 1e5+5;
using namespace std;
typedef long long LL;
typedef pair <LL,int> P;
#define mp make_pair
int n, a[N];
LL m, tmp, now, ans[N];
priority_queue <P,vector<P>,greater<P> >Q;

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

inline bool check(LL x) {
	LL tmp = m;
	for(int i=1;i<=n;++i) {
		tmp -= x / a[i];
		if(tmp < 0) return false;
	}
	return true;
}

int main() {
	cin >> m >> n ;
	LL L = 0, mid = 0, R = 0, ans = 0;
	for(int i=1;i<=n;++i) {
		a[i] = read();
		if(a[i] > R) R = a[i];
	}
	L = R + 1, R = R * m;
	while(L <= R) {
		mid = (L+R) >> 1;
		if(check(mid)) L = (ans = mid) + 1;
		else R = mid - 1;
	}
//	cout << ans << endl;
	int i;
	for(R = ans, i = 1; i <= n; ++i) R = min(R,max((ans/a[i]-1)*a[i],0LL));
	for(i = 1; i <= n; ++i) now += R / a[i], Q.push(mp(R/a[i]*a[i],i));
	while(now<m){
	    P tt=Q.top();Q.pop();
	    ::ans[tt.second]=++now;
	    tt.first+=a[tt.second];
	    Q.push(tt);
  	}
	for(i=1;i<n;i++)printf("%lld ",::ans[i]);printf("%lld",::ans[n]);
}
