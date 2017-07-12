
#include <stdio.h>
#include <math.h>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 3e5+5;
const int mx = 3e5;
int Tim,n,m,top,tp;
int cnt[N][4];
char s[N];
struct seg;
struct edge;
vector<edge*>now[N][4];
struct edge
{
	seg *pre,*nxt;
	inline void solve();
	inline void merge();
}List[N<<1];
struct seg
{
	int l,r,flag,h0,t0;
	edge *pre,*nxt;
	inline int calc()
	{return h0+cnt[Tim][flag]-cnt[t0][flag];}
	inline bool checka()
	{return pre&&pre->pre->calc()>calc();}
	inline bool checkb()
	{return nxt&&nxt->nxt->calc()>calc();}
	inline void update()
	{flag = checka()|(checkb()<<1);}
}list[N<<1],*last,*first;
inline void edge::solve()
{
	int delta = abs(pre->calc()-nxt->calc()),flag = pre->flag^nxt->flag;
	if(delta && flag && delta+cnt[Tim][flag]<=mx)
		now[delta+cnt[Tim][flag]][flag].push_back(this);
}
inline void edge::merge()
{
	if(!(pre&&nxt))return ;
	int h = pre->calc();
	if(nxt->calc()!=h)return ;
	seg* ret = pre;
	ret->l = pre->l,ret->r = nxt->r,ret->h0 = h,ret->t0 = Tim;
	ret->pre = pre->pre,ret->nxt = nxt->nxt,ret->update();
	if(ret->pre)ret->pre->nxt = ret;
	if(ret->nxt)ret->nxt->pre = ret;
	if(ret->pre)ret->pre->solve();
	if(ret->nxt)ret->nxt->solve();
	pre = NULL,nxt = NULL;
}

int main()
{
	int h;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)
	{
		scanf("%d",&h);
		if(last && last->h0==h)
			{last->r=i;continue;}
		++top;
		list[top].l = list[top].r = i;list[top].h0 = h,list[top].t0 = 0;
		if(last)
		{
			++tp;
			List[tp].pre = last,List[tp].nxt = &list[top];
			last->nxt = &List[tp];list[top].pre = &List[tp],last->update();
		}else first = &list[top];
		last = &list[top];
	}
	last->update();
	for(seg *i = first;i->nxt;i=i->nxt->nxt)
		i->nxt->solve();
	scanf("%s",s+1);
	for(Tim = 1;Tim<=m;Tim++)
	{
		cnt[Tim][1]=cnt[Tim-1][1]+(s[Tim]=='A'),cnt[Tim][2]=cnt[Tim-1][2]+(s[Tim]=='B');
		cnt[Tim][3]=cnt[Tim-1][3]+1;
		for(int f = 1;f<= 3;f++)
		{
			int sz = now[cnt[Tim][f]][f].size();
			for(int i = 0;i<sz;i++)now[cnt[Tim][f]][f][i]->merge();
		}
	}
	Tim = m;
	for (seg* i=first;i;i=i->nxt?i->nxt->nxt:NULL)
   	    for (int j=i->l;j<=i->r;++j)
        {
            if (j>1) putchar(' ');
            printf("%d",i->calc());
        }
    putchar('\n');
	return 0;
}
