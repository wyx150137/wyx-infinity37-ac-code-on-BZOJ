
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 100000+5;

inline int read()
{
	int x=0,f=1;char ch =getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1) + (x<<3) + ch - '0';ch = getchar();}
	return x*f;
}

int L[N],R[N],n,m;
int a[N],b[N],c[N],cnt;
int num[N];
int end[N][4];

bool check(int mid)
{
	int cnt = 0,cl = 0 ,cr = 0;
	for(int i=1;i<=n;++i) L[i] = N ,R[i] = 0;
	for(int i=1;i<=m;++i) a[i] = 0;
	for(int i=1;i<=mid;++i)
	{
		int tmp = end[i][0];
		int x = end[i][1], y = end[i][2];
		if(a[tmp] && a[tmp] != y) return false;
		a[tmp] = y;
		L[x] = min(L[x],tmp);
		R[x] = max(R[x],tmp);
	}

	for(int i=1;i<=m;++i)
	{
		if(a[i])
		{
			num[i] = ++cnt;
			a[cnt] = a[i];
			b[cnt] = c[cnt] = 0;
		}
	}

	for(int i=1;i<=n;++i)
		if(R[i])
			b[num[L[i]]] ++,c[num[R[i]]] ++;
	int t = n;
	int s = 0;
//	cout << cnt << endl;
	for(int i=1;i<=cnt;++i)
	{
		s += b[i];
		if(s > a[i]) return false;
		while(b[i] --)
			if(cl > 0) cl --;
			else t --;
		while(s + cl + cr < a[i]) cl ++,t --;
		while(s + cl + cr > a[i]) if(cr > 0) cr --;else cl --;
		s -= c[i];
		cr += c[i];
		if(t < 0) return false;
	}
	return  1;
}

int main()
{
//	freopen("02.in","r",stdin);
	int T = read();
	while(T--)
	{
		n = read(), m = read();
		for(int i=1;i<=m;++i)
			end[i][0] = read(), end[i][1] = read(),end[i][2] = read()+1	;
		int l = 2;
		int r = m;
		int ans = 1;
		while(l<=r)
		{
			int mid = (l+r) >> 1;
			if(check(mid))
				ans = mid, l = mid + 1;
			else r = mid - 1;
		}
		printf("%d\n",ans);
	}
}
  
