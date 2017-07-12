
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 1100000+5;
using namespace std;

int cnt = 0,n,m,A,b,p;
int ans = 0;

struct interval
{
	int l,r;
	interval () {}
	interval (int _l,int _r):l(_l),r(_r){}
	bool operator<(const interval &z)const
	{
		return l < z.l;
	}
}a[N<<2];

void add(int l,int r){
	if(l<=r)a[++cnt] = interval(l,r);
	else a[++cnt] = interval(l,n-1),a[++cnt] = interval(0,r);
}

char s[N];

int main()
{
	cin >> n >> A >> b >> p >> m ;
	scanf("%s",s);
	for(int i=0,now = 0;i<m;++i,(now+=A)%=n)
		if(s[i] == '0')
			add((p-now+n)%n,(n-1-now+n)%n);
		else
			add((n-now+n)%n,(p+n-now-1)%n);
	for(int i=1,c=(b-A+n)%n;i<m;++i,c=(c-A+n)%n)
		add(c,c);
	sort(a+1,a+cnt+1);
	int tmp = -1;
	for(int i=1;i<=cnt;++i)
	{
		if(a[i].l > tmp) ans += a[i].l-tmp-1,tmp = a[i].r;
		else tmp = max(tmp,a[i].r);
	}
	cout << ans + n - 1 - tmp;
}
