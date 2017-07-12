
#include <set>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 500000+5;
using namespace std;

struct data
{
	int x,y;
	bool operator < (const data &z)const
	{
		return x < z.x;
	}
}a[N];

char str[N];
int p[N];

void solve()
{
	int len = strlen(str+1);
	str[0] = '!' ;
	char *s = str;
	int mx = 0, id = 0;
	for(int i=1;i<=len;++i)
	{
		if(mx < i) p[i] = 0;
		else p[i] = min(mx-i,p[2*id-i]);
		while(s[i+p[i]+1] == s[i-p[i]]) p[i] ++;
		if(mx < i + p[i]) mx = i + p[i], id = i;
	}	
}

set<int> S;

int main()
{
	int n,ans = 0,tot = 0; cin >> n;
	scanf("%s",str+1); solve();
	for(int i=1;i<=n;++i) a[i].x = i - p[i], a[i].y = i;
	sort(a+1,a+n+1);
	for(int i=1;i<=n;++i)
	{
		while(tot < n && a[tot+1].x <= i) S.insert(a[++tot].y);
		ans = max(ans,(*--S.lower_bound(i+p[i]/2+1)-i)*4);
	}
	cout << ans << endl;
}
