
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 5e4+5;
using namespace std;

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

#define max(a,b) ((a)>(b)?(a):(b))

int a[N],n;
int Len[N];

int main()
{
	int n = read(),k = read();
	for(int i=1;i<=n;++i) a[i] = read();

	sort(a+1,a+n+1);
	int l = 1;
	int r = 1;
	
	while(l <= n )
	{
		while(a[r] - a[l] <= k && r <= n) r ++;
		Len[l] = r - l; l ++;
	}

	int ans = 0;

	for(int i=n;i>=1;--i)
	{
		ans = max(ans,Len[i] + Len[i+Len[i]]);
		Len[i] = max(Len[i],Len[i+1]);
	}

	cout << ans << endl;
} 
