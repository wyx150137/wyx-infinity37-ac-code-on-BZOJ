
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e6+5;
int last[N],a[N],tmp[N],stack[N],top,cnt,n,k;
struct Line
{
	int lth,col[N],nxt[N],last[N],Min[N],end[N];
	void init()
	{
		top = 0;
		for(int i = 1;i<= lth;i++)scanf("%d",&tmp[i]);
		for(int i = 1;i< lth;i++)nxt[tmp[i]] = tmp[i+1];
		for(int i = n;i>=1;i--)
		{
			end[i] = 0;
			if(col[i]==tmp[lth])end[i] = i;
			else if(nxt[col[i]]&&last[nxt[col[i]]])
				end[i] = end[last[nxt[col[i]]]];
			if(col[i]==tmp[1]&&end[i])stack[++top] = i;
			last[col[i]] = i;
		}
		stack[top+1] = 1;
		for(int i = 1;i<=top;i++)
			for(int j = stack[i]-1;j>= stack[i+1];j--)
				Min[j] = end[stack[i]];
	}
}a1,a2;
struct Seg
{int l,r;}seg[N];
bool cmp(Seg a,Seg b)
{
	return a.l<b.l;
}
int main()
{
	scanf("%d%d",&n,&k);
	for(int i = 1;i<= n;i++)
		scanf("%d",&a[i]);
	for(int i = 1;i<= n;i++)
		a1.col[i] = a[i],a2.col[i] = a[n-i+1];
	scanf("%d%d",&a1.lth,&a2.lth);
	a1.init();
	a2.init();
	for(int i = 1;i<= n;i++)
	{
		if(a1.last[a2.col[i]])
		{
			int tmp1 = a1.Min[a1.last[a2.col[i]]],tmp2 = a2.Min[i];
			if(tmp1&&tmp2&&tmp1<=n-tmp2+1)
				seg[++cnt] = (Seg){tmp1,n-tmp2+1};
		}
	}
	sort(seg+1,seg+cnt+1,cmp);
	int L = seg[1].l,R = seg[1].r,top = 0;
	for(int i = 2;i<= cnt;i++)
	{
		if(seg[i].l>R)
		{
			for(int j = L;j<=R;j++)
				if(a[j]==tmp[a2.lth])stack[++top] = j;
			L = seg[i].l,R = seg[i].r;
		}
		else R = max(seg[i].r,R);
	}
	for(int j = L;j<=R;j++)
		if(a[j]==tmp[a2.lth])stack[++top] = j;
	printf("%d\n",top);
	for(int i = 1;i<=top;i++)
		printf("%d ",stack[i]);
	//printf("%d\n",stack[top]);
	return 0;
}
