
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;

const int N = 1e5+5;
const int M = 1e7+5;
int n,Ans1,Ans2,Maxx;
int A[N],B[N];
int p[M],v[M],vis[M],f[M];

inline void First()
{
	for(int i=2;i<=Maxx;i++)
	{
		if(!p[i]) p[++*p]=i,v[i]=*p;
		for(int j=1;j<=*p&&p[j]*i<=Maxx;j++)
		{
			p[p[j]*i]=1; v[p[j]*i]=j;
			if(i%p[j]==0) break;
		}
	}
}

int gcd(int x,int y)
{
	if(y==0)return x;
	return gcd(y,x%y);
}

int main()
{
	srand(2037);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&A[i]),Maxx=max(Maxx,A[i]);
	First();
	for(int K=1;K<=4;K++)
	{
		int x=A[rand()%n+1],cnt=0,w=0,Max=0,nAns=0;
		for(int i=1;i<=n;i++)
			if(A[i]!=x) B[++cnt]=A[i]<x?(x-A[i]):(A[i]-x);
			else w++;
		for(int i=1;i<=*p;i++) vis[i]=f[i]=0;
		for(int i=1;i<=cnt;i++)
		{
			int now=B[i];
			for(;now^1;now/=p[v[now]])
			{
				vis[v[now]]++;
				f[v[now]]=gcd(f[v[now]],B[i]);
				int y=p[v[now]];
				while((now/y)%y==0) now/=y;
			}
		}
		for(int i=1;i<=*p;i++)
			if(vis[i]>vis[Max]||(vis[i]==vis[Max]&&f[i]>nAns)) Max=i,nAns=f[i];
		if(vis[Max]+w>Ans1) Ans1=vis[Max]+w,Ans2=nAns;
		else if(vis[Max]+w==Ans1&&nAns>Ans2) Ans2=nAns;
	}
	printf("%d %d\n",Ans1,Ans2);
	return 0;
}
