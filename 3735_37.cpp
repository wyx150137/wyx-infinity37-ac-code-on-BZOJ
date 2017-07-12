
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 1e5+5;
struct data
{
	ll pos;int i;
	data(){}
	data(ll _pos,int _i):pos(_pos),i(_i){}
	bool operator <(const data &s)const
	{
		if(pos==s.pos)return i>s.i;
		return pos>s.pos;
	}
}heap[N];
int cnt,a[N];ll n,L,R,now;int k;
ll Ans[N];
bool check(ll mid)
{
	ll ans = n;
	for(int i = 1;i<= k;i++)
	{
		ans-=mid/a[i];
		if(ans<0)return false;
	}
	return true;
}
int main()
{
	scanf("%lld%d",&n,&k);
	for(int i = 1;i<= k;i++)
	{
		scanf("%d",&a[i]);
		R = max(R,1ll*a[i]);
	}
	L = R+1,R = R*n;
	ll ans = 0;
	while(L<=R)
	{
		ll mid = (L+R)>>1;
		if(check(mid))L=mid+1,ans=mid;
		else R = mid-1;
	}
	R = ans;
	for(int i = 1;i<= k;i++)R = min(R,max((ans/a[i]-1)*a[i],0ll));
	cnt = 0;
	for(int i = 1;i<= k;i++)
	{
		now+=R/a[i];
		heap[++cnt] = data(R/a[i]*a[i],i);
		push_heap(heap+1,heap+cnt+1);
	}
	while(now<n)
	{
		data tmp = heap[1];
		pop_heap(heap+1,heap+cnt+1);
		Ans[tmp.i] = ++now;
		tmp.pos+=a[tmp.i];
		heap[cnt] = tmp;
		push_heap(heap+1,heap+cnt+1);
	}
	for(int i = 1;i< k;i++)
		printf("%lld ",Ans[i]);
	printf("%lld\n",Ans[k]);
	return 0;
}
