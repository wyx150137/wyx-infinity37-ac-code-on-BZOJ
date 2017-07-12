
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <set>
#define N 100000+5
using namespace std;
inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch <'0'||ch >'9'){if(ch=='-')f=-1;ch = getchar();}
	while(ch >='0'&&ch<='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}
long long ans = 0;
struct data
{
	int x,y;
	bool operator <(const data&z)const
	{
		return y > z.y;
	}
}a[N],b[N];
multiset<int>s;
int main()
{
	int n=read(),m=read();
	for(int i=1;i<=n;++i)a[i].x=read(),a[i].y=read();
	for(int i=1;i<=m;++i)b[i].x=read(),b[i].y=read();
	sort(a+1,a+n+1);sort(b+1,b+m+1);
	int j=1;
	for(int i=1;i<=n;++i)
	{
		while(a[i].y<=b[j].y && j<=m)s.insert(b[j++].x);
		multiset<int>::iterator it = s.lower_bound(a[i].x);
		if(it == s.end()){puts("-1");return 0;}
		ans += *it;
		s.erase(it);
	}
	cout<<ans;
}
