
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#define lowbit(x) ((x)&(-x))
using namespace std;
#define N 1000000
int n;

int T[N+5];
int tmp[N+5];

struct Point
{	
	int x,y;
}p[N+5];

bool cmp1(const Point &a,const Point &b)
{
	return a.x ^ b.x ? a.x < b.x : a.y < b.y;
}

bool cmp2(const Point &a,const Point &b)
{
	return a.y ^ b.y ? a.y < b.y : a.x < b.x;
}

int cnt ;
struct Line
{
	int k,x,y,r;
	bool operator<(const Line &z)const
	{
		return y ^ z.y ? y < z.y : k < z.k;
	}
}s[N+5];

void updata(int x,int num)
{
	while(x<=N)
	{
		T[x] += num;
		x += lowbit(x);
	}
}

int ask(int x)
{
	int ans = 0;
	while(x)
	{
		ans += T[x];
		x -= lowbit(x);
	}
	return ans;
}

int find(int x)
{
	int l = 1,r = n;
	while(l<=r)
	{
		int mid = (l+r)>>1;
		if(tmp[mid] == x)return mid;
		else if(tmp[mid] < x) l = mid + 1;
		else r = mid - 1;
	}
}

void insert(int k,int l,int r,int t)
{
	if(!k){s[++cnt].x = find(l);s[cnt].r= find(r);s[cnt].y = t;}
	else
	{
		s[++cnt].x=find(t);s[cnt].y=l;s[cnt].k=1;
		s[++cnt].x=find(t);s[cnt].y=r;s[cnt].k=-1; 
	}
}

void init()
{
	sort(p+1,p+n+1,cmp1);
	for(int i=2;i<=n;++i)
		if(p[i].x==p[i-1].x)
			insert(1,p[i-1].y,p[i].y,p[i].x);
	sort(p+1,p+n+1,cmp2);
	for(int i=2;i<=n;++i)
		if(p[i].y==p[i-1].y)
			insert(0,p[i-1].x,p[i].x,p[i].y);
}

int ans ;

void work()
{
	for(int i=1;i<=cnt;++i)
		if(!s[i].k)
			ans += ask(s[i].r-1)-ask(s[i].x);
		else
			updata(s[i].x,s[i].k);
}

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int main()
{
	n = read();
	for(int i=1;i<=n;++i)
		p[i].x=read(),p[i].y=read(),tmp[i] = p[i].x;
	sort(tmp+1,tmp+n+1);
	init();
	sort(s+1,s+cnt+1);
	work();
	cout<<ans+n;
}
