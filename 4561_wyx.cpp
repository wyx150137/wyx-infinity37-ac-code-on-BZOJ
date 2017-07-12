
#include <cmath>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
#define fir first
#define sec second
#define mp make_pair
const int N = 4e5+5;
typedef long long LL;
typedef double f2;
int n, m, tot, cnt, root;
LL now;
int rnd[N], ls[N], rs[N], tr[N], val[N], id[N];

inline LL read() {
	LL x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

struct data {
	LL x,y,r;
	void R() {
		x = read(), y = read(), r = read();
	}
	bool operator < (const data &z) const {
		return x - r < z.x - z.r;
	}
}c[N];

pair <LL,int> x[N];

inline void updata(int k) {
	tr[k] = tr[ls[k]] + tr[rs[k]]+ val[k];
}

inline void lturn(int &k) {
	int t = rs[k]; rs[k] = ls[t]; ls[t] = k;
	updata(k); updata(t); k = t;
}

inline void rturn(int &k) {
	int t = ls[k]; ls[k] = rs[t]; rs[t] = k;
	updata(k); updata(t); k = t;
}

inline f2 calc(int x,int k) {
	f2 tmp = (c[x].x-now)*(c[x].x-now);
	tmp = sqrt(c[x].r*c[x].r-tmp);
	if(k==1) return c[x].y + tmp;
	else return c[x].y - tmp;
}

inline void insert(int &x,int p,int k) {
	if(!x) {
		x = ++cnt; rnd[x] = rand();
		tr[x] = val[x] = k; id[x] = p;
		return;
	}
	tr[x] += k;
	if(calc(id[x],val[x]) < calc(p,k) || (calc(id[x],val[x])==calc(p,k) && k > val[x])) {
		insert(ls[x],p,k);
		if(rnd[ls[x]] < rnd[x]) rturn(x);
	}
	else {
		insert(rs[x],p,k);
		if(rnd[rs[x]] < rnd[x]) lturn(x);
	}
}

void del(int &x,int p,int k) {
	if(id[x] == p && val[x] == k) {
		if(!ls[x] || !rs[x]) x = ls[x] + rs[x];
		else if(rnd[ls[x]] < rnd[rs[x]]) rturn(x), del(x,p,k);
		else lturn(x),del(x,p,k);
		return;
	}
	tr[x] -= k;
	if(calc(id[x],val[x]) < calc(p,k) || (calc(id[x],val[x]) == calc(p,k) && k > val[x])) del(ls[x],p,k);
	else del(rs[x],p,k);
}

inline int find(int tt) {
	int x = root, ans = 0;
	while(x) {
		if(calc(id[x],val[x]) > tt) {
			ans += tr[ls[x]] + val[x];
			x = rs[x];
		} 
		else x = ls[x];
	}
	return ans;
}

int main() { srand(150137);
	cin >> n; LL ans = 0;
	for(int i=1;i<=n;++i)  {
		c[i].R();
		x[++tot] = mp(c[i].x-c[i].r,i);
		x[++tot] = mp(c[i].x+c[i].r,-i);
	}
	sort(x+1,x+tot+1);
	for(int i=1;i<=tot;++i) {
		now = x[i].fir;
		if(x[i].sec > 0) {
			int k = find(c[x[i].sec].y);
			if(~k & 1) ans += c[x[i].sec].r * c[x[i].sec].r;
			else ans -= c[x[i].sec].r * c[x[i].sec].r;
			insert(root,x[i].sec,1);
			insert(root,x[i].sec,-1);
		}
		else {
			del(root,-x[i].sec,1);
			del(root,-x[i].sec,-1);
		}
	}
	cout << ans << endl;
}
