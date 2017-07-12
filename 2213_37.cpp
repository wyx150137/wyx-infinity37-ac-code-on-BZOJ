
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int Q = 27;
const int N = 1e6+5;
int f[Q][Q],L[Q][Q],tot[Q],C[Q][Q],sec[Q][Q];
char s[N];
int ans;
void update(int x,int y)
{
	if(C[x][y]!=tot[y])ans = max(ans,f[x][y]-L[x][y]);
	else ans = max(ans,f[x][y]-sec[x][y]);
	if(f[x][y]<L[x][y])
	{
		if(C[x][y]==tot[y])L[x][y] = f[x][y];
		else
		{
			sec[x][y] = L[x][y];
			L[x][y] = f[x][y];
			C[x][y] = tot[y];
		}
	}else if(f[x][y]<sec[x][y])
		if(C[x][y]!=tot[y])
			sec[x][y] = L[x][y];
}
int main()
{
	int n;
	scanf("%d",&n);
	scanf("%s",s+1);
	memset(sec,0x3f,sizeof(sec));
	for(int i = 1;i<= n;i++)
	{
		s[i] = s[i]-'a';
		tot[s[i]]++;
		for(int j = 0;j<26;j++)
		{
			if(j==s[i])continue;
			f[j][s[i]]--;
			update(j,s[i]);
			f[s[i]][j]++;
			update(s[i],j);
		}
	}
	printf("%d\n",ans);
}
