
#include <stdio.h>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 6e6+5;
char s[100];
int ch[N][10],siz[N],cnt;
vector<int>num[N];
void Insert(int id)
{
	int now = 0,i = 1;
	while(s[i])
	{
		if(!ch[now][s[i]-'a'])ch[now][s[i]-'a'] = ++cnt;
		now = ch[now][s[i]-'a'];
		i++;
		siz[now]++;
		if(siz[now]>num[now].size())num[now].push_back(id);
	}
}
void Delete()
{
	int now = 0,i= 1;
	while(s[i])
	{
		now = ch[now][s[i]-'a'];
		siz[now]--;
		i++;
	}
}
int Find()
{
	int now = 0,i = 1;
	while(s[i])
	{
		now = ch[now][s[i]-'a'];
		i++;
	}
	return now;
}
int main()
{
	int n,k,a,b,c,lst=0;
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
	{
		scanf("%d",&k);
		if(k==3)
		{
			scanf("%s",s+1);
			scanf("%d%d%d",&a,&b,&c);
			a = ((ll)a*abs(lst)+b)%c;
			int pos = Find();
			if(num[pos].size()<=a)lst = -1;
			else lst = num[pos][a];
			printf("%d\n",lst);
		}else
		{
			scanf("%s",s+1);
			if(k==1)Insert(i);
			else Delete();
		}
	}
	return 0;
}
