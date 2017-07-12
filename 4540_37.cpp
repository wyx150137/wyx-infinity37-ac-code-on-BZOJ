
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 1e5+5;
int a[N],lg2[N];
int st[N][18],n,q;
int Min(int x,int y)
{
	return a[x]<a[y]?x:y;
}
void build_st()
{
	for(int i = 2;i<= n;i++)
		lg2[i] = lg2[i>>1]+1;
	for(int i = 1;i<= n;i++)
		st[i][0] = i;
	for(int j = 1;j<= 17;j++)
		for(int i = 1;i<=n;i++)
		{
			st[i][j] = st[i][j-1];
			if(i+(1<<(j-1))<=n)
				st[i][j] = Min(st[i][j],st[i+(1<<(j-1))][j-1]);
		}
}
int Ask(int l,int r)
{
	if(l>r)swap(l,r);
	int lth = lg2[r-l+1];
	return Min(st[l][lth],st[r-(1<<lth)+1][lth]);
}

ll left[N],right[N];
int stack[N],top;
void init()
{
	stack[top=0]=0;
	for(int i = 1;i<= n;i++)
	{
		while(top&&a[stack[top]]>=a[i])top--;
		right[i] = right[stack[top]]+(ll)a[i]*(i-stack[top]);
		stack[++top] = i;
	}
	stack[top=0]=n+1;
	for(int i = n;i;i--)
	{
		while(top&&a[stack[top]]>=a[i])top--;
		left[i] = left[stack[top]]+(ll)a[i]*(stack[top]-i);
		stack[++top] = i;
	}
}
ll getleft(int l,int r)
{
	int t = Ask(l,r);
	return (ll)a[t]*(r-t+1)+left[l]-left[t];
}
ll getright(int l,int r)
{
	int t = Ask(l,r);
	return (ll)a[t]*(t-l+1)+right[r]-right[t];
}

struct Ask
{
	int l,r,lpos,id;
	bool operator <(const Ask &s)const
	{
		if(lpos==s.lpos)return r<s.r;
		return lpos<s.lpos;
	}
}ask[N];
ll ans;
ll Ans[N];
void solve()
{
	int l = 1,r = 0;
	for(int i = 1;i<= q;i++)
	{
		while(r<ask[i].r)ans+=getright(l,++r);
		while(r>ask[i].r)ans-=getright(l,r--);
		while(l<ask[i].l)ans-=getleft(l++,r);
		while(l>ask[i].l)ans+=getleft(--l,r);
		Ans[ask[i].id] = ans;
	}
}

int main()
{
	scanf("%d%d",&n,&q);
	for(int i = 1;i<= n;i++)scanf("%d",&a[i]);
	build_st();
	init();
	int block = sqrt(q);
	for(int i = 1;i<= q;i++)
	{
		scanf("%d%d",&ask[i].l,&ask[i].r);
		ask[i].lpos = (ask[i].l-1)/block+1;
		ask[i].id = i;
	}
	sort(ask+1,ask+q+1);
	solve();
	for(int i = 1;i<= q;i++)
		printf("%lld\n",Ans[i]);
	return 0;
}
