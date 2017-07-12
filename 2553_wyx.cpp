
#include <queue>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;
const int N = 80+5;
typedef long double ld;
int ch[N][26],fail[N],end[N],cnt,len[6],cov[6];
char sav[6][20];
queue <int> q;
struct Matrix{
	ld a[81][81];
	int n,m;
	Matrix () {}
	Matrix (int _n,int _m) :n(_n),m(_m){ memset(a,0,sizeof a);}
}res;
  
Matrix operator*(const Matrix &a,const Matrix &b){
	Matrix res(a.n,b.m);
	register int i,j,k;
	for(i=0;i<a.n;++i)
		for(j=0;j<b.m;++j)
			for(k=0;k<a.m;++k)
				res.a[i][j] += a.a[i][k]*b.a[k][j];
	return res;
}

int main(){// freopen("flag.in","r",stdin);freopen("flag.out","w",stdout);
	int n,L,k; cin >> n >> L >> k;
	register int i,j;
	int p=0;
	for(i=1;i<=n;++i) scanf("%s",sav[i]+1),len[i] = strlen(sav[i]+1);
	for(i=1;i<=n;++i){
		p = 0;
		for(j=1;j<=len[i];++j){
			if(!ch[p][sav[i][j]-'a']) ch[p][sav[i][j]-'a'] = ++ cnt; p = ch[p][sav[i][j]-'a'];
		}
		end[p] = 1;
	}
	for(j=0;j<k;++j) if(ch[0][j]) q.push(ch[0][j]);
	while(!q.empty()){
		int tt = q.front(); q.pop();
		for(j=0;j<k;++j){
			if(ch[tt][j]){
				q.push(ch[tt][j]);
				for(p=fail[tt];p&&!ch[p][j];p=fail[p]);
				end[ch[tt][j]] |= end[fail[ch[tt][j]]=ch[p][j]];
			}
			else ch[tt][j] = ch[fail[tt]][j];
		}
	}

	Matrix res(1,cnt+2),add(cnt+2,cnt+2);
	res.a[0][0] = 1.000;
	add.a[cnt+1][cnt+1] = 1.000;
	for(i=0;i<=cnt;++i)
		for(j=0;j<k;++j)
			if(end[ch[i][j]]) add.a[i][cnt+1] += (ld)1/k,add.a[i][0] += (ld)1/k;
			else add.a[i][ch[i][j]] += (ld) 1 / k;
	for(;L;L>>=1,add=add*add) if(L&1) res = res * add;
	printf("%.6lf\n",(double)res.a[0][cnt+1]);
}
