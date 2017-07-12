
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int mod = 1e9+7;
const int S = 1<<10;
struct data
{
	int f;
	void operator +=(const data &s)
	{
		f = f+s.f>=mod?f+s.f-mod:f+s.f;
	}
	void operator -=(const data &s)
	{
		f = f-s.f>=0?f-s.f:f-s.f+mod;
	}
}f[2][S][S];
int a[S];
int main()
{
	int n;
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)scanf("%d",&a[i]),a[i] = (S-1)^a[i];
	int now = 1,pre = 0,i,j,k;
	f[0][0][0].f=1;
	for(i = 1;i<= n;i++)
	{
		for(j = 0;j<S;j++)
			for(k = j;;k = (k-1)&j)
			{
				f[now][j][k].f = 0;
				if(!k)break;
			}
		for(j = 0;j<S;j++)
			for(k = j;;k = (k-1)&j)
			{
				f[now][j|a[i]][k^(k&a[i])]+=f[pre][j][k];
				f[now][j|a[i]][k^(k&a[i])|a[i]^(a[i]&j)]-=f[pre][j][k];
				if(!k)break;
			}
		for(j = 0;j<S;j++)
			for(k = j;;k = (k-1)&j)
			{
				f[pre][j][k] += f[now][j][k];
				if(!k)break;
			}
		//swap(now,pre);
	}
	printf("%d\n",f[pre][S-1][0].f);
	return 0;
}
