
#include <iostream>
#include <cstdio>
#include <queue>
#include <stdlib.h>
#define N 1000010
using namespace std;
struct data
{
	int w,c;
};
int st,en;
bool operator <(const data &x,const data &y)
{
	if(x.w!=y.w) return x.w<y.w;
	if(x.c==en) return false;
	return true;
}

priority_queue<data>q;

void quit()
{
	puts("0");
	exit(0);
}

int ans[N];
int main()
{
	int n;
	scanf("%d%d%d",&n,&st,&en);
	int i,j,x,y,m=0;
	data t,tmp;
	for(i=1;i<=n;i++)
	{
		scanf("%d",&t.w);
		m+=t.w;
		t.c=i;
		if(i==st) t.w--;
		if(i==en) t.w--;
		if(t.w<0) quit();
		q.push(t);
	}
	ans[1]=st;ans[m]=en;
	bool f;
	for(i=2;i<m;i++)
	{
		t=q.top();f=false;
		q.pop();
		if(t.c==st)
		{
			tmp=t;
			if(!q.empty()) 
				t=q.top();
			else quit();
			q.pop();
			f=true;
		}
		st=ans[i]=t.c;
		if(t.w>1)
		q.push((data){t.w-1,t.c});
		if(f) q.push(tmp);
	}
	if(ans[m-1]==ans[m]) {puts("0");return 0;}
	for(i=1;i<=m;i++)
	printf("%d ",ans[i]);
	
}
