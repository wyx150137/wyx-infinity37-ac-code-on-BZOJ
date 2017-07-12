
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define inf 0x7fffffff
using namespace std;
int n,k,cnt,ans=inf;
int head[65];
int next[1000005],v[1000005],a[1000005];
inline int read()
{
    char ch=getchar();
    int f=1,x=0;
    while(!(ch>='0'&&ch<='9')){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+(ch-'0');ch=getchar();}
    return x*f;
}
bool cal(int x)
{
	int mx=0;
	for(int i=1;i<=k;i++)
	{
		while(v[head[i]]>x)
		{
		    if(!next[head[i]])return 0;
			head[i]=next[head[i]];
			}
		if(v[head[i]]<=x)mx=max(mx,x-v[head[i]]);
	}
	ans=min(ans,mx);
	return 1;
}
int main()
{
	n=read();k=read();
	for(int i=1;i<=k;i++)
	{
		int x=read();
		for(int j=1;j<=x;j++)
		{
			int y=read();
			v[++cnt]=y;
			next[cnt]=head[i];
			head[i]=cnt;
			a[cnt]=y;
		}
	}
	sort(a+1,a+cnt+1);
	for(int i=cnt;i>0;i--)
	{
		if(a[i]!=a[i+1])
		if(!cal(a[i]))break;
	}
	printf("%d",ans);
	return 0;
}
