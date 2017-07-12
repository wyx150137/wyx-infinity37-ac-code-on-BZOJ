
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 300000+5;
using namespace std;

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int a[N],n;

int solve()
{
	int i,j,k=0;
	for(i=0,j=1;i<n && j<n;k=0)
	{ 
		while(a[(i+k)%n] == a[(j+k)%n] && k < n) k ++;if(k == n) break;
		if(a[(i+k)%n] > a[(j+k)%n]) i += k + 1, i = (i==j) ? i + 1 : i;
		else j += k+1, j = (i==j) ? j + 1: j;
	}
	return min(i,j);
}

int main()
{
	n = read();
	for(int i=0;i<n;++i) a[i] = read();
	int tt = solve();
	for(int i=0;i<n-1;++i)
		printf("%d ",a[(tt+i)%n]);
	cout << a[(tt+n-1)%n] << endl;
}
