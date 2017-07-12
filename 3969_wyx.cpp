
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#define M 1000000+10
using namespace std;

int a[M],n,m,k;

inline int read()
{
    int x=0,f=1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
    while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
    return x*f;
}	

bool check(int mid)
{
	int i;int cnt = 0;
	for(i=1;i<=m;++i)
	{
		if(i!=m&&a[i+1]-a[i]<=mid){cnt++,i++;continue;}
		if(i>2ll*cnt*k)return false;
	}
	return true;
}

int main()
{
	cin>>n>>k;
	m = n * k * 2;
	for(int i=1;i<=m;++i)
		a[i] =read();
	sort(a+1,a+m+1);
	int l = 0;
	int r = a[m]-a[1];
	while(l<r)
	{
		int mid = (l+r)>>1;
		if(check(mid))
			r = mid;
		else l = mid + 1;
	}
	printf("%d\n",check(l)?l:r);
}	
