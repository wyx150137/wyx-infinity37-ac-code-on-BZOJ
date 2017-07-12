
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int N = 1005;
const int M = 1<<16;
int cow[N];
int sta[M],cnt;
void init(int k)
{
	for(int i = 0;i<M;i++)
	{
		int tmp = i,c = 0;
		while(tmp)
		{
			tmp-=tmp&(-tmp);
			c++;
		} 
		if(c==k)
			sta[++cnt] = i;
	}
	return ;
}
int main()
{
	int n,d,k;
	scanf("%d%d%d",&n,&d,&k);
	init(k);
	for(int i = 1;i<= n;i++)
	{
		int c,x;
		scanf("%d",&c);
		for(int j = 1;j<= c;j++)
		{
			scanf("%d",&x);
			cow[i]|=(1<<(x-1));
		}
	}
	int t_ans = 0;
	for(int i= 1;i<= cnt;i++)
	{
		int ans = 0;
		for(int j = 1;j<= n;j++)
		{
			if((cow[j]|sta[i])!=sta[i])continue;
			else ans++;
		}
		t_ans = max(ans,t_ans);
	}
	printf("%d\n",t_ans);
	return 0;
}
