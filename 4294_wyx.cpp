
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
typedef unsigned long long ull;
char str[25];
ull ten[25], v;
ull mod;
int n;

ull mul(ull a,ull b){
	ull ans = 0;
	for(;b;b>>=1,a=(a+a)%mod)
		if(b&1)
			ans = (ans + a) % mod;
	return ans;
		
}

struct Matrix{
	ull a[2][2];
	Matrix () {}
	void init() {
		memset(a,0,sizeof a);
		a[0][0] = a[1][1] = 1;
	}
}a,b;

Matrix &operator * (const Matrix &a,const Matrix &b) {
	static Matrix re;
	memset(re.a,0,sizeof re.a);
	int i,j,k;
	for(i=0;i<2;++i)
		for(j=0;j<2;++j)
			for(k=0;k<2;++k)
				(re.a[i][j] += mul(a.a[i][k],b.a[k][j])) %= mod;
	return re;
}

Matrix &pow(Matrix a,ull b){
	static Matrix re; re.init();
	for(;b;b>>=1,a=a*a)
		if(b&1)
			re = re * a;
	return re;
}

ull calc(ull x){
	a.a[0][0] = 0; 
	a.a[0][1] = a.a[1][0] = a.a[1][1] = 1;
	a = pow(a,x);
	return a.a[0][1];
}

void DFS(ull x,int y) {
	mod = ten[y];
	if(calc(x) != v % ten[y]) return;
	if(y == n) {
		printf("%llu\n",x+6*ten[18]);
		exit(0);
	}
	for(int i=0;i<10;++i) DFS(x+6*ten[y]*i,y+1);
}

int main(){
	scanf("%s",str+1); n = strlen(str+1);
	for(int i=1;i<=n;++i) v = v *10 + str[i] - '0';
	ten[0] = 1;
	for(int i=1;i<=20;++i)ten[i] = ten[i-1]*10;
	for(int i=0;i<60;++i) DFS(i,1);
	puts("NIE");
}
