
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 1e5+5;
struct data
{
	ll num;int pos;
	bool operator <(const data &a)const
	{
		if(num==a.num)return pos<a.pos;
		return num<a.num;
	}
};
ll gcd(ll x,ll y)
{
	if(y==0)return x;
	else return gcd(y,x%y);
}
data tmp,f[2][N];
ll a[N];
int main()
{
	int n;
	ll ans = 0;
	scanf("%d",&n);
	int now = 1,pre = 0;
	int cntn = 0,cntp = 0;
	for(int i = 1;i<= n;i++)
	{
		scanf("%lld",&a[i]);
		for(int j = 1;j <= cntp;j++)
			f[pre][j].num = gcd(f[pre][j].num,a[i]);
		tmp.num = a[i];
		tmp.pos = i;
		cntp++;
		f[pre][cntp] = tmp;
		sort(f[pre]+1,f[pre]+cntp+1);
		cntn = 0;
		for(int j = 1;j<= cntp;j++)
			if(f[pre][j].num!=f[pre][j-1].num)
				f[now][++cntn] = f[pre][j];
		for(int j = 1;j<= cntn;j++)
			ans = max(ans,f[now][j].num*(i-f[now][j].pos+1));
		swap(now,pre);
		cntp = cntn;
	}
	printf("%lld\n",ans);
	return 0;
}
