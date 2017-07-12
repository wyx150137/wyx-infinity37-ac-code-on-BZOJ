
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 2e5+5;
char str[N];
int sa[N],rank[N],newrank[N],cnt[N],q[N];

inline bool same(int a,int b,int hl,int len){
	if(a+hl>=len||b+hl>=len) return false;
	return rank[a] == rank[b] && rank[a+hl] == rank[b+hl];
}

void build(int len,int lim){
	register int i,j,k;
	for(i=0;i<lim;++i) cnt[i] = 0;
	for(i=0;i<len;++i) ++cnt[rank[i] = str[i]];
	for(i=0;i<lim;++i) cnt[i] += cnt[i-1];
	for(i=len-1;~i;--i)sa[--cnt[rank[i]]] = i;
	for(int d=1;;d++){
		int hl = 1<<(d-1), id = 0;
		for(i=0;i<len;++i) if(sa[i]+hl>=len) q[id++] = sa[i];
		for(i=0;i<len;++i) if(sa[i] >= hl) q[id++] = sa[i]-hl;
		for(i=0;i<lim;++i) cnt[i] = 0;
		for(i=0;i<len;++i) cnt[rank[q[i]]] ++;
		for(i=0;i<lim;++i) cnt[i] += cnt[i-1];
		for(i=len-1;~i;--i) sa[--cnt[rank[q[i]]]] = q[i];
		lim = 0 ;
		for(i=0;i<len;++lim) {
			for(j=i;same(sa[j],sa[j+1],hl,len)&&j<len-1;++j);
			for(k=i,i=j+1;k<=j;++k) newrank[sa[k]] = lim;
		}
		if(lim == len) break;
		for(i=0;i<len;++i) rank[i] = newrank[i];
	}
} 

int main(){
	scanf("%s",str); int len = strlen(str);
	for(int i=0;i<len;++i) str[i+len] = str[i];
	build(len<<1,256); for(int i=0;i<len<<1;++i) 
	if(sa[i] < len) putchar(str[sa[i]+len-1]);
}
