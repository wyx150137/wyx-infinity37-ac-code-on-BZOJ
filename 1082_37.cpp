
#include<cstdio>
#include<cmath>
#include<ctime>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>
#include<set>
#define ll long long
#define inf 1000000000
using namespace std;
int read()
{
	int f=1,x=0;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
bool flag;
int n,m,mid;
int a[55],b[1005],bl[1005];
ll sa;
int sb[1005];
void dfs(int ak,int bk,int w)
{
	if(bk==0)flag=1;
	while(ak<=n&&a[ak]<b[1]){w+=a[ak];ak++;}
	if(flag||ak>n)return;
	if(w+sb[mid]>sa)return;
	int t=ak,t1=ak,t2=bk,t3=w;
	if(b[bk]==b[bk+1]&&bk!=mid)t=bl[bk+1];
	for(int i=t;i<=n;i++)
		if(a[i]>=b[bk])
		{
			bl[bk]=i;a[i]-=b[bk];
			bk--;
			dfs(ak,bk,w);
			ak=t1;bk=t2;w=t3;a[i]+=b[t2];
		}
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	m=read();
	for(int i=1;i<=m;i++)b[i]=read();
	sort(a+1,a+n+1);
	sort(b+1,b+m+1);
	while(b[m]>a[n])m--;
	int tot=0;
	for(int i=1;i<=n;i++)	
		if(a[i]>b[1])a[++tot]=a[i];
	n=tot;
	for(int i=1;i<=n;i++)sa+=a[i];
	for(int i=1;i<=m;i++)sb[i]=sb[i-1]+b[i];
	int l=1,r=m,ans=0;
	while(l<=r)
	{
		mid=(l+r)>>1;
		flag=0;dfs(1,mid,0);
		if(flag)ans=mid,l=mid+1;
		else r=mid-1;
	}
	printf("%d\n",ans);
	return 0;
}
