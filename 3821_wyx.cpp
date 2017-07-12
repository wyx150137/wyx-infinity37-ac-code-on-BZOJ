
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 4e5+5;
typedef long long LL;
int n,mod,x,y;
int z,a,b,q;
int val[N],cnt;
struct seg{
	int l,r;
}tr[N];

inline int read(){
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

struct data{
	data () {}
	data (int _x,int _y,int _a,int _b):x(_x),y(_y),a(_a),b(_b){}
	int x,y,a,b;
}p[N*10];

void merge(int k){
	int l1 = tr[k<<1].l,l2 = tr[k<<1|1].l, l = 1;
	for(tr[k].l = cnt + 1; l <= n ; ){
		if(p[l1].y < p[l2].y){
			p[++cnt] = data(l,p[l1].y,(LL)p[l1].a*p[l2].a%mod,((LL)p[l1].b*p[l2].a+p[l2].b)%mod);
			l = p[l1].y + 1; l1 ++; continue;
		}
		if(p[l1].y > p[l2].y){
			p[++cnt] = data(l,p[l2].y,(LL)p[l1].a*p[l2].a%mod,((LL)p[l1].b*p[l2].a+p[l2].b)%mod);
			l = p[l2].y + 1; l2 ++; continue;
		}
		if(p[l1].y == p[l2].y){
			p[++cnt] = data(l,p[l1].y,(LL)p[l1].a*p[l2].a%mod,((LL)p[l1].b*p[l2].a+p[l2].b)%mod);
			l = p[l1].y + 1,l1 ++, l2 ++; continue;
		}
	}
	tr[k].r = cnt;
}

inline void updata(int l,int r,int pos){
	while(l<r){
		int mid = (l+r) >> 1;
		if(p[mid].y < pos) l = mid + 1;
		else r = mid ; 
	}
	a = (LL)a*p[l].a%mod;
	b = ((LL)b*p[l].a + p[l].b)%mod;
}

void change(int k,int l,int r,int pos){
	if(l==r){
		tr[k].l = ++cnt;
		if(x != 1) p[cnt] = data(1,x-1,1,0);
		p[++cnt]  = data(x,y,a,b);
		if(y != n) p[++cnt] = data(y+1,n,1,0);
		tr[k].r = cnt;
		return;
	}
	int mid = (l+r) >> 1;
	if(pos <= mid) change(k<<1,l,mid,pos);
	else change(k<<1|1,mid+1,r,pos);
	if(pos == r) merge(k);
}

void ask(int k,int l,int r,int x,int y){
	if(x <= l && r <= y){
		updata(tr[k].l,tr[k].r,z);
		return;
	}
	int mid = (l+r) >> 1;
	if(x <= mid) ask(k<<1,l,mid,x,y);
	if(y > mid) ask(k<<1|1,mid+1,r,x,y); 
}

int main(){
	int tt = read(); tt %= 2;
	n = read(), mod = read();
	register int i;
	for(i=1;i<=n;++i) val[i] = read();
	q = read();
	int lastans = 0;
	int sum = 0;
	int Max = min(q,100000);
	for(i=1;i<=q;++i){
		int opt = read();
		if(opt == 1){
			x = read(), y = read(), a = read(), b = read();
			x ^= lastans * tt, y ^= lastans * tt;
			change(1,1,Max,++sum);
		}
		else{
			x = read() ^ (lastans*tt), y = read() ^ (lastans*tt), z = read() ^ (lastans*tt);
			a = 1, b = 0;
			ask(1,1,Max,x,y);
			lastans = ((LL)a*val[z]+b) % mod;
			printf("%d\n",lastans);
		}
	}
}
