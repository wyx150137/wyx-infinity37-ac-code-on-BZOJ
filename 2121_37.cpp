
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
int dp[155][35],f[155],p[155][35],len[35],bin[25],n,m;
bool ok[155][155];
char s[35][25],str[155];

int main()
{
	scanf("%s",str+1);
	m = strlen(str+1);
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
	{
		scanf("%s",s[i]+1);
		len[i] = strlen(s[i]+1);
	}
	bin[0] = 1;
	for(int i = 1;i<= 22;i++)
		bin[i] = bin[i-1]<<1;
	for(int i = 1;i<= m;i++)
		for(int j = 1;j<= n;j++)
			for(int k = 1;k<= len[j];k++)
				if(str[i]==s[j][k])
					p[i][j]|=bin[k];
	for(int i = m;i;i--)
	{
		for(int j = 1;j<= n;j++)dp[i-1][j] = 1;
		for(int j = i;j<= m;j++)
		for(int k = 1;k<= n;k++)
		{
			dp[j][k]=(dp[j-1][k]<<1)&p[j][k];
            for (int x=i; x<j; x++) if (ok[x+1][j]) dp[j][k]|=dp[x][k];
			if  (dp[j][k]&bin[len[k]]) ok[i][j]=1;
		}
	}
	for(int i = 1;i<= m;i++)
	{
		f[i] = f[i-1]+1;
		for(int j = 1;j<= i;j++)
			if(ok[j][i])
				f[i] = min(f[i],f[j-1]);
	}
	printf("%d\n",f[m]);
	return 0;
}
