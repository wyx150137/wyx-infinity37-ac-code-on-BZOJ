
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e6+5;
int a[N],ans[N],top;
int Q[N],P[N],hq,tq,hp,tp;
int main()
{
	int n,m,c;
	scanf("%d%d%d",&n,&m,&c);
	for(int i = 1;i<= n;i++)
		scanf("%d",&a[i]);
	hq = 0,tq = -1,hp = 0,tp = -1;
	//Q[0] = P[0] = 1;
	for(int i = 1;i<= n;i++)
	{
		while(hq<=tq&&a[Q[tq]]<=a[i])tq--;
		Q[++tq] = i;
		while(hp<=tp&&a[P[tp]]>=a[i])tp--;
		P[++tp] = i;
		while(hq<=tq&&Q[hq]<i-m+1)hq++;
		while(hp<=tp&&P[hp]<i-m+1)hp++;
		if(i>=m&&a[Q[hq]]-a[P[hp]]<=c)
			ans[++top] = i-m+1;
	}
	for(int i = 1;i<= top;i++)
		printf("%d\n",ans[i]);
	if(top==0)printf("NONE\n");
	return 0;
}
