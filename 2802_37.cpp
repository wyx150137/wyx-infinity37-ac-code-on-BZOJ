
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 250005;
typedef long long LL;
struct H
{int no,val;}heap[N];
LL a[N];
int ans[N],cnt;
bool cmp(H a,H b)
{
	return a.val<b.val;
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)scanf("%lld",&a[i]);
	for(int i = 1;i<= n;i++)
	{
		int b;
		scanf("%d",&b);
		a[i]+=a[i-1];
		if(b<=a[i])
		{
			a[i]-=b;
			heap[++cnt].val = b;
			heap[cnt].no = ++ans[0];
			ans[ans[0]] = i;
			push_heap(heap+1,heap+cnt+1,cmp);
		}else if(cnt)
		{
			int tmp = heap[1].val,pos = heap[1].no;
			if(a[i]+tmp-b>=0&&tmp>b)
			{
				pop_heap(heap+1,heap+cnt+1,cmp);
				cnt--;
				a[i] = a[i]+tmp-b;
				ans[pos] = i;
				heap[++cnt].val = b;
				heap[cnt].no = pos;
				push_heap(heap+1,heap+cnt+1,cmp);
			}
		}
	}
	printf("%d\n",ans[0]);
	for(int i = 1;i< ans[0];i++)
		printf("%d ",ans[i]);
	if(ans[0])printf("%d\n",ans[ans[0]]);
	return 0;
}
