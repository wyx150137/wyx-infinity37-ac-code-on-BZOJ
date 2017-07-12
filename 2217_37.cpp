
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 2e6+5;
int ansl[N],ansr[N];
char s[N>>1];
int ex2[N>>1];
int main()
{
	int n,q;
	scanf("%d%d",&n,&q);
	scanf("%s",s+1);
	int sum = 0;
	for(int i = 1;i<= n;i++)
	{
		sum+=s[i]=='W'?1:2;
		ansr[sum] = i;
		ansl[sum] = 1;
	}
	for(int i = n;i>=1;i--)
		if(s[i]=='T')
			ex2[i] = ex2[i+1]+1;
	for(int i = 1;i<= 2*n;i++)
	{
		if(i>sum)break;
		if(!ansl[i])
		{
			int tmp = ansr[i+1];
			if(ex2[1]<ex2[tmp])
			{
				ansr[i] = tmp+ex2[1];
				ansl[i] = 2+ex2[1];
				continue;
			}
			if(tmp+ex2[tmp]==n+1)continue;
			ansr[i] = tmp+ex2[tmp];
			ansl[i] = 1+ex2[tmp];
		}
	}
	int x;
	for(int i = 1;i<= q;i++)
	{
		scanf("%d",&x);
		if(!ansl[x])
			printf("NIE\n");
		else 
			printf("%d %d\n",ansl[x],ansr[x]);
	}
	return 0;
}
