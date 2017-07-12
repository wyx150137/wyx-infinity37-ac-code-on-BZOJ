
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int Len = 200000+5;
char s[Len];
int c[Len],sa[Len],val[Len],q[Len],newval[Len];
bool is_same(int a,int b,int hl,int len)
{
	return val[a]==val[b]&&((a+hl>len&&b+hl>len)||(a+hl<len&&b+hl<len&&val[a+hl]==val[b+hl]));
}
void build_sa(int len,int lim)
{
	int i,j,k;
	for(i = 0;i<lim;i++)c[i]=0;
	for(i = 0;i<len;i++)c[val[i]=s[i]]++;
	for(i = 1;i<lim;i++)c[i]+=c[i-1];
	for(i = len-1;i>=0;i--)sa[--c[val[i]]] = i;
	for(int d=1;;d++)
	{
		int hl = 1<<(d-1),id = 0;
		for(i = 0;i<len;i++)if(sa[i]+hl>=len)q[id++] = sa[i];
		for(i = 0;i<len;i++)if(sa[i]>=hl)q[id++] = sa[i]-hl;
		for(i = 0;i<lim;i++)c[i] = 0;
		for(i = 0;i<len;i++)c[val[q[i]]]++;
		for(i = 1;i<lim;i++)c[i]+=c[i-1];
		for(i = len-1;i>= 0;i--)sa[--c[val[q[i]]]] = q[i];
		lim = 0;
		for(i = 0;i<len;lim++)
		{
			for(j = i;j<len-1&&is_same(sa[j],sa[j+1],hl,len);j++);
			for(k = i,i = j+1;k<=j;k++)newval[sa[k]] = lim;
		}
		for(int i = 0;i<len;i++)val[i] = newval[i];
		if(lim==len)break;
	}
}
int main()
{
	scanf("%s",s);
	int len = strlen(s);
	for(int i = 0;i<len;i++)
		s[i+len] = s[i];
	build_sa(2*len,256);
	for(int i = 0;i< 2*len;i++)
		if(sa[i]<len)
			printf("%c",s[sa[i]+len-1]);
	return 0;
}
