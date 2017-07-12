
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 5e5+5;
bool cmp1(const int &a,const int &b){return a<b;}
bool cmp2(const int &a,const int &b){return b<a;}
int heap[N],ans[N],cnth,cnta;
int lamp[N],lst[N];
int main()
{
	int n,k;
	scanf("%d%d",&n,&k);
	for(int i = 1;i<= n;i++)
		scanf("%d",&lamp[i]);
	for(int i = 1;i<= n;i++)
		scanf("%d",&lst[i]);
	sort(lamp+1,lamp+n+1,cmp2);
	sort(lst+1,lst+n+1,cmp2);
	int j = 1;
	long long tans = 0;
	for(int i = 1;i<= n;i++)
	{
		while(j<=n&&lamp[j]>=lst[i])
		{
			heap[++cnth] = lamp[j];
			push_heap(heap+1,heap+cnth+1,cmp2);
			j++;
		}
		if(cnth<=0&&k>=1)k--,tans+=lst[i];
		else if(cnth<=0){printf("NIE\n");return 0;}
		else
		{
			tans+=heap[1];
			ans[++cnta] = heap[1]-lst[i];
			push_heap(ans+1,ans+cnta+1,cmp1);
			pop_heap(heap+1,heap+cnth+1,cmp2);
			cnth--;
		}
	}
	while(k&&cnta)
	{
		tans-=ans[1];
		pop_heap(ans+1,ans+cnta+1,cmp1);
		cnta--,k--;
	}
	printf("%lld\n",tans);
	return 0;
}
