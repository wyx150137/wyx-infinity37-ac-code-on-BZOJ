
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 2505;
int n,m,ml,mw,s,tmp[N][N],f[2][N],L[2][N],R[2][N],l[N],r[N];
int mxc[N],mxr[N];
char str[N];
bool a[N][N];
void solve(int mxc[])
{
	for(int j = 1;j<= m;j++)
		L[0][j] = 0,R[0][j] = m+1,f[0][j] = 0;
	for(int i = 1,cur = 1;i<= n;i++)
	{
		l[0] = 0,r[m+1] = m+1;
		for(int j = m;j;j--)
			if(a[i][j])r[j]=r[j+1];
			else r[j]=j;
		for(int j = 1;j<= m;j++)
			if(a[i][j])
			{
				l[j] = l[j-1];
				f[cur][j] = f[cur^1][j]+1;
				L[cur][j] = max(L[cur^1][j],l[j]);
				R[cur][j] = min(R[cur^1][j],r[j]);
				int r = f[cur][j],c = R[cur][j]-L[cur][j]-1;
				mxc[r] = min(mxc[r],c);
				if(!a[i+1][j])
				{
					for(int p = r+1;p<= n;p++)
						if(mxc[p])
							mxc[p]=0;
						else break;
				}
			}else
				l[j] = j,f[cur][j]=L[cur][j]=0,R[cur][j]=m+1;
		cur^=1;
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)
	{
		scanf("%s",str+1);
		for(int j = 1;j<= m;j++)
			a[i][j]=str[j]=='X';
	}
	memset(mxc,0x3f,sizeof(mxc));
	memset(mxr,0x3f,sizeof(mxr));
	solve(mxc);
	for(int j = 1;j<= m;j++)
		for(int i = 1;i<= n>>1;i++)
			swap(a[i][j],a[n-i+1][j]);
	solve(mxc);
	for(int i = 1;i<= n;i++)
		for(int j = 1;j<= m;j++)
			tmp[j][i]=a[i][j],a[i][j]=false;
	for(int i = 1;i<= m;i++)
		for(int j = 1;j<= n;j++)
			a[i][j]=tmp[i][j];
	swap(n,m);
	solve(mxr);
	for(int j = 1;j<= m;j++)
		for(int i = 1;i<= n>>1;i++)
			swap(a[i][j],a[n-i+1][j]);
	solve(mxr);
	swap(n,m);
	mxr[0] = n+1;
	for(int i = n,j=1;j<= m;j++)
		for(;i>mxr[j];i--)
			mxc[i] = min(mxc[i],j-1);
	for(int i = 1;i<=n;i++)
		if(i*mxc[i]>s)
			s=i*mxc[i],ml=i,mw=mxc[i];
	printf("%d %d\n",ml,mw);
	return 0;
}
