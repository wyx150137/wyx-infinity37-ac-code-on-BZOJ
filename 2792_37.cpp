
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int M = 1e6+5;
int x[M];
int c[M];
long long l[M],r[M];
int n;
LL m;
int check(int p)
{
	memcpy(c,x,sizeof(x));
	memset(l,0,sizeof(l));
	memset(r,0,sizeof(r));
	LL tot = 0;
	for(int i = 1;i<= n-1;i++)
		if(c[i+1]-c[i]>=p)
		{
			tot+=c[i+1]-c[i]-p;
			c[i+1] = c[i]+p;
		}
	//if(c[1]>c[2]+p){tot+=c[1]-c[2]-p;c[1] = c[2]+p;}
	if(tot>m)return -1;
	for(int i = n;i>= 2;i--)
		if(c[i-1]-c[i]>=p)
		{
			tot+=c[i-1]-c[i]-p;
			c[i-1] = c[i]+p;
		}
	//if(c[n]>c[n-1]+p){tot+=c[n]-c[n-1]-p;c[n] = c[n-1]+p;}
	if(tot>m)return -1;
	LL sum =0;
	int j = 1;
	for(int i = 1;i<= n;i++)
	{
		while((i-j)*p>c[j]&&j<i)
			{sum-=c[j];j++;}
		l[i]=sum-(LL)(i-j)*(i-j+1)/2*p;
		sum+=c[i];
	}
	sum =0,j = n;
	for(int i = n;i>= 1;i--)
	{
		while((j-i)*p>c[j]&&j>i)
			{sum-=c[j];j--;}
		r[i]=sum-(LL)(j-i)*(j-i+1)/2*p;
		sum+=c[i];
	}
	for(int i = 1;i<= n;i++)
		if(tot+l[i]+r[i]+c[i]<=m)
			return i;
	return -1;
}
int main()
{
	//freopen("stu.in","r",stdin);
	//freopen("stu.out","w",stdout);
	int maxn = 0;
	scanf("%d%lld",&n,&m);
	for(int i = 1;i<= n;i++)
	{
		scanf("%d",&x[i]);
		maxn = max(maxn,x[i]);
	}
	int L = 0,R = maxn+1;
	int ans = 1;
	while(L<R)
	{
		int mid = (L+R)>>1;
		int tmp = check(mid);
		if(tmp==-1)L = mid+1;
		else {ans = tmp;R = mid;}
	}
	printf("%d %d\n",ans,L);
	return 0;
}
