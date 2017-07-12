
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
#define s(i) (s[i]-'a')
const int N = 1e5+5;
int ch[N][26],fail[N];
int sum[N],cnt;
char s[N];
void insert()
{
	int now = 0,i = 0;
	while(s[i])
	{
		if(!ch[now][s(i)])ch[now][s(i)] = ++cnt;
		now = ch[now][s(i)];
		i++;
	}
	sum[now]=i;
}
int q[N],h,t;
void build()
{
	h = 0,t = -1;
	for(int i = 0;i<26;i++)
		if(ch[0][i])
			q[++t]=ch[0][i];
	while(h<=t)
	{
		int x= q[h++];
		for(int i = 0;i<26;i++)
		{
			int j = ch[fail[x]][i];
			if(ch[x][i])
			{
				fail[ch[x][i]] = j;
				q[++t]=ch[x][i];
			}else
				ch[x][i] = j;
		}
	}
}
char str[N],st1[N];
int st2[N],top;
int main()
{
	scanf("%s",str);
	int n;
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
	{
		scanf("%s",s);
		insert();
	}
	build();
	int now = 0;
	for(int i = 0;str[i];i++)
	{
		st1[++top] = str[i];
		now = ch[now][str[i]-'a'];
		st2[top] = now;
		if(sum[now])
		{
			top-=sum[now];
			now = st2[top];
		}
	}
	for(int i = 1;i<= top;i++)printf("%c",st1[i]);
	return 0;
}
