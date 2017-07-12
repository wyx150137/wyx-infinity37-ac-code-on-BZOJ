
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef unsigned long long ull;
const int sed = 37;
const int N = 1e5+5;
ull Pow[N],h1[N],h2[N];
char s1[N],s2[N];
int l1,l2,T,c;
void check(int l1,int r1,int l2,int r2)
{
	while(c<=3&&l1<=r1)
	{
		if(s1[l1]!=s2[l2])l1++,l2++,c++;
		else if(s1[r1]!=s2[r2])r1--,r2--,c++;
		else break;
	}
	if(l1>r1||c>3)return ;
	if(h1[r1]-h2[r2]==(h1[l1-1]-h2[l2-1])*Pow[r1-l1+1])return ;
	int d = (r1-l1)>>1;
	check(l1,l1+d,l2,l2+d);
	check(l1+d+1,r1,l2+d+1,r2);
}
void work()
{
	l1=strlen(s1+1);
	l2=strlen(s2+1);
	for(int i = 1;i<= l1;i++)h1[i]=h1[i-1]*sed+s1[i];
	for(int i = 1;i<= l2;i++)h2[i]=h2[i-1]*sed+s2[i];
	int ans = 0;
	for(int i = 1;i<= l1-l2+1;i++)
	{
		c = 0;
		check(i,i+l2-1,1,l2);
		if(c<=3)ans++;
	}
	printf("%d\n",ans);
}
int main()
{
	Pow[0] = 1;
	for(int i = 1;i<N;i++)Pow[i] = Pow[i-1]*sed;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%s%s",s1+1,s2+1);
		work();
	}
	return 0;
}
