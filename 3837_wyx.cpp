
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
const int M = 1e7+1;
const int P = 664600;
inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int n, x, a[N], b[N], maxv;
int p[P], tot, ans1, ans2, T;
int last[P], now, v[M], cnt, pos[P];
int tmp[32], fac, vis[P];

struct data{
	int cnt, hash, num;
	data () {
		cnt = hash = 0;
		num = 1;
	}
	data (int _cnt,int _hash,int _num) 
	:cnt(_cnt), hash(_hash), num(_num){}

	bool operator < (const data &z) const {
		return hash < z.hash;
	}
}c[P];

inline void solve(int x,int y) {
	register int i, j, k;
	for(i=0;i<fac;++i) vis[tmp[i]] = 0;
	for(fac=0;x!=1;vis[v[x]]*=p[v[x]],x/=p[v[x]]) 
		if(!vis[v[x]]) 
			tmp[fac++] = v[x], vis[v[x]] = 1;
	for(i=0;i<fac;++i) {
		k = vis[tmp[i]];
		if(last[tmp[i]] ^ T) {
			last[tmp[i]] = T;
			c[j=pos[tmp[i]] = ++now] = data(0,0,k);
		}
		else j = pos[tmp[i]];
		c[j].cnt ++, c[j].hash ^= y;
		if(c[j].num > k) c[j].num = k;
	}
}

int main() {
	c[0].hash = -1;
	n = read();
	register int i,j;
	for(i=0;i<n;++i) {
		a[i] = read();
		while(!b[i]) b[i] = rand();
		if(a[i] > maxv) maxv = a[i];
	}
	for(int i=2;i<=maxv;++i) {
		if(!v[i]) p[v[i] = ++tot] = i;
		for(j=1;p[j]*i<=maxv;++j) {
			v[i*p[j]] = j;
			if(i%p[j] == 0) break;
		}
	}
	for(T=1;T<=4;++T) {
		for(x=a[rand()%n],i=cnt=now=0;i<n;++i) 
			if(a[i] != x) solve(abs(a[i]-x),b[i]);
			else cnt ++;
		sort(c+1,c+now+1);
		for(j=0,i=1;i<=now;++i) 
			if(c[i].hash ^ c[j].hash) {
				if(j) {
					if(c[j].cnt + cnt > ans1) ans1 = c[j].cnt + cnt, ans2 = c[j].num;
					else if(c[j].cnt + cnt == ans1 && c[j].num > ans2) ans2 = c[j].num;
				}
				j = i;
			}
			else 
				c[j].num *= c[i].num;
		if(c[j].cnt + cnt > ans1) ans1 = c[j].cnt + cnt, ans2 = c[j].num;
		else if(c[j].cnt + cnt == ans1  && c[j].num > ans2) ans2 = c[j].num;
	}
	cout <<ans1 << " " << ans2 << endl;
}
