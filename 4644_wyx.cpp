
#include <vector>
#include <bitset>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N =  1000+5;
const int Max = 1000;
typedef bitset<N> Int;
#define pb push_back
Int a[N], b[N<<2], ans[N];

struct data{
	Int temp[N];

	inline void insert(Int x) {
		for(int i=Max;i>=0;--i) if(x[i]){
			if(!temp[i][i]) {temp[i] = x; break;}
			else x ^= temp[i];
		}
	}

	inline Int ask() {
		Int ans;
		for(int i=Max;i>=0;--i) {
			if(!ans[i] && temp[i][i])
				ans ^= temp[i];
		}
		return ans;
	}
} temp[30];

vector <int> V[N<<2];

inline void insert(int k,int l,int r,int x,int y,int val) {
	if(x <= l && r <= y)  {
		V[k].pb(val);
		return;
	}
	int mid = (l+r) >> 1;
	if(x <= mid) insert(k<<1,l,mid,x,y,val);
	if(y > mid) insert(k<<1|1,mid+1,r,x,y,val);
}

inline void change(int k,int l,int r,int x,int y,const Int &val) {
	static int cnt = 0;
	b[++cnt] = val;
	insert(k,l,r,x,y,cnt);
}

inline void build(int k,int l,int r,int depth) {
	temp[depth] = temp[depth-1];
	for(int i=0;i<V[k].size();++i) temp[depth].insert(b[V[k][i]]);
	if(l==r) {
		ans[l] = temp[depth].ask();
		return;
	}
	int mid = (l+r) >> 1;
	build(k<<1,l,mid,depth+1);
	build(k<<1|1,mid+1,r,depth+1);
}

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int pre[N];
char str[N];
Int tt;

int main() {
//	freopen("tt.in","r",stdin);
	read();
	int n = read(), m = read();
	register int j;
	for(int i=1;i<=m;++i) {
		tt.reset();
		int x = read(), y = read();
		scanf("%s", str+1);
		int len = strlen(str+1);
		for(j=len;j>=1;--j) {
			tt[len-j] = (str[j] == '1');
		}
		change(1,0,m,pre[x],i-1,a[x]);
		change(1,0,m,pre[y],i-1,a[y]);
		pre[x] = i;
		pre[y] = i;
		a[x] ^= tt;
		a[y] ^= tt;
	}
	for(int i=1;i<=n;++i) 
		change(1,0,m,pre[i],m,a[i]);
	build(1,0,m,1);
	for(int i=1;i<=m;++i) {
		for(j=Max;j>=0 && !ans[i][j];--j);
		if(j == -1) puts("0");
		else { 
			for(;~j;--j) printf("%d", ans[i][j] ? 1 : 0);
			puts("");
		}
	}
}
