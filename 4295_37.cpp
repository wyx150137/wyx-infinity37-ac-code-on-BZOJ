
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
#define ll long long
#define inf 2000000000000000000ll
#define eps 1e-10
#define md
#define N 5000010
using namespace std;
const int D=2000000;
struct QQ { int dt,id;} q[N];
int a[N],b[N],r[N],sum[N],mn[N],T[N];
char st[N];
bool vis[N];
ll lun[N],ed[N],win[N],last[N];
int main()
{
	int n,m;
	scanf("%d",&n);
	for (int i=0;i<n;i++) scanf("%d",&a[i]);
	scanf("%d",&m); scanf("%s",st);
	for (int i=0;i<m;i++) b[i]=st[i]=='W'?1:-1;
	for (int i=0;i<m;i++)
		if (!vis[i])
		{
		int x=i,tot=0;
		while (!vis[x])
		{
			vis[x]=1; r[++tot]=x; sum[tot]=sum[tot-1]+b[x];
			x=(x+n)%m;
		}
		for (int j=1;j<=tot;j++)
		{
			r[j+tot]=r[tot];
			sum[j+tot]=sum[j+tot-1]+b[r[j]];
		}
		int h=1,w=0;
		for (int j=1;j<=tot;j++)
		{
			while (h<=w&&q[w].dt>=sum[j]) w--;
			q[++w].id=j; q[w].dt=sum[j];
		}
		for (int j=1;j<=tot;j++)
		{
			while (h<=w&&q[h].id<j) h++;
			mn[j]=-(q[h].dt-sum[j-1]);
			win[j]=sum[j+tot-1]-sum[j-1];
			while (h<=w&&q[w].dt>=sum[j+tot]) w--;
			q[++w].id=j+tot; q[w].dt=sum[j+tot];
		}
		for (int j=D-(tot<<1);j<=D+(tot<<1);j++) last[j]=inf;
		for (int j=(tot<<1);j>tot;j--)
			last[sum[j]+D]=j;
		for (int j=tot;j;j--)
		{
			x=r[j]; T[x]=tot;
			last[sum[j]+D]=j;
			while (x<n)
			{
				if (win[j]>=0&&a[x]>mn[j]) lun[x]=inf;
				else
				{
					if (a[x]<=mn[j]) lun[x]=0;
					else lun[x]=(a[x]-mn[j]-1)/(-win[j])+1;
					ed[x]=a[x]+lun[x]*win[j];
					ed[x]=last[-ed[x]+sum[j-1]+D]-(j-1);
				}
				x+=m;
			}
		}
	}
	ll ans=inf;
	for (int i=0;i<n;i++)
	{
		if (lun[i]==inf) continue;
		ans=min(ans,(lun[i]*T[i]+ed[i]-1)*n+i+1);
	}
	if (ans==inf) printf("-1\n");
		else printf("%lld\n",ans);
	return 0;
}
