
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define lowbit(x) ((x)&(-x))
const int inf = 0x7fffffff;
const int N = 100005;
using namespace std;

char str[N],s[N<<1];
int p[N<<1],tr[N];

struct data
{
	int l,r;
	data () {}
	data (int _,int __):l(_),r(__){}
	bool operator < (const data &z)const
	{
		return r < z.r;
	}
}a[N];

int cnt = 0;
inline void add(int x,int y)
{
	x = (x>>1) + 1;
	y = (y>>1) - 1;
	if(x > y) return;
	a[++cnt] = data(x,y);
}

void manacher()
{
	int len = strlen(str);
	s[0] = '!', s[1] = '^';
	for(int i=1;i<=len;++i) s[i<<1] = str[i-1], s[i<<1|1] = '^';
	len ++; len <<= 1;
	int mx = 0 , id = 0;
	for(int i=1;i<len;++i)
	{
		if(mx < i) p[i] = 1;
		else p[i] = min(mx-i,p[2*id-i]);
		while(s[i+p[i]] == s[i-p[i]]) p[i] ++;
		add(i-p[i],i+p[i]);
		if(i+p[i] > mx) mx = i + p[i], id = i;
	}
}

inline void updata(int x,int tt)
{
	while(x)
	{
		tr[x] = min(tr[x],tt);
		x -= lowbit(x);
	}
}

inline int ask(int x)
{
	if(!x) return 0;
	int ans = inf;
	while(x < N)
	{
		ans = min(ans,tr[x]);
		x += lowbit(x);
	}
	return ans;
}

int main()
{
	while(~scanf("%s",str))
	{
		cnt = 0;
		int n = strlen(str);
		memset(tr,0x7f,sizeof tr);
		manacher();
		sort(a+1,a+cnt+1);
		int ans = inf;
		for(int i=1;i<=cnt;++i)
		{
			int x = ask(a[i].l-1) + 1;
			updata(a[i].r,x);
			if(a[i].r == n) ans = min(ans,x);
		}
		cout << ans - 1 << endl;
	}
}
