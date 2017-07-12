
#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
struct Heap
{
	ll w;int l;
	Heap(){}
	Heap(ll _w,int _l):w(_w),l(_l)
	{}
	bool operator <(const Heap &s)const
	{
		if(w!=s.w)return s.w<w;
		else return s.l<l;
	}
};
priority_queue<Heap>heap;
int n,k,nn;
ll ans = 0;
int main()
{
	scanf("%d%d",&n,&k);
	nn = n;ll x;
	for(int i = 1;i<= n;i++)
	{
		scanf("%lld",&x);
		heap.push(Heap(x,1));
	}
	if((n-1)%(k-1))nn+=(k-1)-(n-1)%(k-1);
	for(int i = n+1;i<= nn;i++)
		heap.push(Heap(0,1));
	while(nn>1)
	{
		ll s1 = 0;int s2 = 0;
		for(int i = 1;i<= k;i++)
		{
			Heap x = heap.top();
			heap.pop();
			s1+=x.w;s2=max(s2,x.l);
		}
		ans+=s1,nn-=(k-1);
		heap.push(Heap(s1,s2+1));
	}
	printf("%lld\n%d\n",ans,heap.top().l-1);
	return 0;
}
