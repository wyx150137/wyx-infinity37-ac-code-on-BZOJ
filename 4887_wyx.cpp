
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int mod = 2017;

struct Matrix {
	int n, m;
	int a[35][35];
	int sum;
	Matrix () {
		sum = 0;
		memset(a, 0, sizeof a);
	};
	Matrix (int x,int y) {
		n=x;
		m=y;
		sum = 0;
		memset(a,0,sizeof a);
	}
	void out() {
		for(int i=1;i<=n;++i) {
			for(int j=1;j<=m;++j)
				cout << a[i][j] << ' ';
			puts("");
		}
	}
}a,b;

Matrix operator *(Matrix a,Matrix b) {
	Matrix c(b.n,a.m);
	for(int i=1;i<=c.n;i++)
		for(int j=1;j<=c.m;j++) {
			for(int k=1;k<=a.n;k++)
				(c.a[i][j]+=a.a[k][j]*b.a[i][k]%mod)%=mod;
			(c.sum += c.a[i][j]) %= mod;
		}
	return c;
}

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int main() {
//	freopen("tt.in","r",stdin);
	int n = read(), m = read();
	a.n = n+1, a.m = 1;
	a.a[1][1] = 1;
	b.n = b.m = n + 1;
	for(int i=1;i<=m;++i) {
		int x = read(), y = read();
		b.a[x][y] ++; b.a[y][x] ++;
	}
	for(int i=1;i<=n+1;++i) b.a[i][i] = 1, b.a[n+1][i] = 1;
	int temp; 
	cin >> temp;
	for(;temp;temp>>=1,b=b*b)
		if(temp&1)
			a = a * b;
	cout << a.sum << endl;
}
