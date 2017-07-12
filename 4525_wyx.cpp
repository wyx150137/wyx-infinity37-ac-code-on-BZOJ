
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 5e5+5;
using namespace std;

int a[N];
int n,k,L=0,R=1e9;

inline bool check(int mid)
{
	int l = 1,cnt = 1;
	for(int i=1;i<=n;++i) if(a[i] - a[l] > 2*mid) cnt ++, l = i;
	return cnt <= k;
}

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9') {if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9') {x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int main()
{
	n = read(),k = read();
	for(int i=1;i<=n;++i) a[i] = read();sort(a+1,a+n+1);
	while(L < R)
	{
		int mid = (L+R) >> 1; if(check(mid)) R = mid ; else L = mid + 1;
	}
	cout << L << endl;
}
