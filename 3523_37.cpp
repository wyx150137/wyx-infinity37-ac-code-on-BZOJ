
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1000005;
struct H
{
	int col,num,se;
}heap[N];
bool cmp(H a,H b)
{
	if(a.num!=b.num)
		return a.num<b.num;
	return a.se<b.se;
}
int a[N],ans[N],cnt;
int main()
{
	int n,s,t;
	scanf("%d%d%d",&n,&s,&t);
	int sum = 0;
	for(int i = 1;i<= n;i++)
	{
		scanf("%d",&a[i]);
		sum = sum+a[i];
	}
	if(sum==1&&s==t)
		{printf("%d\n",1);return 0;}
	else if(sum==1){printf("0\n");return 0;}
	for(int i = 1;i<= n;i++)
	{
		if(a[i]-(i==s)-(i==t)>0)
		{
		heap[++cnt].col = i;
		heap[cnt].num = a[i]-(i==s)-(i==t);
		heap[cnt].se = i==t;
		push_heap(heap+1,heap+cnt+1,cmp);
		}else if(a[i]-(i==s)-(i==t)<0)
		{printf("0\n");return 0;}
	}
	int i;
	ans[1] = s,ans[sum] = t; 
	for(i = 2;i< sum;i++)
	{
		H x = heap[1];
		pop_heap(heap+1,heap+1+cnt,cmp);
		cnt--;
		if(x.col==ans[i-1]&&cnt!=0)
		{
			H tmp = x;
			x = heap[1];
			pop_heap(heap+1,heap+1+cnt,cmp);
			cnt--;
			ans[i] = x.col;
			x.num--;
			if(x.num)
			{
				heap[++cnt] = x;
				push_heap(heap+1,heap+cnt+1,cmp);
			}
			heap[++cnt] = tmp;
			push_heap(heap+1,heap+cnt+1,cmp);
			continue;
		}
		else if(x.col!=ans[i-1])
		{
			ans[i] = x.col;
			x.num--;
			if(x.num)
			{
				heap[++cnt] = x;
				push_heap(heap+1,heap+cnt+1,cmp);
			}
		}
		if(!cnt&&ans[i]==0)
			{printf("0\n");return 0;}
	}
	if(ans[sum]!=ans[sum-1]||sum==1)
	{
		for(i = 1;i< sum;i++)
			printf("%d ",ans[i]);
		printf("%d\n",ans[sum]);
	}
	else printf("0\n");
	return 0;
}
