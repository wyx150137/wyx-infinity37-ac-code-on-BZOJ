
#include <stdio.h>
#include <math.h>
#include <bitset>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
int bel[N];
bitset<N>f,g;
struct Ask
{
	int opt,l,r,x,id;
	Ask(){}
	Ask(int _opt,int _l,int _r,int _x,int _id):opt(_opt),l(_l),r(_r),x(_x),id(_id){}
	bool operator<(const Ask &s)const 
	{
		if(bel[l]==bel[s.l])return r<s.r;
		return bel[l]<bel[s.l];
	}
}ask[N];
int cnt[N],ans[N],a[N];
void Del(int x)
{
	cnt[x]--;
	if(cnt[x]==0)f[x]=0,g[100000-x]=0;
}
void Add(int x)
{
	cnt[x]++;
	if(cnt[x]==1)f[x]=1,g[100000-x]=1;
}
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)scanf("%d",&a[i]);
	int bl = sqrt(n)+1;
	for(int i = 1;i<= n;i++)bel[i] = i/bl+1;
	for(int i = 1;i<= m;i++)
	{
		int l,r,opt,x;
		scanf("%d%d%d%d",&opt,&l,&r,&x);
		ask[i] = Ask(opt,l,r,x,i);
	}
	sort(ask+1,ask+m+1);
	int l = 0,r = 0;
	for(int i = 1;i<= m;i++)
	{
		while(l<ask[i].l)Del(a[l]),l++;
		while(l>ask[i].l)l--,Add(a[l]);
		while(r<ask[i].r)r++,Add(a[r]);
		while(r>ask[i].r)Del(a[r]),r--;
		if(ask[i].opt==1)
		{
			if(((f>>ask[i].x)&f).any())ans[ask[i].id] = 1;
			else ans[ask[i].id] =0;
		}
		else if(ask[i].opt==2)
		{
			if(((g>>(100000-ask[i].x))&f).any())ans[ask[i].id] = 1;
			else ans[ask[i].id] =0;
		}
		else
		{
			for(int j = 1;j*j<=ask[i].x;j++)
				if(ask[i].x%j==0)
					if(f[j]==1&&f[ask[i].x/j]==1)
						{ans[ask[i].id] = 1;break;}
			if(ask[i].x==0&&f[0]==1)
				ans[ask[i].id] = 1;
		}
	}
	for(int i= 1;i<= m;i++)
		if(ans[i])printf("yuno\n");
		else printf("yumi\n");
	return 0;
}
