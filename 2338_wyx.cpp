
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1600+5;
typedef long long LL;

inline LL read() {
	LL x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

struct poi {
	LL x,y;
	poi () {}
	poi (LL _x,LL _y):x(_x),y(_y){}
	inline bool operator == (const poi &z) const { return x == z.x && y == z.y;	}
	poi operator - (const poi &z) const {return poi(x-z.x,y-z.y);}
	LL operator * (const poi &z) const {return x*z.y-y*z.x;	}
} a[N];

struct line {
	LL len;
	poi *tmp1,*tmp2, mid;
	bool operator < (const line &z) const {
		if(len == z.len) return mid.x ^ z.mid.x ? mid.x < z.mid.x : mid.y < z.mid.y;
		return len < z.len;
	}
}l [N*N];

inline LL dis(const poi &a,const poi &b) {return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);}
inline LL labs(LL x) {return x < 0 ? -x : x;}

int n, tot; LL ans;

int main() {
	register int i, j;
	n = read();
	for(i=1;i<=n;++i) {
		a[i].x = read(), a[i].y = read();
		for(j=1;j<i;++j) {
			l[++tot].len = dis(a[i],a[j]);
			l[tot].tmp1 = &a[i], l[tot].tmp2 = &a[j];
			l[tot].mid = poi(a[i].x+a[j].x,a[i].y+a[j].y);
		}
	}
	sort(l+1,l+tot+1);
	for(i=1;i<=tot;++i) for(j=i-1;j && l[i].len == l[j].len && l[i].mid == l[j].mid; --j) 
		ans = max(ans,labs( ( (*l[i].tmp1)-(*l[j].tmp1) )*( (*l[i].tmp1)-(*l[j].tmp2) ) ) );
	cout << ans << endl;
}

