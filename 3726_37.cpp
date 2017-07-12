
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 2005;
char s[N];
int l0[N],r0[N],l1[N],r1[N],a[N],b[N],nxt[N],pre[N],G[N],NXT[N];
int L[N],R[N],ans;
void add(int x,int y){NXT[y]=G[x];G[x]=y;}
void del(int x){nxt[pre[x]]=nxt[x];pre[nxt[x]]=pre[x];}
int main()
{
	int n,m,i,j;
	scanf("%d%d",&n,&m);
	for(i = 1;i<= m;i++)l0[i]=l1[i]=1,r0[i]=r1[i]=m;
	for(int T = 1;T<= n;T++)
	{
		scanf("%s",s+1);
		for(i=j=1;i<=m;i++)
			if(s[i]=='.')
			{
				a[i]++,b[i]++;
				if(l0[i]<j)l0[i]=j;
				if(l1[i]<j)l1[i]=j;
			}else
			{
				b[i]=a[i]+1,a[i]=0;
				l1[i]=l0[i],l0[i]=1;
				if(l1[i]<j)l1[i]=j;
				j=i+1;
			}
		for(i=j=m;i>=1;i--)
			if(s[i]=='.')
			{
				if(r0[i]>j)r0[i]=j;
				if(r1[i]>j)r1[i]=j;
			}else
			{
				r1[i]=r0[i],r0[i]=m;
				if(r1[i]>j)r1[i]=j;
				j=i-1;
			}
		for(i = 0;i<= T;i++)G[i]=0;
		for(i = m;i;i--)add(a[i],i),pre[i]=i-1,nxt[i]=i+1;
		for(pre[1]=0,nxt[m]=m+1,i=T;~i;i--)
			for(j=G[i];j;j=NXT[j])
				L[j]=pre[pre[j]],del(j);
		for(i = 0;i<= T;i++)G[i]=0;
		for(i = 1;i<=m;i++)add(a[i],i),pre[i]=i-1,nxt[i]=i+1;
		for(pre[1]=0,nxt[m]=m+1,i=T;~i;i--)
			for(j=G[i];j;j=NXT[j])
				R[j]=nxt[nxt[j]],del(j);
		for(i = 1;i<=m;i++)
		{
			ans = max(ans,(r1[i]-l1[i]+1)*b[i]);
			if(!a[i])continue;
			j = l0[i];
			if(j>1&&b[j-1]>=a[i]){if(L[i])j=L[i]+1;else j--;}
			ans = max(ans,(r0[i]-j+1)*a[i]);
			j = r0[i];
			if(j<m&&b[j+1]>=a[i]){if(R[i])j=R[i]-1;else j++;}
			ans = max(ans,(j-l0[i]+1)*a[i]);
		}
	}
	printf("%d\n",ans);
	return 0;
}
