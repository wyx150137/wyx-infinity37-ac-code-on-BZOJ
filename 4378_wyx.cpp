
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#define lowbit(x) ((x)&(-x))
using namespace std;
const int N = 1000000;
typedef long long LL;

int T1[N+5];
LL T2[N+5];

struct ask
{
	int chose;
	int x,y;
}q[N+5];

void updata(int x,int num)
{
	while(x <= N )
	{
		T1[x] += (num >= 0) ? 1 : -1;
		T2[x] += (LL)num;
		x += lowbit(x);
	}
}

int ask1(int x)
{
	int ans = 0;
	while(x)
	{
		ans += T1[x];
		x -= lowbit(x);
	}
	return ans;
}

LL ask2(int x)
{
	LL ans = 0;
	while(x)
	{
		ans += T2[x];
		x -= lowbit(x);
	}
	return ans;
}

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int a[N+5];
int V[N<<1];
int tt;

int find(int x)
{
	int l = 1;
	int r = tt;
	while(l<=r)
	{
		int mid = (l+r)>>1;
		if(V[mid] == x) return mid;
		if(V[mid] < x) l = mid + 1;
		else r = mid - 1;
	}
	return 0;
}

int main()
{
	int n = read(), m = read();
	char str[10]; 
	for(int i=1;i<=m;++i)
	{
		scanf("%s",str);
		q[i].chose = (str[0] == 'U');
		q[i].x = read(),q[i].y = read();
		V[++tt] = q[i].y;
	}
	V[++tt] = 0;
	for(int i=1;i<=n;++i)
		updata(1,0);
	sort(V+1,V+tt+1);
	for(int i=1;i<=m;++i)
	{
		if(q[i].chose == 1)
		{
			int tt = find(a[q[i].x]);
			updata(tt,-a[q[i].x]);
			a[q[i].x] = q[i].y;
			tt = find(a[q[i].x]) ;
			updata(tt,a[q[i].x]);	
		}
		else
		{
			int tt = find(q[i].y);
			int tt1 = ask1(N) - ask1(tt-1);
			if(tt1 >= q[i].x){puts("TAK");continue;}
			LL tt2 = ask2(tt-1);
			if(tt2 >= ((LL)q[i].x - tt1)*q[i].y)
				puts("TAK");
			else puts("NIE");
		}
	}
}
