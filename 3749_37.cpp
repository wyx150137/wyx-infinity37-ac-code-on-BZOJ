
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e6+5;
int f[N][5],a[N],n,ans[N];
bool work(int u)
{
	memset(f,0,sizeof(f));
	f[1][u] = 1;
	for(int i = 2;i<= n;i++)
	{
		if(f[i-1][1]&&a[i-1]<=2*a[i])f[i][1] = 1;
		if(f[i-1][4]&&a[i-1]<=a[i])f[i][1] = 4;
		if(f[i-1][2]&&a[i-1]*2>=a[i])f[i][2] = 2;
		if(f[i-1][3]&&a[i-1]>=a[i])f[i][2] = 3;
		if(f[i-1][1]&&a[i-1]<=a[i])f[i][3] = 1;
		if(f[i-1][4]&&2*a[i-1]<=a[i])f[i][3] = 4;
		if(f[i-1][2]&&a[i-1]>=a[i])f[i][4] = 2;
		if(f[i-1][3]&&a[i-1]>=a[i]*2)f[i][4] = 3;
	}
	if(f[n][u]==0)return false;
	for(int i=n;i>=1;i--)
	{
        if(u==1)ans[i-1]=(i-1)%(n-1)+1;
        if(u==2)ans[i]=(i-1)%(n-1)+1;
        if(u==3)ans[i-1]=ans[i]=(i-1)%(n-1)+1;
        u=f[i][u];
    }
    for(int i = 1;i<n-1;i++)printf("%d ",ans[i]);
    printf("%d\n",ans[n-1]);
	return true;
}
int main()
{
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
		scanf("%d",&a[i]);
	a[++n] = a[1];
	for(int i = 1;i<=4;i++)if(work(i))return 0;
	printf("NIE\n");
	return 0;
}
