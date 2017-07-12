
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 100005;
int pre[N],fi[N],n,m;
struct E
{
	int x,y;
	E(int _x=0,int _y=0):x(_x),y(_y){}
	bool operator <(const E &s)const
	{
		if(x!=s.x)return x<s.x;
		return y<s.y;
	}
}e[N];
bool check(int x,int l,int r)
{
	if(x<=0)return false;
	for(int i = l+x;i<= r;i++)
	{
		if((i-l)%x!=pre[i]-l)return false;
		if(e[fi[i]].x==i&&e[fi[i]].y<l+x&&fi[i]<=m)return false;
	}
	return true;
}
bool judge(int l,int r)
{
	if(l==r)return true;
	int x=0;
	for(int i = l;i<= r;i++)
	{
		if(pre[i]>=l)continue;
		for(;fi[i]<=m&&e[fi[i]].x==i&&e[fi[i]].y<l;fi[i]++);
		if(fi[i]<=m&&e[fi[i]].x==i){pre[i]=e[fi[i]].y;++fi[i];}
	}
	pre[l] = l;
	for(int i = r;i>l;i--)
		if(pre[i]==l&&r-l+1>=(pre[i-1]-l+1)*2)
			{x = pre[i-1]-l+1;break;}
	if(!check(x,l,r)&&(r-pre[r])*2>=r-l+1&&pre[r]>=l)x = r-pre[r];
	if(check(x,l,r)&&judge(l,l+x-1)&&judge(l+x,r))return true;
	return false;
}
int main()
{
	int cas,x,y;
	scanf("%d",&cas);
	while(cas--)
	{
		scanf("%d%d",&n,&m);
		bool flag = false;
		for(int i = 1;i<= m;i++)
		{
			scanf("%d%d",&x,&y);
			if(x<y)swap(x,y);
			e[i] = E(x,y);
			if(x==y)flag = true;
		}
		if(flag){puts("NO");continue;}
		sort(e+1,e+m+1);
		for(int i = 0;i<n;i++)pre[i] = -1;
		int j = 1;
		for(int i = 0;i< n;i++)
		{
			fi[i] = j;
			for(;e[j].x==i&&j<=m;j++);
		}
		if(judge(0,n-1))puts("YES");
		else puts("NO");
	}
	return 0;
}
