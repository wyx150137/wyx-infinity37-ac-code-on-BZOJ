
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <algorithm>
#include <map>
#include <queue>
#define N 200000+5
#define M 300000+5
using namespace std;
int a[N];
inline int read()
{
	int x = 0, f = 1; char ch = getchar();
	while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
	return x * f;
}
map <int ,int >mp;
priority_queue<int>Q;
struct seg
{
	int l,r,mn;
}tr[M];
void build(int k,int l,int r)
{
	tr[k].l=l,tr[k].r=r;
	if(l==r)
	{
		tr[k].mn=1;
		return ;
	}
	int mid=(l+r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	tr[k].mn=tr[k<<1].mn+tr[k<<1|1].mn;
}
void change(int k,int pos)
{
	if(tr[k].l==pos && tr[k].r==pos)
	{	
			tr[k].mn--;
		return;
	}
	int mid=(tr[k].l+tr[k].r)>>1;
	if(pos<=mid)
		change(k<<1,pos);
	else 
		change(k<<1|1,pos);
	tr[k].mn=tr[k<<1].mn+tr[k<<1|1].mn;
}
int ask(int k,int l,int r)
{
	if(l==tr[k].l && r==tr[k].r)
		return tr[k].mn;
	int mid=(tr[k].l+tr[k].r)>>1;
	if(r<=mid)
		return ask(k<<1,l,r);
	else if(l>mid)
		return ask(k<<1|1,l,r);
	else
		return ask(k<<1,l,mid)+ask(k<<1|1,mid+1,r);
}
int main()
{
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;++i)
		a[n-i+1]=read(),Q.push(a[n-i+1]);
	for(int i=n+1;i<=m+n;++i)
		a[i]=read(),Q.push(a[i]);
	for(int i=1;i<=m+n;++i)
		mp[a[i]]=i;
	int mid=n;
	long long times=0;
	build(1,1,m+n);
	while(!Q.empty())
	{
		int tmp=Q.top();
		Q.pop();
		int pos=mp[tmp];
		if(pos==mid || pos==mid+1)
		{
			change(1,pos);
			mid=pos;
		}	
		else
		{
			if(pos>mid)
			{	
				times+=ask(1,mid+1,pos-1);
				mid=pos;
			}
			else
			{
				times+=ask(1,pos+1,mid);
				mid=pos;
			}
			change(1,pos);
			//printf("times=%d tmp=%d pos=%d mid=%d\n",times,tmp,pos,mid );
		}
		//printf("%d succeed\n",tmp );
	}
	cout<<times;
}
