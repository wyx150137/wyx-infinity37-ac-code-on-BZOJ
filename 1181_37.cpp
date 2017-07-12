
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 205;
const int INF = 1<<30;
int _a[N],a[N],b[N];
int s[N],ans[N];
bool cmp(int x,int y)
{
	return _a[x]>_a[y];
}
int f[2][N];
int V,n,m,tot;
bool check(int idx,int mid)
{
	for(int i = 0;i<= m;i++)
		f[0][i] = f[1][i] = INF;
	f[0][0] = 0;
	int now = 0;
	for(int i = 1;i<= min(n,21);i++)
	{
		if(i==idx)continue;
		for(int j = 0;j<= m;j++)
		{
			f[now^1][j] = INF;
			for(int k = 0;k<= j;k++)
			{
				int x = (a[idx]*k+mid)/(mid+1)-a[i];
				if(a[idx]*k%(mid+1)==0 && b[i]>b[idx] && k)
					x++;
				x = max(x,0);
				if (k && (a[i]+x)*20<V) 
					x+=(V+19-20*(a[i]+x))/20;
				f[now^1][j] = min(f[now^1][j],f[now][j-k]+x);
			}
		}
		now^=1;
	}
	return f[now][m-mid]<=V-tot;
}
int main()
{
	scanf("%d%d%d",&V,&n,&m);
	for(int i = 1;i<= n;i++)
	{
		scanf("%d",&_a[i]);
		b[i] = i;
		tot+=_a[i];
	}
	for(int i = 1;i<= n;i++)
	{
		_a[i]+=V-tot;
		for(int j = 1;j<= m;j++)
		{
			int mk = 0;
			for(int k = 1;k<= n;k++)
				if(_a[k]*20>=V&&(mk==0||_a[k]*(s[mk]+1)>_a[mk]*(s[k]+1)))
					mk = k;
			s[mk]++;
		}
		printf("%d",s[i]);
		if(i==n)printf("\n");else printf(" ");
		for(int j = 0;j<= n;j++)s[j]=0;
		_a[i]-=V-tot;
	}
	sort(b+1,b+n+1,cmp);
	for(int i = 1;i<= n;i++)a[i] = _a[b[i]];
	for(int i = 1;i<= n;i++)
	{
		if(a[i]*20<V){ans[b[i]]=0;continue;}
		int l = -1,r = m,mid;
		while(l+1<r)
		{
			mid = (l+r)>>1;
			if(check(i,mid))
				r = mid;
			else 
				l = mid;
		}
		ans[b[i]] = r;
	}
	for(int i = 1;i<= n;i++)
		printf("%d",ans[i]),printf("%c",i==n?'\n':' ');
	return 0;
}
