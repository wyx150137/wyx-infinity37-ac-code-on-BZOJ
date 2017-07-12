
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 2005;
bool a[N][N],b[N][N],vis[N],bo[N];
int stack[N],top,dfn[N],low[N],nxt[N],Dfn,dcc,bel[N],que[N],size[N],m,p[N],n;
bool ins[N];
void join(int x)
{
	vis[x]=true;
	for(int i = 1;i<= m;i++)if(a[que[i]][x])bo[que[i]]=true;
}
void work()
{
	int head=que[1],tail=que[1];
	int x,y,i,j;
	for(i = 2;i<= m;i++)
	{
		x = que[i];
		if(a[x][head])
		{
			nxt[x] = head;
			head = x;
			continue;
		}
		for(j=head,y=0;y!=tail&&a[j][x];y=j,j=nxt[j]);
		if(y==tail)
		{
			nxt[tail]=x;
			tail = x;
		}else
		{
			nxt[x] = j,nxt[y] = x;
		}
	}
	int mid = head;
	join(head);
	while(mid!=tail)
	{
		x = nxt[mid];
		if(a[x][head])
		{
			mid = x;join(x);
			continue;
		}
		for(i=head;i!=mid && a[i][x];j=i,i=nxt[i]);
		if(i!=mid)
		{
			nxt[j]=x,nxt[mid]=head;
			mid = x,head = i;join(x);
		}else
		{
			for(i = 1;i<= m;i++)if(!vis[que[i]] && bo[que[i]])break;
			for(j=head;j!=mid && a[j][que[i]];j = nxt[j]);
			for(y = nxt[mid];;y=nxt[y])
			{
				join(y);
				if(y==que[i])break;
			}
			nxt[mid] = head;head = j;mid = que[i];
			for(j=head,i=nxt[head];i!=head;j=i,i=nxt[i]);
			nxt[j] = x;
		}
	}
	for(int i = 1;i<= m;i++)bo[que[i]]=vis[que[i]]= false;
	nxt[tail]=head;
}
void tarjan(int x)
{
	dfn[x] = low[x] = ++Dfn;
	stack[++top] = x;
	ins[x] = true;
	for(int i = 1;i<=n;i++)if(a[x][i])
	{
		if(!dfn[i])
		{
			tarjan(i);
			low[x] = min(low[x],low[i]);
		}else if(ins[i])
			low[x] = min(low[x],dfn[i]);
	}
	if(dfn[x]==low[x])
	{
		dcc++;p[dcc]=x;
		int tmp;m=0;
		do
		{
			tmp = stack[top--];
			ins[tmp]=false;
			bel[tmp]=dcc;
			size[dcc]++;que[++m]=tmp;
		}while(tmp!=x);
		work();
	}
}
int f[N],g[N];
int dp(int x)
{
	if(f[x])return f[x];
	int y,z;
	for(y=1;y<=dcc;y++)if(b[x][y])
	{
		z=dp(y);
		if(z>f[x])
		{
			g[x] = y;
			f[x] = z;
		}
	}f[x]+=size[x];
	return f[x];
}
void print(int x)
{
	if(!x)return ;
	int y;printf(" %d",x);
	for(y =nxt[x];y!=x;y=nxt[y])
	{
		printf(" %d",y);
	}
	print(p[g[bel[x]]]);
}
int main()
{
	scanf("%d",&n);
	for(int j = 2;j<=n;j++)
		for(int i = 1;i<j;i++)
		{
			scanf("%d",&a[i][j]);
			a[j][i]=!a[i][j];
		}
	for(int i = 1;i<= n;i++)if(!dfn[i])tarjan(i);
	for(int i = 1;i<= n;i++)
		for(int j = 1;j<= n;j++)
			if(bel[i]!=bel[j])
				b[bel[i]][bel[j]]|=a[i][j];
	for(int i = 1;i<= dcc;i++)f[i]=dp(i);
	for(int i = 1;i<= n;i++)
	{
		printf("%d",f[bel[i]]);
		print(i);printf("\n");
	}
	return 0;
}
