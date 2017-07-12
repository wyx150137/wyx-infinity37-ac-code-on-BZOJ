
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int N = 6e4+5;
const int B = 305;
int c[N],sum[B][B],Sum[B][N];
int a[N],b[N],bel[N],bs[B],be[B],n,L,cnt,size;
int Find(int x)
{
	int l = 1,r = L+1;
	while(l<r)
	{
		int mid = (l+r)>>1;
		if(b[mid]<x)l=mid+1;
		else r = mid;
	}
	return l;
}
void update(int x,int y)
{
	for(int i = x;i<=n;i+=i&(-i))
		c[i]+=y;
}
int getans(int x)
{
	int ans = 0;
	for(int i = x;i>0;i-=i&(-i))
		ans+=c[i];
	return ans;
}
void Update(int id,int x,int y)
{
	for(int i = x;i<=cnt;i+=i&(-i))
		sum[id][i]+=y;
}
int Getans(int id,int x)
{
	int ans = 0;
	for(int i = x;i>0;i-=i&(-i))
		ans+=sum[id][i];
	return ans;
}
void UPDATE(int id,int x,int y)
{
	for(int i = x;i<=n;i+=i&(-i))
		Sum[id][i]+=y;
}
int GETANS(int id,int x)
{
	int ans = 0;
	for(int i = x;i>0;i-=i&(-i))
		ans+=Sum[id][i];
	return ans;
}
int ni[B];
int main()
{
	//freopen("noon.in","r",stdin);
	//freopen("noon.out","w",stdout);
	//freopen("x.in","r",stdin);
	scanf("%d",&n);
	size = floor(sqrt(n));
	for(int i = 1;i<= n;i+=size)
	{
		bs[++cnt]=i;be[cnt]=min(n,i+size-1);
		for(int j = bs[cnt];j<=be[cnt];j++)
			bel[j]=cnt;
	}
	for(int i =1;i<= n;i++)
		scanf("%d",&a[i]),b[i]=a[i];
	sort(b+1,b+n+1);
	for(int i = 1;i<= n;i++)
		if(b[i]!=b[L])
			b[++L]=b[i];
	for(int i = 1;i<= n;i++)a[i]=Find(a[i]);
	//for(int i = 1;i<= n;i++)printf("%d ",a[i]);
	//printf("\n");
	for(int i = 1;i<= cnt;i++)
	{
		for(int j = bs[i];j<=be[i];j++)
			update(a[j],1);
		for(int j = i+1;j<=cnt;j++)
		{
			int t = 0;
			for(int k = bs[j];k<=be[j];k++)
				t+=getans(n)-getans(a[k]);
			Update(i,j,t);
		}
		for(int j = bs[i];j<=be[i];j++)
			update(a[j],-1);
	}
	for(int i=1;i<=cnt;i++)
		for(int j = 1;j<=be[i];j++)
			UPDATE(i,a[j],1);
	for(int i = 1;i<= cnt;i++)
	{
		for(int j = bs[i];j<=be[i];j++)
		{
			ni[i]+=getans(n)-getans(a[j]);
			update(a[j],1);
			//if(i==1)printf("%d\n",ni[i]);
		}
		for(int j = bs[i];j<=be[i];j++)
			update(a[j],-1);
	}
	//for(int i = 1;i<= cnt;i++)
	//	printf("%d\n",ni[i]);
	int q,ans=0;
	scanf("%d",&q);
	while(q--)
	{
		int l,r,j,k;
		scanf("%d%d",&j,&k);
		j^=ans,k^=ans;
		ans = 0;
		l = bel[j],r=bel[k];
		if(r-l<=1)
		{
			for(int i = j;i<= k;i++)
			{
				ans+=getans(n)-getans(a[i]);
				update(a[i],1);
			}
			for(int i = j;i<=k;i++)
				update(a[i],-1);
		}else
		{
			for(int i = l+1;i<= r-1;i++)
			{
				ans+=ni[i];
				ans+=Getans(i,r-1)-Getans(i,i);
				//printf("%d\n",ans);
			}
			for(int i = j;i<=be[l];i++)
			{
				ans+=getans(n)-getans(a[i]);
				ans+=GETANS(r-1,a[i]-1)-GETANS(l,a[i]-1);
				update(a[i],1);
				//printf("%d\n",ans);
			}
			for(int i = bs[r];i<=k;i++)
			{
				ans+=getans(n)-getans(a[i]);
				ans+=GETANS(r-1,n)-GETANS(r-1,a[i])-GETANS(l,n)+GETANS(l,a[i]);
				update(a[i],1);
				//printf("%d\n",ans);
			}
			for(int i=j;i<=be[l];i++)update(a[i],-1);
			for(int i=bs[r];i<=k;i++)update(a[i],-1);
		}
		printf("%d\n",ans);
	}
	return 0;
}
