
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
using namespace std;
const int N = 300+5;
multiset <int> S;

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch - '0';ch = getchar();}
	return x*f;
}

int a[N*N];
int cnt = 0;
int ans[N][N];
int now[N],n,sum;

map<int,int> mp;

void solve(int x){

	S.clear();mp.clear();
	for(int i=3;i<=sum;++i) S.insert(a[i]);
	memset(now,0,sizeof now);
	multiset <int> :: iterator it;

	it = S.find(x);S.erase(it);
	int tmp = a[1] + a[2] - x;
	if(tmp & 1) return;
	tmp >>= 1;
	now[1] = tmp,now[2] = a[1] - now[1],now[3] = x - now[2];
//	cout << now[1] << " " << x << endl;
	if(now[1] == now[2] || now[2] == now[3] || now[1] == now[3] || now[1] <= 0 || now[2] <= 0 || now[3] <= 0) return;
	mp[now[1]] = mp[now[2]] = mp[now[3]] = 1;
	for(int i=4;i<=n;++i)
	{
		it = S.begin();
		tmp = *it;
		now[i] = tmp - now[1];
		if(mp[now[i]] >= 1)
			return;
		if(now[i] <= 0) return;
		mp[now[i]] = 1;
		for(int j=1;j<i;++j)
		{
			it = S.find(now[i]+now[j]);
			if(it == S.end()) return;
			S.erase(it);
		}
	}
	cnt ++;
//	cout << x << endl;	
	memcpy(ans[cnt],now,sizeof now);
}

int main()
{
//	freopen("squ.in", "r", stdin);
//	freopen("squ.out", "w", stdout);

	n = read();
	sum = (n*(n-1)) >> 1;
	for(int i=1;i<=sum;++i) a[i] = read();
	sort(a+1,a+sum+1);

	for(int i=3;i<=n;++i)
		if(a[i]!=a[i-1] || i == 3)
			solve(a[i]);
	cout << cnt << endl;

	for(int i=1;i<=cnt;++i)
	{
		for(int j=1;j<=n;++j)
			printf("%d ",ans[i][j]);
		puts("");
	}
}

