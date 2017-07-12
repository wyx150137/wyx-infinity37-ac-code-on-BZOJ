
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 5001;
typedef long long ll;
int X[N*N],mp[N][N];
bool us[N][N];
int l[N],r[N],ans[N<<1],top;
int main()
{
	int a,b,c,d,n,m,q;
	scanf("%d%d%d%d%d",&X[0],&a,&b,&c,&d);
	scanf("%d%d%d",&n,&m,&q);
	int end = n*m;
	for(int i = 1;i<= end;i++)
		X[i] = ((ll)a*X[i-1]%d*X[i-1]%d+(ll)b*X[i-1]%d+c)%d;
	for(int i = 1;i<= end;i++)
		mp[(i-1)/m+1][(i-1)%m+1] = i;
	for(int i = 1;i<= end;i++)
	{
		int j = X[i]%i+1;
		swap(mp[(i-1)/m+1][(i-1)%m+1],mp[(j-1)/m+1][(j-1)%m+1]);
	}
	for(int t = 1;t<= q;t++)
	{
		int i,j;
		scanf("%d%d",&i,&j);
		swap(mp[(i-1)/m+1][(i-1)%m+1],mp[(j-1)/m+1][(j-1)%m+1]);
	}
	for(int i = 1;i<= n;i++)
		for(int j = 1;j<= m;j++)
			X[mp[i][j]] = (i-1)*m+j;
	for(int i = 1;i<= n;i++)l[i]=1,r[i]=m;
	for(int i = 1;i<= end;i++)
	{
		if(us[(X[i]-1)/m+1][(X[i]-1)%m+1])continue;
		ans[++top] = i;
		if(top>=n+m-1)break;
		int x = (X[i]-1)/m+1,y = (X[i]-1)%m+1;
		for(int j = x+1;j<= n;j++)
			for(int k = l[j];k<y;k++)us[j][k]=true,l[j]++;
		for(int j = x-1;j>=1;j--)
			for(int k = r[j];k>y;k--)us[j][k]=true,r[j]--;
	}
	for(int i = 1;i< top;i++)
		printf("%d ",ans[i]);
	printf("%d\n",ans[top]);
	return 0;
}
