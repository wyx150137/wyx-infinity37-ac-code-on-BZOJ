
#include <stdio.h>
#include <set>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
multiset<int>m;
int ans[305][305];
int t_ans[305];
int sum[90005],n,tot,cnt;
void getans(int sum3)
{
	m.clear();
	for(int i = 3;i<= tot;i++)
		m.insert(sum[i]);
	if((sum[1]+sum[2]+sum3)&1)return ;
	t_ans[1] = (sum[1]+sum[2]-sum3)>>1;
	t_ans[2] = (sum[1]+sum3-sum[2])>>1;
	t_ans[3] = (sum[2]+sum3-sum[1])>>1;
	if(t_ans[1]<=0||t_ans[2]<=0||t_ans[3]<=0)return ;
	m.erase(m.find(sum3));
	for(int i = 4;i<= n;i++)
	{
		t_ans[i] = *m.begin()-t_ans[1];
		if(t_ans[i]<=0)return ;
		for(int j = 1;j<i;j++)
		{
			int tmp = t_ans[j]+t_ans[i];
			if(m.find(tmp)==m.end())return ;
			m.erase(m.find(tmp));
		}
	}
	for(int i = 2;i<= n;i++)
		if(t_ans[i-1]>=t_ans[i])return ;
	cnt++;
	for(int i = 1;i<= n;i++)
		ans[cnt][i] = t_ans[i];
}
int main()
{
	scanf("%d",&n);
	tot = n*(n-1)/2;
	for(int i = 1;i<=tot;i++)
		scanf("%d",&sum[i]);
	sort(sum+1,sum+tot+1);
	for(int i = 3;i<= n;i++)
		if(i==3||sum[i]!=sum[i-1])
			getans(sum[i]);
	printf("%d\n",cnt);
	for(int i = 1;i<= cnt;i++)
	{
		for(int j = 1;j<=n;j++)
			printf("%d ",ans[i][j]);
		printf("\n");
	}
	return 0;
}
