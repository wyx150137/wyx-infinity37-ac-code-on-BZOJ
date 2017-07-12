
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 100000+5;
const int M = N << 2;
using namespace std;

struct Seg
{
	int Max[2],Llen[2],Rlen[2];
	int cover,sum,rev;
	bool yes[2];
}tr[M];

inline void updata(int k)
{
	tr[k].sum = tr[k<<1].sum + tr[k<<1|1].sum;
	tr[k].Llen[0] = tr[k<<1].Llen[0];
	tr[k].Llen[1] = tr[k<<1].Llen[1];
	tr[k].Rlen[0] = tr[k<<1|1].Rlen[0];
	tr[k].Rlen[1] = tr[k<<1|1].Rlen[1];
	if(tr[k<<1].yes[0]) tr[k].Llen[0] += tr[k<<1|1].Llen[0];
	if(tr[k<<1].yes[1]) tr[k].Llen[1] += tr[k<<1|1].Llen[1];
	if(tr[k<<1|1].yes[0]) tr[k].Rlen[0] += tr[k<<1].Rlen[0];
	if(tr[k<<1|1].yes[1]) tr[k].Rlen[1] += tr[k<<1].Rlen[1];
	tr[k].Max[0] = max(max(tr[k<<1].Max[0],tr[k<<1|1].Max[0]),tr[k<<1].Rlen[0]+tr[k<<1|1].Llen[0]);
	tr[k].Max[1] = max(max(tr[k<<1].Max[1],tr[k<<1|1].Max[1]),tr[k<<1].Rlen[1]+tr[k<<1|1].Llen[1]);
	tr[k].yes[0] = (tr[k<<1].yes[0]&tr[k<<1|1].yes[0]); 
	tr[k].yes[1] = (tr[k<<1].yes[1]&tr[k<<1|1].yes[1]);
}

int a[N];

inline void build(int k,int l,int r)
{
	tr[k].cover = -1; tr[k].rev = 0;
	if(l==r)
	{
		if(a[l])
		{
			tr[k].sum = 1;
			tr[k].Llen[1] = tr[k].Rlen[1] = 1;
			tr[k].Llen[0] = tr[k].Rlen[0] = 0;
			tr[k].Max[1] = 1; tr[k].Max[0] = 0;
			tr[k].yes[1] = 1;
		}
		else
		{
			tr[k].sum = 0;
			tr[k].Llen[1] = tr[k].Rlen[1] = 0;
			tr[k].Llen[0] = tr[k].Rlen[0] = 1;
			tr[k].Max[0] = 1, tr[k].Max[1] = 0;
			tr[k].yes[0] = 1;
		}
		return ;
	}
	int mid = (l+r) >> 1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	updata(k);
}

void down(int k,int l,int r)
{
	if(l==r) return;
	int mid = (l+r) >> 1;
	if(tr[k].cover != -1)
	{
		tr[k<<1].cover = tr[k<<1|1].cover = tr[k].cover;
		if(tr[k].cover == 1)
		{
			tr[k<<1].Max[1] = tr[k<<1].Llen[1] = tr[k<<1].Rlen[1] = tr[k<<1].sum = mid - l + 1;
			tr[k<<1|1].Max[1] = tr[k<<1|1].Llen[1] = tr[k<<1|1].Rlen[1] = tr[k<<1|1].sum = r - mid;
			tr[k<<1].yes[1] = tr[k<<1|1].yes[1] = 1;
			tr[k<<1].Max[0] = tr[k<<1|1].Max[0] = 
			tr[k<<1].Llen[0] = tr[k<<1|1].Llen[0] = 
			tr[k<<1].Rlen[0] = tr[k<<1|1].Rlen[0] = 0;
			tr[k<<1].yes[0] = tr[k<<1|1].yes[0] = 0;
		}
		else
		{
			tr[k<<1].sum = tr[k<<1|1].sum = 0;
			tr[k<<1].Max[0] = tr[k<<1].Llen[0] = tr[k<<1].Rlen[0] =  mid - l + 1;
			tr[k<<1|1].Max[0] = tr[k<<1|1].Llen[0] = tr[k<<1|1].Rlen[0] = r - mid;
			tr[k<<1].yes[0] = tr[k<<1|1].yes[0] = 1;
			tr[k<<1].Max[1] = tr[k<<1|1].Max[1] = 
			tr[k<<1].Llen[1] = tr[k<<1|1].Llen[1] = 
			tr[k<<1].Rlen[1] = tr[k<<1|1].Rlen[1] = 0;
			tr[k<<1].yes[1] = tr[k<<1|1].yes[1] = 0;
		}
		tr[k].cover = -1;
		tr[k].rev = 0;
		return ;
	}
	if(tr[k].rev)
	{
		int len1 = mid - l + 1;
		int len2 = r - mid;
		tr[k<<1].sum = len1 - tr[k<<1].sum;
		tr[k<<1|1].sum = len2 - tr[k<<1|1].sum;
		swap(tr[k<<1].Max[0],tr[k<<1].Max[1]);
		swap(tr[k<<1|1].Max[0],tr[k<<1|1].Max[1]);
		swap(tr[k<<1].yes[1],tr[k<<1].yes[0]);
		swap(tr[k<<1|1].yes[1],tr[k<<1|1].yes[0]);
		swap(tr[k<<1].Llen[0],tr[k<<1].Llen[1]);
		swap(tr[k<<1].Rlen[0],tr[k<<1].Rlen[1]);
		swap(tr[k<<1|1].Llen[0],tr[k<<1|1].Llen[1]);
		swap(tr[k<<1|1].Rlen[0],tr[k<<1|1].Rlen[1]);
		if(tr[k<<1].cover != -1) tr[k<<1].cover = !tr[k<<1].cover;else tr[k<<1].rev ^= 1;
		if(tr[k<<1|1].cover != -1) tr[k<<1|1].cover = !tr[k<<1|1].cover; else tr[k<<1|1].rev ^= 1;
		tr[k].rev = 0;
	}
}

void change(int k,int L,int R,int x,int y,int val)
{
	down(k,L,R);
	if(L == x &&  R == y)
	{
		if(val == 1)
		{
			tr[k].Max[1] = tr[k].Llen[1] = tr[k].Rlen[1] = tr[k].sum = R - L + 1;
			tr[k].Max[0] = tr[k].Llen[0] = tr[k].Rlen[0] = 0;
			 tr[k].rev = 0; tr[k].cover = val;
			tr[k].yes[1] = 1,tr[k].yes[0] = 0;
			return;
		}
		else
		{
			tr[k].Max[0] = tr[k].Llen[0] = tr[k].Rlen[0] = R - L + 1;
			tr[k].Max[1] = tr[k].Llen[1] = tr[k].Rlen[1] = tr[k].sum = 0;
			tr[k].rev = 0,tr[k].cover = val;
			tr[k].yes[1] = 0, tr[k].yes[0] = 1;
			return;
		}
	}
	int mid = (L+R) >> 1;
	if(y <= mid) change(k<<1,L,mid,x,y,val);
	else if(x > mid)change(k<<1|1,mid+1,R,x,y,val);
	else change(k<<1,L,mid,x,mid,val),change(k<<1|1,mid+1,R,mid+1,y,val);
	updata(k);
}

void Rev(int k,int L,int R,int x,int y)
{
	down(k,L,R);
	if(L == x && R == y)
	{
		swap(tr[k].Max[0],tr[k].Max[1]);
		swap(tr[k].yes[0],tr[k].yes[1]);
		swap(tr[k].Llen[0],tr[k].Llen[1]);
		swap(tr[k].Rlen[0],tr[k].Rlen[1]);
		int tmp = R - L + 1;
		tr[k].sum = tmp - tr[k].sum;
		if(tr[k].cover != -1)
			tr[k].cover = ! tr[k].cover;
		else tr[k].rev = 1;
		return;
	}
	
	int mid = (L+R) >> 1;
	if(y <= mid) Rev(k<<1,L,mid,x,y);
	else if(x > mid) Rev(k<<1|1,mid+1,R,x,y);
	else Rev(k<<1,L,mid,x,mid),Rev(k<<1|1,mid+1,R,mid+1,y);
	updata(k);
}

int Ask_sum(int k,int l,int r,int x,int y)
{
	down(k,l,r);
	if(l==x && r==y)
		return tr[k].sum;

	int mid = (l+r) >> 1;
	if(y <= mid)
		return Ask_sum(k<<1,l,mid,x,y);
	else if(x > mid)return Ask_sum(k<<1|1,mid+1,r,x,y);
	else return Ask_sum(k<<1,l,mid,x,mid)+Ask_sum(k<<1|1,mid+1,r,mid+1,y);
}

Seg Ask_max(int k,int l,int r,int x,int y)
{
	down(k,l,r);
	if(l==x && r== y)
		return tr[k];
	int mid = (l+r) >> 1;
	if(y <= mid)return Ask_max(k<<1,l,mid,x,y);
	else if(x > mid) return Ask_max(k<<1|1,mid+1,r,x,y);
	else
	{
		Seg tmp1 = Ask_max(k<<1,l,mid,x,mid);
		Seg tmp2 = Ask_max(k<<1|1,mid+1,r,mid+1,y);
		Seg tmp;
		tmp.Llen[1] = tmp1.Llen[1];
		if(tmp1.yes[1]) tmp.Llen[1] += tmp2.Llen[1];
		
		tmp.Rlen[1] = tmp2.Rlen[1];
		if(tmp2.yes[1]) tmp.Rlen[1] += tmp1.Rlen[1];
		
		tmp.Max[1] = max(tmp1.Max[1],tmp2.Max[1]);
		tmp.Max[1] = max(tmp.Max[1],tmp1.Rlen[1] + tmp2.Llen[1]);
		
		tmp.yes[1] = tmp1.yes[1] & tmp2.yes[1];
		return tmp;
	}
}

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1) + (x<<3) + ch - '0';ch = getchar();}
	return x*f;
}

int main()
{
	int n = read(), m = read();
	for(int i=1;i<=n;++i) a[i] = read();
	build(1,1,n);
	while(m--)
	{
		int opt = read(),a = read()+1, b = read()+1;
		if(opt == 0 || opt == 1)
			change(1,1,n,a,b,opt);
		else if(opt == 2)
			Rev(1,1,n,a,b);
		else if(opt == 3)
			printf("%d\n",Ask_sum(1,1,n,a,b));
		else printf("%d\n",Ask_max(1,1,n,a,b).Max[1]);
	}
}
