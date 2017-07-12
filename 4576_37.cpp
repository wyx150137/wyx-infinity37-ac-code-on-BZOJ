
#include <stdio.h>
#include <cctype>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 262145;
int f[60][N];
char getc()
{
	static const int LEN = 4096;
	static char buf[LEN],*S=buf,*T=buf;
	if(S == T)
	{
		T = (S=buf)+fread(buf,1,LEN,stdin);
		if(S == T)return EOF;
	}
	return *S++;
}
int read()
{
	static char ch;
	static int D;
	while(!isdigit(ch=getc()));
	for(D=ch-'0'; isdigit(ch=getc());)
		D=(D<<3)+(D<<1)+(ch-'0');
	return D;
}
int main()
{
	int n,x,ans = 0;
	n=read();
	for(int i = 1;i<= n;i++){x=read();f[x][i] = i+1;}
	for(int i= 2;i<= 58;i++)
		for(int j = 1;j<= n;j++)
		{
			if(!f[i][j])f[i][j] = f[i-1][f[i-1][j]];
			if(f[i][j])ans = i;
		}
	printf("%d",ans);
	return 0;
}
