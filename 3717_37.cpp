
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = (1<<24)+5;
int f[N],g[N];
int a[N],c[105];
bool cmp(const int &a,const int &b)
{
	return a>b;
}
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)scanf("%d",&a[i]);
	for(int i = 1;i<= m;i++)scanf("%d",&c[i]);
	for(int i = n;i;i--)a[1<<(i-1)]=a[i];
	sort(c+1,c+m+1,cmp);
	int end = (1<<n),tmp,x;
	for(int i = 1;i<end;i++)
	{
		f[i] = m+1,g[i] = -1;
		for(int j = i;j;j-=tmp)
		{
			tmp = j&(-j),x = i-tmp;
			if(a[tmp]<=g[x]&&(f[x]<f[i]||(f[x]==f[i]&&g[x]-a[tmp]>g[i])))f[i]=f[x],g[i]=g[x]-a[tmp];
			else if((f[x]+1<f[i]||(f[x]+1==f[i]&&c[f[x]+1]-a[tmp]>g[i]))&&c[f[x]+1]>=a[tmp])f[i]=f[x]+1,g[i]=c[f[x]+1]-a[tmp];
		}
	}
	if(f[end-1]>m)printf("NIE\n");
	else printf("%d\n",f[end-1]);
	return 0;
}
