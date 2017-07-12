
#include <cmath>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
typedef double f2;
const f2 eps = 1e-6;
const f2 inf = 1e9+7;
const int N = 1000+5;

struct poi {
	f2 x,y;
};

struct line {
	poi tmp1,tmp2;
	f2 k,b;
	line () {}
	line (f2 x1,f2 y1,f2 x2,f2 y2) {
		tmp1 = (poi) {x1,y1};
		tmp2 = (poi) {x2,y2};
		k = (tmp2.y - tmp1.y)/(tmp2.x-tmp1.x);
		b = tmp1.y - tmp1.x * k;
	}
	inline f2 f(f2 x) {
		return k*x+b;
	}
}l[N];

int n,tot;
f2 alpha;

struct data{
	double x,r;
}a[N];

f2 f(f2 x) {
	int i; f2 ans = 0;
	for(i=1;i<=n;++i) {
		if(fabs(x-a[i].x)>a[i].r) continue;
		f2 tmp = fabs(x - a[i].x);
		ans = max(ans,sqrt(a[i].r*a[i].r-tmp*tmp));
	}
	for(i=1;i<=tot;++i)  if(x >= l[i].tmp1.x && x <= l[i].tmp2.x) ans = max(ans,l[i].f(x));
	return ans;
}

double calc(f2 fl,f2 fr,f2 fmid,f2 len) {
	return len*(fl+fr+4*fmid)/6.0;
} 

f2 get(f2 l,f2 r,f2 mid,f2 fl,f2 fr,f2 fmid,f2 len) {
	f2 lmid = (l+mid)/2, rmid = (mid+r)/2;
	f2 flmid = f(lmid), frmid = f(rmid);
	f2 L = calc(fl,fmid,flmid,mid-l);
	f2 R = calc(fmid,fr,frmid,r-mid);
	if(fabs(L+R-len)<eps) return len;
	else return get(l,mid,lmid,fl,fmid,flmid,L) + get(mid,r,rmid,fmid,fr,frmid,R);
}

int main() {
	int i; f2 l = inf, r = -inf;
	cin >> n >> alpha; ++n, alpha = 1/(tan(alpha));
	for(i=1;i<=n;++i) {
		scanf("%lf", &a[i].x);
		a[i].x *= alpha;
		a[i].x += a[i-1].x;
	}
	for(i=1;i<n;++i) scanf("%lf",&a[i].r);
	for(i=1;i<=n;++i) {
		l = min(l,a[i].x-a[i].r);
		r = max(r,a[i].x+a[i].r);
	}
	for(i=2;i<=n;++i) {
		f2 L = a[i].x - a[i-1].x;
		if(L - fabs(a[i-1].r-a[i].r) < eps) continue;
		f2 tmp1 =  (a[i-1].r-a[i].r) / L;
		f2 tmp2 = sqrt(1-tmp1*tmp1);
		::l[++tot] = line(a[i-1].x+a[i-1].r*tmp1,a[i-1].r*tmp2,a[i].x+a[i].r*tmp1,a[i].r*tmp2);
	}
	f2 mid = (l+r)/2 ,fl = f(l),fr = f(r), fmid = f(mid);
	printf("%.2lf\n",2*get(l,r,mid,fl,fr,fmid,calc(fl,fr,fmid,r-l)));
}
