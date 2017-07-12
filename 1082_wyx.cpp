
#include <stdio.h>
#include <string.h>
#include <algorithm>
#define N 1000+5
#include <iostream>
using namespace std;
bool flag = false;
int n,a[N],b[N],m;
long long asum,bsum[N];
int bl[N];
int mid;

void DFS(int last,int x,int w)
{
	if(!x)
		flag=true;
	while(last<=n && a[last]<b[1])
		w+=a[last++];
	if(flag || last>n)return;
	if(w+bsum[mid]>asum)return;
	int tlast=last;
	int t1=last,t2=x,t3=w;
	if(b[x]==b[x+1] && x!=mid )tlast=bl[x+1];
	for(int i=tlast;!flag && i<=n;i++)
		if(a[i]>=b[x])
		{
			bl[x]=i;a[i]-=b[x];
			x--;
			DFS(last,x,w);
			last=t1;x=t2;w=t3;
			a[i]+=b[t2];
		}
}

int main()
{
	cin>>n;
	for(int i=1;i<=n;++i)
		scanf("%d",a+i);
	cin>>m;
	for(int i=1;i<=m;++i)
		scanf("%d",b+i);
	sort(a+1,a+n+1);
	sort(b+1,b+m+1);
	int tt = 0;
	while(b[m]>a[n])
		m--;
	for(int i=1;i<=n;++i)
		if(a[i]>b[1])
			a[++tt] = a[i];
	n = tt;
	for(int i=1;i<=n;++i)
		asum+=a[i];
	for(int i=1;i<=m;++i)
		bsum[i] = bsum[i-1]+b[i];
	int l = 1;
	int r = m + 1;
	while(l<r)
	{
		mid = (l+r)>>1;
		flag = false;
		DFS(1,mid,0);
		if(flag)
			l = mid + 1;
		else r = mid;
	}
	cout<<l-1;
}

