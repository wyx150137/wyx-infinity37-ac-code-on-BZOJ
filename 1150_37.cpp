
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 200005;
const int INF = 0x3f3f3f3f;
struct Heap
{int no,val;}heap[N];
bool cmp(const Heap &a,const Heap &b)
{
	return a.val>b.val;
}
int len[N],pre[N],L[N],R[N];
int main()
{
	int n,k,y;
	scanf("%d%d",&n,&k);
	for(int i = 1;i<= n;i++)
	{
		scanf("%d",&y);
		len[i] = y-pre[i-1];
		pre[i] = y;
		L[i] = i-1,R[i]=i+1;
	}
	int cnt = 0;
	for(int i = 2;i<= n;i++)
	{
		heap[++cnt] = (Heap){i,len[i]};
		push_heap(heap+1,heap+cnt+1,cmp);
	}
	L[2] = 0,R[n]=0;
	int ans = 0;
	for(int i =1;i<= k;i++)
	{
		while(heap[1].val!=len[heap[1].no])
			pop_heap(heap+1,heap+cnt+1,cmp),cnt--;
		int x = heap[1].no;
		int l = L[x],r = R[x];
		pop_heap(heap+1,heap+cnt+1,cmp),cnt--;
		ans+=len[x];
		L[R[x] = R[r]]=x;
		R[L[x] = L[l]]=x;
		len[x] = (l&&r)?min(INF,len[l]+len[r]-len[x]):INF;
		len[l] = len[r] = INF;
		heap[++cnt] = (Heap){x,len[x]};
		push_heap(heap+1,heap+cnt+1,cmp);
	}
	printf("%d\n",ans);
	return 0;
}
