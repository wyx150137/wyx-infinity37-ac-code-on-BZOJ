
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define LL long long
const int N  = 1000005;
using namespace std;


int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

int m,n,mx,tot,last[N];
LL cnt,ans[N];
bool lucky[N],used[N];

void solve()
{
	while(n--)
	{
		int x=read(),t=x;
		for(int j=last[x]+x,k=0;j<=mx;j+=x)
		{
			if(!used[j])
			{
				cnt++;t--;
				used[j]=1;k++;
				if(lucky[j])ans[++ans[0]]=cnt;
				if(k==x)break;
			}
			last[x]=j;
		}
		cnt+=t;
	}
}
int main()
{
	m=read();
	for(int i=1;i<=m;i++)
	{
		int x=read();
		lucky[x]=1;
		mx=max(mx,x);
	}
	n=read();
	solve();
	printf("%lld\n",ans[0]);
	for(int i=1;i<=ans[0];i++)
		printf("%lld\n",ans[i]);
	return 0;
}
