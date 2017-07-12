
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e6+5;
const int INF = 0x3f3f3f3f;
int v[N],stack[N],top,nxt[N],fv[N],b[N],pre[N];
char s[N];
int main()
{
	int n,ans = 0;
	scanf("%d",&n);
	scanf("%s",s+1);
	for(int i = 1;i<= n;i++)
	{
		if(s[i]=='p')pre[i] = pre[i-1]+1;
		else pre[i] = pre[i-1]-1;
	}
	for(int i = 1;i<= n;i++)
	{
		while(top>0&&pre[i]-pre[stack[top]-1]<0)
		{
			nxt[stack[top]] = i-1;
			top--;
		}
		if(top)fv[i] = stack[1];
		else if(pre[i]-pre[i-1]==1)fv[i] = i;
		else fv[i] = INF;
		if(pre[i]-pre[i-1]==1)stack[++top] = i;
	}
	while(top>0)
	{
		nxt[stack[top]] = n;
		top--;
	}
	int L,R,mid,head = 0;
	for(int i = n;i>= 1;i--)
	{
		while(top>0&&pre[stack[top]]-pre[i-1]<0)
		{
			L = 2,R = head+1;
			while(L<R)
			{
				mid = (L+R)>>1;
				if(nxt[b[mid]]>=stack[top])L = mid+1;
				else R = mid;
			}
			ans = max(ans,stack[top]-max(fv[stack[top]]-1,b[L-1]-1));
			top--;
		}
		if(pre[i]-pre[i-1]==1)
		{
			stack[++top] = i;
			while(head&&nxt[b[head]]<=nxt[i])head--;
			b[++head] = i;
		}
	}
	while(top>0)
	{
		L = 2,R = head+1;
		while(L<R)
		{
			mid = (L+R)>>1;
			if(nxt[b[mid]]>=stack[top])L = mid+1;
			else R = mid;
		}
		ans = max(ans,stack[top]-max(fv[stack[top]]-1,b[L-1]-1));
		top--;
	}
	printf("%d\n",ans);
	return 0;
}
