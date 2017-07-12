
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#define max(a,b) ((a)>(b)?(a):(b))
const int N = 50000+5;
using namespace std;

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int L[N],R[N],a[N];

int main()
{
	int n = read(),mx = 0,l,r;
	for(int i=1;i<=n;++i) a[i] = read(),mx = max(mx,a[i]);
	for(int i=1;i<=n;++i)
	{
		l = r = i;
		while(a[l] <= a[i] && l) l--;
		if(l != 0)
		{
			l --;
			while(a[l] <= a[i] && l) l--;
		}
		while(a[r] <= a[i] && r<=n) ++r;
		if(r != n+1)
		{
			r ++;
			while(a[r] <= a[i] && r <= n) ++r;
		}
		L[i] = max(l,0); R[i] = min(r,n+1);
	}
	int ans = 0,tmp;
	for(int i=1;i<=n;++i)
		if(a[i] != mx)
		{
			tmp = 0;
			for(int j=L[i]+1;j<=R[i]-1;++j) tmp = max(tmp,a[j]^a[i]);
			ans = max(ans,tmp);
		}
	cout << ans << endl;
}
