
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 6e4+5;
using namespace std;

int rank[N],newrank[N],cnt[N],sa[N],q[N];
char tmp[5],str[N];

inline bool same(int a,int b,int hl,int len){
	if(a+hl>len||b+hl>len) return false;
	return rank[a] == rank[b] && rank[a+hl] == rank[b+hl];
}

void get(int len,int lmt){
	register int i,j,k;
	for(i=0;i<lmt;++i) cnt[i] = 0;
	for(i=0;i<len;++i) cnt[rank[i] = str[i]] ++;
	for(i=1;i<lmt;++i) cnt[i] += cnt[i-1];
	for(i=len-1;~i;--i)sa[--cnt[rank[i]]] = i;
	for(int d=1;;d++){
		int id = 0, hl = 1<<(d-1);
		for(i=0;i<len;++i) if(sa[i]+hl>=len) q[id++] = sa[i];
		for(i=0;i<len;++i) if(sa[i] >= hl) q[id++] = sa[i]-hl;
		for(i=0;i<lmt;++i) cnt[i] = 0;
		for(i=0;i<len;++i) cnt[rank[q[i]]] ++;
		for(i=1;i<lmt;++i) cnt[i] += cnt[i-1];
		for(i=id-1;~i;--i) sa[--cnt[rank[q[i]]]] = q[i];
		for(i=lmt=0;i<len;i=j+1,lmt++){
			for(j=i;same(sa[j],sa[j+1],hl,len)&&j<len-1;++j) ;
			for(k=i;k<=j;++k) newrank[sa[k]] = lmt;
		}
		if(lmt == len) break;
		for(i=0;i<len;++i) rank[i] = newrank[i];
	}
	for(i=0;i<len;++i) rank[sa[i]] = i;

}

int main(){
	int n,i,j,times = 0; cin >> n;
	for(i=0;i<n;++i){
		scanf("%s",tmp);
		str[i] = tmp[0];
	}
	str[n] = 0; 
	for(i=n+1;i<=n+n;++i) str[i] = str[n+n-i];
	get(n<<1|1,256);
	for(i=0,j=n+1;i+j<=2*n;times++){
		if(times == 80) putchar('\n'), times = 0;
		if(rank[i] < rank[j]) putchar(str[i++]);
		else putchar(str[j++]);
	}
}
