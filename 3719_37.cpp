
#include <stdio.h>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
const int S = 1e6+5;
const int size = 1e6;
struct data
{
	int x1,y1,x2,y2;
	bool operator <(const data &s)const
	{
		if(x1==s.x1)
		{
			if(x2==s.x2)
			{
				if(y1==s.y1)return y1<s.y1;
				else return y2<s.y2;
			}else return x2<s.x2;
		}else return x1<s.x1;
	}
}s[N],Ans[N];
int fa[N],st[N];
int getfa(int x)
{
	if(fa[x]==x)return x;
	else return fa[x] = getfa(fa[x]);
}
void merge(int a,int b)
{
	int x = getfa(a),y = getfa(b);
	if(x==y)return ;
	s[a].x1 = min(s[a].x1,s[b].x1),s[a].x2 = max(s[a].x2,s[b].x2);
	s[a].y1 = min(s[a].y1,s[b].y1),s[a].y2 = max(s[a].y2,s[b].y2);
	fa[y] = a;
}
struct node{ vector<int>q1,q2;}tr[S<<2];
bool cmp(int a,int b)
{
	return s[a].y2==s[b].y2?a<b:s[a].y2<s[b].y2;
}
int sta[S],top;
void Insert(int p,int l,int r,int a,int b)
{
	if(l>=a&&r<=b){sta[++top]=p;return ;}
	int mid = (l+r)>>1;
	if(a<=mid)Insert(p<<1,l,mid,a,b);
	if(b >mid)Insert(p<<1|1,mid+1,r,a,b);
}
void update(int rt,int x)
{
	for(;rt;rt>>=1)tr[rt].q1.push_back(x);
}
int find_rt(int p,int l,int r,int x)
{
	if(l==r)return p;
	int mid = (l+r)>>1;
	if(x<=mid)return find_rt(p<<1,l,mid,x);
	else return find_rt(p<<1|1,mid+1,r,x);
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
	{
		scanf("%d%d%d%d",&s[i].x1,&s[i].x2,&s[i].y1,&s[i].y2);
		s[i].x1++,s[i].y1++;fa[i]=st[i]=i;
	}
	sort(st+1,st+n+1,cmp);
	for(int i = 1;i<= n;i++)
	{
		bool flag = true;
		while(flag)
		{
			top = 0;flag = false;
			Insert(1,1,size,s[st[i]].x1,s[st[i]].x2);
			for(int j = 1;j<= top;j++)
				for(int k = tr[sta[j]].q1.size()-1;k>=0;k--)
				{
					int y = tr[sta[j]].q1[k];
					if(fa[y]!=y||getfa(y)==getfa(st[i]))
						{tr[sta[j]].q1.pop_back();continue;}
					if(s[y].y2<s[st[i]].y1)break;
					merge(st[i],y);
					flag = true;
					tr[sta[j]].q1.pop_back();
				}
			for(int now = find_rt(1,1,size,s[st[i]].x1);now;now>>=1)
				for(int k = tr[now].q2.size()-1;k>=0;k--)
				{
					int y = tr[now].q2[k];
					if(fa[y]!=y||getfa(y)==getfa(st[i]))
						{tr[now].q2.pop_back();continue;}
					if(s[y].y2<s[st[i]].y1)break;
					merge(st[i],y);
					flag = true;
					tr[now].q2.pop_back();
				}
			for(int now = find_rt(1,1,size,s[st[i]].x2);now;now>>=1)
				for(int k = tr[now].q2.size()-1;k>=0;k--)
				{
					int y = tr[now].q2[k];
					if(fa[y]!=y||getfa(y)==getfa(st[i]))
						{tr[now].q2.pop_back();continue;}
					if(s[y].y2<s[st[i]].y1)break;
					merge(st[i],y);
					flag = true;
					tr[now].q2.pop_back();
				}
		}
		update(find_rt(1,1,size,s[st[i]].x1),st[i]);
		if(s[st[i]].x1!=s[st[i]].x2)
			update(find_rt(1,1,size,s[st[i]].x2),st[i]);
		top = 0;
		Insert(1,1,size,s[st[i]].x1,s[st[i]].x2);
		for(int j = 1;j<= top;j++)
			tr[sta[j]].q2.push_back(st[i]);
	}
	int ans = 0;
	for(int i = 1;i<= n;i++)
		if(fa[i]==i)
		{
			Ans[++ans] = s[i];
			Ans[ans].x1--,Ans[ans].y1--;
		}
	printf("%d\n",ans);
	sort(Ans+1,Ans+ans+1);
	for(int i = 1;i<= ans;i++)
		printf("%d %d %d %d\n",Ans[i].x1,Ans[i].x2,Ans[i].y1,Ans[i].y2);
	return 0;
}
