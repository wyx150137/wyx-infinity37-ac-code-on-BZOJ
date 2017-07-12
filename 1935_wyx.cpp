
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#define N 500005
#define lowbit(x) ((x)&(-x))
using namespace std;

int n,m,tot;
int tail;

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x * f;
}

struct data
{
	int x,y;
	int id,f;
	bool operator < (const data &z)const
	{
		return x ^ z.x ? x < z.x : f < z.f;
	}
}q[2500005];

int X[N],Y[N],a[N],b[N],c[N],d[N];
int T[1500005],dis[1500005],ans[N][5];

void updata(int x,int num)
{
	for(int i=x;i<=tot;i+=lowbit(i))
		T[i] += num;
}

int ask(int x)
{
	int ans = 0;
	while(x)
	{
		ans += T[x];
		x-= lowbit(x);
	}
	return ans;
}

int find(int x)
{
	int l=1,r=tot;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(dis[mid]==x)return mid;
		else if(dis[mid]<x)l=mid+1;
		else r=mid-1;
	}
}
void solve()
{
	sort(q+1,q+tail+1);
	for(int i=1;i<=tail;++i)
	{
		if(!q[i].f)updata(q[i].y,1);
		else
		{
			int tt = ask(q[i].y);
			ans[q[i].id][q[i].f] = tt;
		}
	}
}

int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;++i)
	{
		X[i] = read(),Y[i] = read();
		dis[++tot] = Y[i];
	}
	for(int i=1;i<=m;++i)
	{
		a[i]=read(),b[i]=read(),c[i]=read(),d[i]=read();
		dis[++tot] = b[i] ,dis[++tot] = d[i];
	}
	sort(dis+1,dis+tot+1);
	for(int i=1;i<=n;++i)
	{
		Y[i] =find(Y[i]);
		q[++tail].x=X[i],q[tail].y=Y[i];
	}
	for(int i=1;i<=m;i++)
	{
	    b[i]=find(b[i]);d[i]=find(d[i]);
		q[++tail].x=c[i];q[tail].y=d[i];q[tail].id=i;q[tail].f=1;
		q[++tail].x=a[i]-1;q[tail].y=d[i];q[tail].id=i;q[tail].f=2;
		q[++tail].x=c[i];q[tail].y=b[i]-1;q[tail].id=i;q[tail].f=3;
		q[++tail].x=a[i]-1;q[tail].y=b[i]-1;q[tail].id=i;q[tail].f=4;
	}
	solve();
	for(int i=1;i<=m;++i)
	{
		int t = ans[i][1] + ans[i][4] - ans[i][3] - ans[i][2];
		printf("%d\n",t);
	}
	return 0;
}
