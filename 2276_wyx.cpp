
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define max(a,b) ((a)>(b)?(a):(b))
const int N = 1000000+5;

using namespace std;

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int L[N],R[N];

int q[N];

int main()
{
	int n = read();
	for(int i=1;i<=n;++i) L[i] = read() , R[i] = read();
	int l = 1,r = 0,ans = 1;L[0] = -1e9;R[n+1] = 1e9;
	int i = 1,j = 1;q[1] = 1;
	for(i=1;i<=n;++i)
	{
		if(j==i) ++j;
		if(q[l] == i-1) ++l;
		while(j<=n && L[q[l]] <= R[j])
		{
			while(l<=r && L[q[r]] <= L[j]) --r;
			q[++r] = j ++;
		}
		ans = max(ans,j-i);
	}
	cout << ans << endl;
}
