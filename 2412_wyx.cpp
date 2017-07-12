
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N=2005,inf=~0U>>1;
int M,n,a[N],f[N][N];
inline void up(int&a,int b){ if(a>b)a=b; }
struct ZKW{
	int v[4100];
	inline void ask(int x,int y,int&t) {
		if(x>y)return;
		for(x+=M-1,y+=M+1;x^y^1;x>>=1,y>>=1) {
			if(~x&1)up(t,v[x^1]);
			if(y&1)up(t,v[y^1]);
		}
	}
	inline void ins(int x,int y) {
		for(x+=M;x;x>>=1)up(v[x],y);
	}
	inline void build() {
		for(int i=1;i<=n+M;i++)v[i]=inf;
	}
}T1[N],T2[N];
inline void add(int x,int y){
	if(x>1) T1[y].ins(x-1,f[x][y]+a[x-1]);
	if(y<n) T2[x].ins(y+1,f[x][y]+a[y+1]);
}
int main(){
	scanf("%d",&n);
	register int i, j, g;
	for(M=1;M<n+2;M<<=1);
	for(i=1;i<=n;i++) scanf("%d",&a[i]), T1[i].build(), T2[i].build();
	for(i=1;i<=n;i++) add(i,i-1);
	for(i=1;i<=n;i++) f[i][i] = a[i],add(i,i);
	for(i=n;i;i--)
		for(g=i,j=i+1;j<=n;j++) {
			while(g<=j&&f[i][g-1]<f[g+1][j])g++;
			f[i][j]=inf;
			T1[j].ask(i,g-1,f[i][j]);
			T2[i].ask(g,j,f[i][j]);
			add(i,j);
		}
	return 0*printf("%d",f[1][n]);
}
