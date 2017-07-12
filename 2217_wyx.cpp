
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 1000000+5;
using namespace std;

int sum[N];
char str[N];
int ext[N];
int l[2*N],r[2*N];

char getc()
{
    static const int LEN = 1<<15;
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
	int n,m;
	cin >> n >> m;
	scanf("%s",str+1);
	register int  i = 1;
	for(i=1;i<=n;++i) sum[i] = sum[i-1] + (str[i] == 'W' ?  1 : 2);
	for(i=n;i;--i)
	{
		ext[i] = ext[i+1] + 1;
		if(str[i] == 'W') ext[i] = 0;
	}
	for(i=1;i<=n;++i)
	{
		l[sum[i]] = 1;
		r[sum[i]] = i;
		if(str[i] == 'T')
		{
			if(ext[1] < ext[i])
				l[sum[i]-1] = ext[1] + 2, r[sum[i]-1] = i + ext[1];
			else if(i+ext[i] <= n)
				l[sum[i]-1] = ext[i] + 1, r[sum[i]-1] = i + ext[i];
		}
	}
	for(i=1;i<=m;++i)
	{
		int x = read();
		if(!l[x])
			puts("NIE");
		else
			printf("%d %d\n",l[x],r[x]);
	}
}
