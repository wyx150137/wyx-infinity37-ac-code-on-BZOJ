
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
const LL N = 1e5+5;
const LL inf = 1e16;

LL a[N], b[N], n, m;
LL sum1[N], sum2[N];

inline LL read() {
	LL x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

inline LL find1(LL *a,LL lmt,LL val) {
	LL l = 1, r = lmt + 1;
	while(l<r) {
		LL mid = (l+r) >> 1;
		if(a[mid] <= val) l = mid + 1;
		else r = mid;
	}
	return l;
}

inline LL find2(LL *a,LL lmt,LL val) {
	LL l = 1, r = lmt + 1;
	while(l<r) {
		LL mid = (l+r) >> 1;
		if(a[mid] < val) l = mid + 1;
		else r = mid;
	}
	return l - 1;
}

int main() {
//	freopen("exam.in","r",stdin);
//	freopen("exam.out","w",stdout);
	LL A, B, C;
	cin >> A >> B >> C;
	LL ans = inf;
	LL Min = inf, Max = 0;
	n = read(), m = read();
	for(LL i=1;i<=n;++i) a[i] = read(), Min = min(Min, (LL)a[i]);
	for(LL i=1;i<=m;++i) b[i] = read(), Max = max(Max, (LL)b[i]);
	sort(a+1,a+n+1);
	sort(b+1,b+m+1);
	for(LL i=1;i<=n;++i) sum1[i] = sum1[i-1] + a[i];
	for(LL i=1;i<=m;++i) sum2[i] = sum2[i-1] + b[i];
	LL tmp1 = Max,  tmp2 = Min;
	if(tmp1 <= tmp2) {
		puts("0");
		return 0;
	}
	if(C == inf) tmp1 = tmp2 = Min;
	if(B <= A) {
		for(LL i=tmp1;i>=tmp2;--i) {
			LL tmp = 0;
			LL pos1 = find1(b, m, i);
			tmp += ((LL) sum2[m] - sum2[pos1-1] - (LL)(m-pos1+1)*i) * B;
			LL pos2 = find2(a, n, i);
			tmp += ((LL) pos2 * i - sum1[pos2]) * C;
			ans = min(ans, tmp);
		}
	}
	else {
		for(LL i=tmp1;i>=tmp2;--i) {
			LL tmp = 0;
			if(sum2[m] <= (LL)i*m) {
				LL pos = find1(b , m, i);
				tmp += ((LL)sum2[m]-sum2[pos-1]-(LL)(m-pos+1)*i)*A;
			}
			else {
				LL pos = find1(b, m, i);
				tmp += ((LL)i*(pos-1)-sum2[pos-1]) * A + (sum2[m]-(LL)i*m)*B;
			}
			LL pos = find2(a, n, i);
			tmp += ((LL)pos*i-sum1[pos]) * C;
			ans = min(ans, tmp);
		}
	}
	cout << ans << endl;
}
