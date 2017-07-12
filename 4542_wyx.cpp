
#include <map>
#include <cmath>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 300010+5;
typedef long long LL;
LL mod;
char str[N];
LL a[N], T[N],E[N],sum[N], cnt[N];
map <LL,int> mp;

struct data{
	int l, r, id, blo;
	bool operator < (const data &z) const {
		return blo ^ z.blo ? blo < z.blo : r < z.r;
	}
}q[N];

LL ans = 0;

inline void updata(int x,int val) {
	if(val == 1) {
		int tmp = a[x];
		ans += E[T[tmp]+1] - E[T[tmp]];
		T[tmp] ++;
	}
	else {
		int tmp = a[x];
		ans -= E[T[tmp]] - E[T[tmp]-1];
		T[tmp] --;
	}
}

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

LL G[N];

int main() {//freopen("A.in","r",stdin);freopen("A.out","w",stdout);
	cin >> mod; scanf("%s",str+1); int len = strlen(str+1);
	if(mod == 2 || mod == 5) {
		for(int i=1;i<=len;++i) sum[i] = sum[i-1] + ((str[i]-'0')%mod == 0 ? i : 0);
		for(int i=1;i<=len;++i) cnt[i] = cnt[i-1] + ((str[i]-'0')%mod == 0 ? 1 : 0);
		int Q = read();
		for(int i=1;i<=Q;++i) {
			int l = read(), r = read();
			printf("%lld\n", sum[r]-sum[l-1]-(LL)(cnt[r]-cnt[l-1])*(l-1));
		}
		return 0;
	}
	for(int i=len, base = 1;i;--i, base = (LL)base * 10 % mod) a[i] = (a[i+1]+(LL)(str[i]-'0')*base%mod)%mod;
	for(int i=1;i<=len+1;++i) T[i] = a[i]; sort(T+1,T+len+2);
	for(int i=1;i<=len+1;++i) mp[T[i]] = i; 
	for(int i=1;i<=len+1;++i) a[i] = mp[a[i]];
	memset(T,0,sizeof T);
	for(int i=1;i<=len;++i) E[i] = E[i-1]+i-1;
	int sz = (int)(sqrt(len)+0.5), Q = read();
	for(int i=1;i<=Q;++i)  q[i].l = read(), q[i].r = read()+1, q[i].blo = q[i].l / sz, q[i].id = i;
	sort(q+1,q+Q+1);
	int l = 1, r = 0;
	for(int i=1;i<=Q;++i) {
		while(r<q[i].r) updata(++r,+1);
		while(r>q[i].r) updata(r--,-1);
		while(l<q[i].l) updata(l++,-1);
		while(l>q[i].l) updata(--l,+1);
		G[q[i].id] = ans;
	}
	for(int i=1;i<=Q;++i) printf("%lld\n", G[i]); 
}
