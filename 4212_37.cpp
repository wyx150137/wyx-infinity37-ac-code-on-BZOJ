
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int Lth = 2000005;
const int N = 2005;
char s[Lth],s1[Lth],s2[Lth];
struct STR{int bg,ed;}str[N];
int trie[Lth][26],Max[Lth],Min[Lth],root[Lth],tot;
struct Trie
{
	int ch[Lth][26],sum[Lth],cnt;
	int insert(int id,int pre)
	{
		int tmp,y;
		tmp = y = ++cnt;
		for(int i = str[id].ed;i>=str[id].bg;i--)
		{
			for(int j = 0;j<26;j++)ch[y][j]=ch[pre][j];
			sum[y] = sum[pre]+1;
			int p = s[i]-'a';
			pre = ch[pre][p];
			ch[y][p] = ++cnt;
			y = ch[y][p];
		}
		sum[y] = sum[pre]+1;
		return tmp;
	}
	int getans(int L,int R,int lth)
	{
		for(int i = lth;i>=1;i--)
		{
			//fprintf(stderr, "%d %d\n",L,R);
			L = ch[L][s2[i]-'a'],R = ch[R][s2[i]-'a'];
		}
		return sum[R]-sum[L];
	}
}tr;
bool cmp(const STR &a,const STR &b)
{
	int p1 = a.bg,p2 = b.bg;
	while(p1<=a.ed&&p2<=b.ed)
	{
		if(s[p1]<s[p2])return true;
		else if(s[p1]>s[p2])return false;
		p1++,p2++;
	}
	if (p1<=a.ed) return 0;
	else if (p2<=b.ed) return 1;
	else return 0;
}
char tmp[Lth];
int main()
{
	//freopen("x.in","r",stdin);
	int n;
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
	{
		scanf("%s",tmp+1);
		str[i].bg = str[i-1].ed+1;
		str[i].ed = str[i].bg+strlen(tmp+1)-1;
		for(int j = str[i].bg;j<=str[i].ed;j++)s[j]=tmp[j-str[i].bg+1];
	}
	sort(str+1,str+n+1,cmp);
	for(int i = 1;i<= n;i++)
	{
		int now = 0;
		for(int j = str[i].bg;j<= str[i].ed;j++)
		{
			int p = s[j]-'a';
			if(!trie[now][p])trie[now][p] = ++tot;
			now = trie[now][p];
			if(Min[now]==0)Min[now] = i;
			Max[now] = max(Max[now],i);
		}
	}
	for(int i = 1;i<= n;i++)
		root[i] = tr.insert(i,root[i-1]);
	int ans = 0;
	int m;
	scanf("%d",&m);
	while(m--)
	{
		scanf("%s",s1+1);int lth1 = strlen(s1+1);
		scanf("%s",s2+1);int lth2 = strlen(s2+1);
		for(int i = 1;i<= lth1;i++)s1[i] = (s1[i]-'a'+ans)%26+'a';
		for(int i = 1;i<= lth2;i++)s2[i] = (s2[i]-'a'+ans)%26+'a';
		int now = 0,l = -1,r = -1;
		for(int i = 1;i<= lth1;i++)
		{
			int p = s1[i]-'a';
			if(!trie[now][p])break;
			now = trie[now][p];
			if(i==lth1){l=Min[now],r=Max[now];}
		}
		if(l==-1&&r==-1){ans = 0;printf("%d\n",ans);continue;}
		ans = tr.getans(root[l-1],root[r],lth2);
		printf("%d\n",ans);
	}
	return 0;
}
