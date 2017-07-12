
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 1000000+5;
using namespace std;

int n;
int a[N];

int q[N];

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int k;

int f[N];

void work()
{
	int l = 1;
	int r = 1;
	q[1] = 1;
	for(int i=2;i<=n;++i)
	{
		while(l <= r && q[l] < i - k) l ++;
		f[i] = f[q[l]] + (a[i] >= a[q[l]]);
		while(l <= r && f[q[r]] > f[i]) --r;
		while(f[q[r]] == f[i] && l <= r && a[q[r]] <= a[i]) r --;
		q[++r] = i;
	}
	cout << f[n] << endl;
}

int main()
{
	n = read();
	for(int i=1;i<=n;++i) a[i] = read();
//	for(int i=1;i<=n;++i) cout << a[i] << " " << endl;
	int tmp = read();
	for(int i=1;i<=tmp;++i)
	{
		k = read();
		work();		
	}	
}
