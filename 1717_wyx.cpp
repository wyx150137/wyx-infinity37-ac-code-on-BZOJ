
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 40000+5;
#define max(a,b) ((a)>(b)?(a):(b))
using namespace std;

int sa[N],a[N],rank[N],cnt[N],q[N],n;
int newrank[N],h[N];

inline bool same(int a,int b,int hl,int len){
	if(a+hl>len||b+hl>len) return false;
	return rank[a] == rank[b] && rank[a+hl] == rank[b+hl];
}

void get(int len,int lmt){
	register int i,j,k;
	for(i=0;i<lmt;++i) cnt[i] = 0;
	for(i=0;i<len;++i) cnt[rank[i]=a[i]] ++;
	for(i=1;i<lmt;++i) cnt[i] += cnt[i-1];
	for(i=len-1;~i;--i) sa[--cnt[rank[i]]] = i;
	for(int d=1;;d++){
		int hl = 1<<(d-1),id = 0;
		for(i=0;i<len;++i) if(sa[i]+hl>=len) q[id++] = sa[i];
		for(i=0;i<len;++i) if(sa[i]>=hl) q[id++] = sa[i]-hl;
		for(i=0;i<lmt;++i) cnt[i] = 0;
		for(i=0;i<len;++i) cnt[rank[q[i]]] ++;
		for(i=1;i<lmt;++i) cnt[i] += cnt[i-1];
		for(i=id-1;~i;--i) sa[--cnt[rank[q[i]]]] = q[i];
		for(i=lmt=0;i<len;i=k+1,lmt++){
			for(k=i;k<len-1&&same(sa[k],sa[k+1],hl,len);++k);
			for(j=i;j<=k;++j) newrank[sa[j]] = lmt;
		}
		if(lmt == len) break;
		for(i=0;i<len;++i) rank[i] = newrank[i];
	}
	for(i=0;i<len;++i) rank[sa[i]] = i;
	for(i=0;i<len;++i)
		if(rank[i]){
			j = 0; if(i) j = max(h[rank[i-1]]-1,0);
			for(;i+j<len&&sa[rank[i]-1]+j<len&&a[i+j]==a[sa[rank[i]-1]+j];++j);
			h[rank[i]] = j;
		}
}

inline int read(){
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int k;

inline bool check(int mid){
	int ans = 0,tt = 0,i;
	for(i=0;i<n;++i){
		if(h[i] >= mid){
			tt ++;
			if(tt == k-1)
				return true;
		}
		else tt = 0;
	}
	return false;
}

int main(){//	freopen("03.in","r",stdin);
	n = read(), k = read();
	for(int i=0;i<n;++i) a[i] = read(); 
	get(n,256);
	int l = 1, r = n;
	while(l<r){
		int mid = (l+r) >> 1;
		if(check(mid))
			l = mid + 1;
		else r = mid;
	}
	cout << l-1 << endl;
}	
