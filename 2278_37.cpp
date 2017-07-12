
#include <stdio.h>
#include <cctype>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int M = 2000010;
const int N = 100010;
char getc()
{
	static const int LEN = 4096;
	static char buf[LEN],*S=buf,*T=buf;
	if(S == T)
	{
		T = (S=buf)+fread(buf,1,LEN,stdin);
		if(S == T)return EOF;
	}
	return *S++;
}
inline int read()
{
	static char ch;
	static int D;
	while(!isdigit(ch=getc()));
	for(D=ch-'0'; isdigit(ch=getc());)
		D=(D<<3)+(D<<1)+(ch-'0');
	return D;
}
struct E
{
	int next,to;
}e[M];
int head[N],tot = 1;
vector<int>Ans[M];
void add(int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
}
bool used[M],ins[N],vis[N];
int stack[M],top,cnt,j;
void dfs(int x)
{
	vis[x] = true;
	if(ins[x])
	{
		cnt++;
		Ans[cnt].push_back(x);
		while(stack[top]!=x)
		{
			Ans[cnt].push_back(stack[top]);
			ins[stack[top]] = false;
			top--;
		}
		ins[stack[top]] = false;
		Ans[cnt].push_back(stack[top]);
		top--;
	}
	for(j = head[x];j;j = head[x])
	{
		head[x] = e[j].next;
		if(!used[j])
		{
			used[j] = used[j^1] = true;
			ins[x] = true;
			stack[++top] = x;
			dfs(e[j].to);
		}
	}
}
int d[N];
int main()
{
	int n,m;
	n = read();m = read();
	int x,y,u,w;
	for(int i = 1;i<= m;i++)
	{
		x = read();y = read();u = read();w = read();
		if(u==w)continue;
		d[x]++,d[y]++;
		add(x,y),add(y,x);
	}
	for(int i = 1;i<= n;i++)
		if(d[i]&1)
		{
			printf("NIE\n");
			return 0;
		}
	for(int i = 1;i<= n;i++)
		if(!vis[i])
			dfs(i);
	printf("%d\n",cnt);
	for(int i = 1;i<= cnt;i++)
	{
		printf("%d",Ans[i].size()-1);
		for(int k = 0;k<Ans[i].size();k++)
			printf(" %d",Ans[i][k]);
		printf("\n");
	}
	return 0;
}
