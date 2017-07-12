
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define lowbit(x) ((x)&(-x))
typedef long long LL;
using namespace std;
const int N = 100100+5;
const int inf = 0x7fffffff;
LL tr[N];

inline int read(){
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

struct data{
	int pos;
	LL val;
	int n,m;
	bool operator < (const data &z)const{
		return val < z.val;
	}
}a[N],q[N];

void updata(int x,int val){
	while(x < N){
		tr[x] += val;
		x += lowbit(x);
	}
}

LL ask(int x){
	int ans = 0;
	while(x){
		ans += tr[x];
		x -= lowbit(x);
	}
	return ans;
}

LL F[N],prime[N],mu[N];
LL g[N],cnt;

void init(){
	mu[1] = 1;
	register int i,j;
	for(i=2;i<=N;++i){
		if(!F[i]){
			prime[++cnt] = i;
			mu[i] = -1;
		}
		for(j=1;prime[j]*i<=N;++j){
			F[prime[j]*i] = 1;
			if(i%prime[j] == 0) break;
			mu[prime[j]*i] = -mu[i];
		}
	}
	for(i=1;i<=N;++i) for(j=1;i*j<=N;++j) g[i*j] += i;
	for(i=1;i<=N;++i) a[i].val = g[i], a[i].pos = i;
}

inline int calc(LL x,LL y){
	LL last,i,ans = 0;
	for(i=1;i<=min(x,y);i=last+1){
		last = min(x/(x/i),y/(y/i));
		ans += (x/i)*(y/i)*(ask(last) - ask(i-1));
	}
	return ans&inf;
}

LL ans[N];

int main(){
	init();
	int T = read();
	register int i,j=1,k;
	for(i=1;i<=T;++i) q[i].pos = i, q[i].n = read(), q[i].m = read(), q[i].val = read();
	sort(q+1,q+T+1); sort(a+1,a+N+1);
	for(i=1;i<=T;++i){
		for(;a[j].val <= q[i].val && j <= N;++j)
			for(k=1;k*a[j].pos <= N;++k){
				int tmp = k * a[j].pos;
				updata(tmp,a[j].val*mu[k]);
			}
		ans[q[i].pos] = calc(q[i].n,q[i].m);
	}
	for(int i=1;i<=T;++i)
		printf("%d\n",ans[i]);
}
