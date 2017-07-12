
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define N 10000+5
#define inf 0x7ffffff
using namespace std;

bool vis[N];
int tmp[N],a[N];
int len[N],MIN[N], sum[N];
int tt,n;
int pos[N];


inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch - '0';ch = getchar();}
	return x*f;
}

int find(int l,int r,int x)
{
	int mid = (l+r)>>1;
	if(tmp[mid] == x) 	return mid;
	if(tmp[mid] < x)	return find(mid+1,r,x);
	if(tmp[mid] > x)	return find(l,mid-1,x);
}

void Find_A_Circle(int x)
{	
	vis[x] = true;
	len[++tt] = 1;
	sum[tt] += a[x];
	MIN[tt] = min(MIN[tt],a[x]);
	int now = x;
	while(a[pos[now]]^a[x])
	{
		now = pos[now];
		vis[now] = 1;
		len[tt] ++;
		sum[tt] += a[now];
		MIN[tt] = min(MIN[tt],a[now]);
	}
}

int main()
{
	memset(MIN,0x7f,sizeof MIN);
	int MIN_NUM ;
	n = read();
	for(int i=1;i<=n;++i)
		a[i] = tmp[i] = read();
	sort(tmp+1,tmp+n+1);
	MIN_NUM = tmp[1];
	for(int i=1;i<=n;++i)
		pos[i] = find(1,n,a[i]);
	for(int i=1;i<=n;++i)
		if(!vis[i] && i^pos[i])
			Find_A_Circle(i);
	int ans = 0;
	for(int i=1;i<=tt;++i)
	{
		int tmp1 = (len[i]-2)*MIN[i];
		int tmp2 = MIN[i] + (len[i]+1)*MIN_NUM;
		ans += sum[i]+min(tmp1,tmp2);
	}
	cout<<ans;
}
