
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 5e5+5;
const int M = 4e6+5;
const double alpha = 0.81;
const int INF = 1e9+1;
struct P
{
	int mn[2],mx[2],d[2],l,r,sz;
	int& operator[](int x){return d[x];}
	P(int x,int y){l = r = 0;d[0] = x,d[1] = y;}
	P(){l=r=0;}
};
int D,pt[N];
int dcnt,tot;
namespace KD_tree
{
	P t[M];
	bool cmp(int a,int b)
	{
	return t[a][D]<t[b][D];
	}
	void update(int k)
	{
		P &l = t[t[k].l],&r = t[t[k].r];
		for(int i = 0;i<2;i++)
			t[k].mn[i] = t[k].mx[i] = t[k][i];
		for(int i = 0;i<2;i++)
		{
			if(t[k].l)t[k].mn[i] = min(t[k].mn[i],l.mn[i]);t[k].mx[i] = max(t[k].mx[i],l.mx[i]);
			if(t[k].r)t[k].mn[i] = min(t[k].mn[i],r.mn[i]);t[k].mx[i] = max(t[k].mx[i],r.mx[i]);
		}
		t[k].sz = l.sz+r.sz+1;
	}
	int NewPoint(int x,int y)
	{
		++dcnt;
		t[dcnt][0] = x;t[dcnt][1]= y;
		update(dcnt);
		return dcnt;
	}
	bool ned_rebuild(int k)
	{
		return max(t[t[k].l].sz,t[t[k].r].sz)>t[k].sz*alpha;
	}
	int query(int p,int x0,int y0,int x1,int y1)
	{
		if(!p||t[p].mn[0]>x1||t[p].mx[0]<x0||t[p].mn[1]>y1||t[p].mx[1]<y0)return 0;
		if(t[p].mn[0]>=x0&&t[p].mx[0]<=x1&&t[p].mn[1]>=y0&&t[p].mx[1]<=y1)return t[p].sz;
		int ans = 0;
		if(t[p][0]>=x0&&t[p][0]<=x1&&t[p][1]>=y0&&t[p][1]<=y1)ans++;
		return ans+query(t[p].l,x0,y0,x1,y1)+query(t[p].r,x0,y0,x1,y1);
	}
	int tmpx,tmpd,tmpf;
	void Insert(int &x,int now,const P &p)
	{
		if(!x){x = NewPoint(p.d[0],p.d[1]);return ;}
		if(p.d[now]>t[x][now])Insert(t[x].l,now^1,p);
		else Insert(t[x].r,now^1,p);
		update(x);
		if(ned_rebuild(x))tmpx = x,tmpd = now,tmpf = 0;
		else if(tmpx==t[x].l||tmpx==t[x].r)tmpf = x;
	}
	void travel(int &x)
	{
		if(!x)return ;
		pt[++tot] = x;
		travel(t[x].l),travel(t[x].r);
	}
	int build(int l,int r,int now)
	{
		if(l>r)return 0;
		int mid = (l+r)>>1,x;
		D = now;
		nth_element(pt+l,pt+mid,pt+r+1,cmp);
		x = pt[mid];
		t[x].l = build(l,mid-1,now^1);
		t[x].r = build(mid+1,r,now^1);
		update(x);
		return x;
	}
	void Insert(int &x,const P &p)
	{
		tmpx = tmpf = 0;
		Insert(x,0,p);
		if(!tmpx)return ;
		tot = 0,travel(tmpx);
		if(!tmpf){x = build(1,tot,tmpd);return ;}
		if(tmpx == t[tmpf].l)t[tmpf].l=build(1,tot,tmpd);
		else t[tmpf].r=build(1,tot,tmpd);
	}
}
struct Node
{int ls,rs,rt;}ti[M];
int ncnt,root;
void Insert(int &x,const P &p,int pos,int L = 1,int R = INF)
{
	if(!x)x = ++ncnt;
	KD_tree::Insert(ti[x].rt,p);
	if(L==R)return ;
	int mid = (L+R)>>1;
	if(pos<=mid)Insert(ti[x].ls,p,pos,L,mid);
	else Insert(ti[x].rs,p,pos,mid+1,R);
}
int query(int &x,int &x0,int &y0,int &x1,int &y1,int k,int L=1,int R=INF)
{
	if(L==R)return L;
	int rcnt = KD_tree::query(ti[ti[x].rs].rt,x0,y0,x1,y1);
	int mid = (L+R)>>1;
	if(k<=rcnt)return query(ti[x].rs,x0,y0,x1,y1,k,mid+1,R);
	else return query(ti[x].ls,x0,y0,x1,y1,k-rcnt,L,mid);
}
int n,q,ans;
int main()
{
	scanf("%d%d",&n,&q);
	int x0,y0,x1,y1,opt,k,tmp;
	for(int i = 1;i<= q;i++)
	{
		scanf("%d",&opt);
		if(opt==1)
		{
			scanf("%d%d%d",&x0,&y0,&k);
			x0 = x0^ans,y0 = y0^ans,k = k^ans;
			P p = P(x0,y0);
			Insert(root,p,k);
		}else
		{
			scanf("%d%d%d%d%d",&x0,&y0,&x1,&y1,&k);
			x0 = x0^ans,y0 = y0^ans,x1 = x1^ans,y1 = y1^ans,k = k^ans;
			tmp = KD_tree::query(ti[root].rt,x0,y0,x1,y1);
			if(tmp<k){printf("NAIVE!ORZzyz.\n");ans = 0;}
			else printf("%d\n",ans = query(root,x0,y0,x1,y1,k));
		}
	}
	return 0;
}
