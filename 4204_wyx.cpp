
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 1000+5;
using namespace std;

int n,m,k;

struct Matrix
{
	double a[N];
	Matrix () 
	{
		memset(a,0,sizeof a);
	}
}a,b,c;

Matrix operator *(Matrix &a,Matrix &b)
{
	Matrix res;
	int i,j;
	for(i=0;i<n;++i)
		for(j=0;j<n;++j)
			res.a[i] += a.a[j]*b.a[(i-j+n)%n];
	return res;
}	

int main()
{
	cin >> n >> m >> k;
	if(n==1){ printf("%.3lf\n",1.0*m); return 0; }
	for(int i=0;i<n;++i) scanf("%lf",&a.a[i]);
	b.a[0] = 1, c.a[0] = -1.0/m+1,c.a[1] = 1.0/m;
	for(;k;k>>=1,c=c*c)if(k&1) b = b*c; a = a * b;
	for(int i=0;i<n;++i) printf("%.3lf\n",a.a[i]);
	return 0;
}
