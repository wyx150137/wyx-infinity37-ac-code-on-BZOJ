
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 1e4;
using namespace std;

int sa[N],cnt[N],h[N],rank[N],newrank[N],q[N];
char str[N];

inline bool same(int a,int b,int hl,int len){
	if(a+hl>len||b+hl>len)return false;
	return rank[a] == rank[b] && rank[a+hl] == rank[b+hl];
}

void get(int len,int lmt){
	register int i,j,k;
	for(i=0;i<lmt;++i) cnt[i] = 0;
	for(i=0;i<len;++i) cnt[rank[i]=str[i]-'0'] ++;
	for(i=1;i<lmt;++i) cnt[i] += cnt[i-1];
	for(i=len-1;~i;--i)sa[--cnt[rank[i]]] = i;
	for(int d=1;;d++){
		int id = 0, hl = 1<<(d-1);
		for(i=0;i<len;++i) if(sa[i]+hl>=len) q[id++] = sa[i];
		for(i=0;i<len;++i) if(sa[i]>=hl) q[id++] = sa[i]-hl;
		for(i=0;i<lmt;++i) cnt[i] = 0;
		for(i=0;i<len;++i) cnt[rank[q[i]]] ++;
		for(i=1;i<lmt;++i) cnt[i] += cnt[i-1];
		for(i=id-1;~i;--i) sa[--cnt[rank[q[i]]]] = q[i];
		for(i=lmt=0;i<len;lmt++,i=j+1){
			for(j=i;same(sa[j],sa[j+1],hl,len)&&j<len-1;++j);
			for(k=i;k<=j;++k) newrank[sa[k]] = lmt;
 		}
 		if(lmt == len) break;
 		for(i=0;i<len;++i) rank[i] = newrank[i];
	}
	for(i=0;i<len;++i) rank[sa[i]] = i;
	for(i=0;i<len;++i) 
		if(rank[i]){
			j = 0; if(i) j = max(0,h[rank[i-1]]-1);
			for(;i+j<len&&sa[rank[i]-1]+j<len&& str[sa[rank[i]-1]+j]==str[i+j];j++);
			h[rank[i]] = j;
		}
}

int main(){
	register int i,j,l,r;
	int len;cin>>len;
	scanf("%s",str);
	get(len,256);
//	for(i=0;i<len;++i) cout << rank[i] << " " ; puts("");
	for(i=0;i<len;++i)
		for(j=h[i]+1;sa[i]+j<=len;++j){
			for(l=i;~l&&h[l]>=j;--l);
			for(r=i+1;r<len&&h[r]>=j;++r);
			if(r-l>1) printf("%d\n",r-l);
		}
}
