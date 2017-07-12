
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 2e5+5;
const int INF = 0x3f3f3f3f;
struct Seg_Tree
{
	int mn[N<<2],lazy[N<<2];
	void build(int p,int l,int r)
	{
		lazy[p] = mn[p] = INF;
		if(l==r)return ;
		int mid = (l+r)>>1;
		build(p<<1,l,mid);
		build(p<<1|1,mid+1,r);
	}
	void push_down(int p,int l,int r)
	{
		if(lazy[p]==INF||l==r)return ;
		mn[p<<1] = min(mn[p<<1],lazy[p]);
		mn[p<<1|1] = min(mn[p<<1|1],lazy[p]);
		lazy[p<<1] = min(lazy[p<<1],lazy[p]);
		lazy[p<<1|1] = min(lazy[p<<1|1],lazy[p]);
		lazy[p] = INF;
	}	
	void Update(int p,int l,int r,int a,int b,int c)
	{
		push_down(p,l,r);
		if(l>=a&&r<=b)
		{
			lazy[p] = min(lazy[p],c);
			mn[p] = min(mn[p],c);
			return ;
		}
		int mid = (l+r)>>1;
		if(a<=mid)Update(p<<1,l,mid,a,b,c);
		if(b >mid)Update(p<<1|1,mid+1,r,a,b,c);
		mn[p] =min(mn[p<<1],mn[p<<1|1]);
	}
	int Getans(int p,int l,int r,int x)
	{
		push_down(p,l,r);
		if(l==r)return mn[p];
		int mid = (l+r)>>1;
		if(x<=mid)return Getans(p<<1,l,mid,x);
		else return Getans(p<<1|1,mid+1,r,x);
	}
}t1,t2;
struct SAM
{
	int trs[N<<1][26],fa[N<<1],len[N<<1];
	bool end[N<<1];
	int cnt,last;
	void init()
	{
		cnt = last = 1;
	}
	void insert(int x)
	{
		int p = last,np = ++cnt,q,nq;
		last = np,len[np] = len[p]+1;
		end[np] =true;
		for(;p&&!trs[p][x];p = fa[p])trs[p][x] = np;
		if(!p)fa[np] = 1;
		else
		{
			q = trs[p][x];
			if(len[q]==len[p]+1)fa[np] =q;
			else
			{
				fa[nq =++cnt] =fa[q];
				len[nq] = len[p]+1;
				memcpy(trs[nq],trs[q],sizeof(trs[q]));
				fa[np] = fa[q] = nq;
				for(;p&&trs[p][x]==q;p =fa[p])trs[p][x] = nq;
			}
		}
	}
	void getans(int n)
	{
		for(int i = 1;i<= cnt;i++)
			end[fa[i]] =false;
		for(int i = 1;i<= cnt;i++)
			if(end[i])
			{
				int l =len[i]-len[fa[i]],r = len[i];
				t1.Update(1,1,n,l,r,r-l+1);
				if(l>1)t2.Update(1,1,n,1,l-1,r);
			}
		for(int i = 1;i<= n;i++)
			printf("%d\n",min(t1.Getans(1,1,n,i),t2.Getans(1,1,n,i)-i+1));
	}
}sam;
char s[N];
int main()
{
	sam.init();
	scanf("%s",s+1);
	int n = strlen(s+1);
	t1.build(1,1,n);
	t2.build(1,1,n);
	for(int i = 1;i<= n;i++)
		sam.insert(s[i]-'a');
	sam.getans(n);	
	return 0;
}
