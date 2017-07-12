
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <map>
#define N 1000000
#define lowbit(x)  ((x)&(-x))
using namespace std;

struct Point
{
	int x,y;
	int a;
	bool operator<(const Point &z)const
	{
		return y ^ z.y ? y < z.y : x < z.x;
	}
}p[N+5];

int T[N+5];

void updata(int x,int num)
{
	while(x<=N)
	{
		T[x] = max(T[x],num);
		x += lowbit(x);
	}
}

int ask(int x)
{
	int ans = 0;
	while(x)
	{
		ans = max(ans,T[x]);
		x -= lowbit(x);
	}
	return ans;
}

int f[N];
inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int tmp[N];
int tt;
map<int,int>mp;

int main()
{
	int n,m,k;
	cin>>n>>m>>k;
	for(int i=1;i<=k;++i)
		p[i].x=read(),p[i].y=read(),p[i].a=read();
	sort(p+1,p+k+1);
	for(int i=1;i<=k;++i)
		tmp[++tt] = p[i].x;
	sort(tmp+1,tmp+tt+1);
	for(int i=1;i<=k;++i)
		if(!mp[tmp[i]])
			mp[tmp[i]] = i;
	for(int i=1;i<=k;++i)
	{
		f[i] = ask(mp[p[i].x])+p[i].a;
		updata(mp[p[i].x],f[i]);
	}
	cout<<ask(N)<<endl;
}
