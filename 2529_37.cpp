
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e6+5;
struct S
{int lth,col;}stick[N],a[4];
bool cmp(S a,S b)
{
	return a.lth<b.lth;
}
int main()
{
	int k,x,tot = 0;
	scanf("%d",&k);
	for(int i = 1;i<= k;i++)
	{
		scanf("%d",&x);
		for(int j = 1;j<= x;j++)
		{
			tot++;
			scanf("%d",&stick[tot].lth);
			stick[tot].col = i;
		}
	}
	sort(stick+1,stick+tot+1,cmp);
	for(int i = 1;i<= tot;i++)
	{
		int j;
		for(j = 1;j<= 3;j++)
			if(stick[i].col==a[j].col)
				{a[j] = stick[i];break;}
		if(j==4)a[1] = stick[i];
		sort(a+1,a+4,cmp);
		if(a[1].col!=0)
			if(a[1].lth+a[2].lth>a[3].lth)
			{
				printf("%d %d %d %d %d %d\n",a[1].col,a[1].lth,a[2].col,a[2].lth,a[3].col,a[3].lth);
				return 0;
			}
	}
	printf("NIE\n");
	return 0;
}
