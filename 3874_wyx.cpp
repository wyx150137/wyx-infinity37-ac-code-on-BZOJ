
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

inline LL read() {
	LL x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}  

struct data {
	LL p, s;
	bool operator < (const data &z) const {
		return s ^ z.s ? s < z.s : p < z.p;
	}
} a[300+5];

bool cmp(const data &a,const data &b) {
	return a.p < b.p;
}

LL m, f, n;  

inline LL F(LL x) {
	LL sum = m - f * x;
	LL maxt = 0, ret = 0, temp;
	if(sum < 0) return 0;
	for(int i=1;i<=n;++i) {
		if(maxt <= a[i].s) {
			temp = a[i].s - maxt + 1;
			temp = min(temp, sum /(a[i].p*x));
			ret += temp * x;
			sum -= a[i].p * x * temp;
			maxt += temp;
		}
		if(maxt <= a[i].s) {
			temp = min(x, sum / a[i].p);
			ret += temp;
			sum -= temp * a[i].p;
			maxt ++;
		}
	}
	return ret;
}

int main() {  
	m = read(), f = read(), n = read();
	for(int i=1;i<=n;++i) a[i].p = read(), a[i].s = read();
	sort(a+1,a+n+1);
	int top = 1;
	for(int i=2;i<=n;++i) 
		if(a[i].s > a[top].s) a[++top] = a[i];
	n = top;
	sort(a+1,a+n+1,cmp);
	LL L = 1, R = m / (f+a[1].p);
	LL ans = 0;
	while(L <= R - 10) {
		LL len = (R-L+1) / 3;
		LL temp1 = L + len;
		LL temp2 = R - len;
		LL all1 = F(temp1), all2 = F(temp2);
		if(all1 < all2) ans = max(ans, all1), L = temp1;
		else ans = max(ans, all2), R = temp2;
	}
	for(LL i = L; i <= R; ++i) ans = max(ans, F(i));
	cout << ans << endl;
}  
