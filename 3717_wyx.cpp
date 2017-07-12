
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int Maxn = 16800000;
#define lowbit(x) ((x)&(-x))

int F[Maxn], G[Maxn] , a[Maxn], c[100+5];
int n,m,tmp;

inline bool cmp(const int &a,const int &b) {
	return a > b;
}

int main () {
	cin >> n >> m;
	int all = (1<<n);
	for(int i=1;i<=n;++i) cin >> a[i];
	for(int i=1;i<=m;++i) cin >> c[i];
	sort(c+1,c+m+1,cmp);
	for(int i=n;i;--i) a[1<<(i-1)] = a[i];
	int tmp, x;
	register int i;
	for(i=1;i<all;++i) {
		F[i] = m + 1,G[i] = -1;
		for(int j=i;j;j-=tmp) {
			tmp = lowbit(j);
			x = i - tmp;
			if (a[tmp]<=G[x]&&(F[x]<F[i]||(F[x]==F[i]&&G[x]-a[tmp]>G[i]))) F[i]=F[x],G[i]=G[x]-a[tmp];
			else if((F[x]+1<F[i]||(F[x]+1==F[i]&&c[F[x]+1]>G[i]+a[tmp]))&&c[F[x]+1]>=a[tmp]) F[i]=F[x]+1,G[i]=c[F[i]]-a[tmp];
		}
	}
	if(F[all-1] > m) puts("NIE");
	else cout << F[all-1] << endl;
}
