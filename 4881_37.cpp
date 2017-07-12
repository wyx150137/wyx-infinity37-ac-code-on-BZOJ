
#include <stdio.h>
#include <set>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 1e5+5;
const int mod = 998244353;
int c[N],a[N],f[N];
int getans(int x)
{
	int ans = 0;
	for(int i = x;i;i-=i&(-i))ans=max(ans,c[i]);
	return ans;
}
void update(int x,int y)
{
	for(int i = x;i<N;i+=i&(-i))c[i] = max(c[i],y);
}
int quick_pow(int x,int y)
{
	int res = 1;
	while(y)
	{
		if(y&1)res = (ll)res*x%mod;
		x = (ll)x*x%mod;
		y>>=1;
	}
	return res;
}
set<int>S;
set<int>::iterator it;
set<int>::iterator tmp;
int main()
{
	int n;
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)scanf("%d",&a[i]);
	int mx = 0;
	for(int i = 1;i<= n;i++)
	{
		f[i] = getans(n-a[i])+1;
		update(n-a[i]+1,f[i]);
		mx = max(mx,f[i]);
	}
	if(mx>2)
	{
		puts("0");
		return 0;
	}
	for(int i = 1;i<= n;i++)
	{
		int mx = a[i];
		it = S.upper_bound(a[i]);
		while(it!=S.end())
		{
			mx = max(mx,*it);
			tmp = it;
			it++;S.erase(tmp);
		}
		S.insert(mx);
	}
	printf("%d\n",quick_pow(2,S.size()));
	return 0;
}
