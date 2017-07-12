
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
int gcd(int a,int b)
{
	if(!b)return a;
	else return gcd(b,a%b);
}
bool calc(int n,int p,int q)
{
	return n%p<q&&n%p%(p-q)==0;
}
int main()
{
	int cas;
	int p,q,n;
	scanf("%d",&cas);
	while(cas--)
	{
		scanf("%d%d%d",&p,&q,&n);
		int d = gcd(p,q);
		if(n%d){puts("R");continue;}
		p/=d,q/=d,n/=d;
		if(p==q)puts("E");
		else if(p>q)
		{
			if(n<p)puts("P");
			else puts(calc(n,p,q)?"E":"P");
		}else
		{
			if(n<p)
			{
				if(n+p<q)puts("E");
				else puts(calc(n+p,q,p)?"P":"E");
			}
			else puts("E");
		}
	}
}
