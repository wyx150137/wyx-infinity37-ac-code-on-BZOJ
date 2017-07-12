
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 2e5+5;
struct Seg
{
	double sum_x,sum_y,sum_x2,sum_xy;
	double add_x,add_y;
	double cov_x,cov_y;
	bool cover;
}tr[N<<2];
double sum_pre[N<<2],vx[N<<2],vy[N<<2];
struct Res
{
	double sum_x,sum_y,sum_x2,sum_xy;
}res;
int n,m;
void Covers(int p,int l,int r,double S,double T)
{
	if(l>r)return ;
	double len = r-l+1;
	double sum = (l+r)*len/2;
	tr[p].add_x = tr[p].add_y = false;
	tr[p].cov_x = S,tr[p].cov_y = T;
	tr[p].cover = true;
	tr[p].sum_x2 = S*S*len+sum*S+sum*S+sum_pre[r]-sum_pre[l-1];
	tr[p].sum_xy = S*T*len+sum*S+sum*T+sum_pre[r]-sum_pre[l-1];
	tr[p].sum_x = (S+l+S+r)*len/2;
	tr[p].sum_y = (T+l+T+r)*len/2;
}
void Push_Down_cover(int p,int l,int r)
{
	if(l==r)return ;
	if(tr[p].cover)
	{
		int mid =(l+r)>>1;
		Covers(p<<1,l,mid,tr[p].cov_x,tr[p].cov_y);
		Covers(p<<1|1,mid+1,r,tr[p].cov_x,tr[p].cov_y);
		tr[p].cover = false;
	}
}
void Add(int p,int l,int r,double S,double T)
{
	if(l>r)return ;
	Push_Down_cover(p,l,r);
	double len = r-l+1;
	tr[p].add_x+=S,tr[p].add_y+=T;
	tr[p].sum_x2 += 2*S*tr[p].sum_x+S*S*len;
	tr[p].sum_xy += S*tr[p].sum_y+T*tr[p].sum_x+S*T*len;
	tr[p].sum_x+=S*len,tr[p].sum_y+=T*len;
}
void Push_Down_add(int p,int l,int r)
{
	if(l==r)return ;
	if(tr[p].add_x||tr[p].add_y)
	{
		int mid =(l+r)>>1;
		Add(p<<1,l,mid,tr[p].add_x,tr[p].add_y);
		Add(p<<1|1,mid+1,r,tr[p].add_x,tr[p].add_y);
		tr[p].add_x = tr[p].add_y = 0;
	}
}
void Push_Down(int p,int l,int r)
{
	Push_Down_add(p,l,r);
	Push_Down_cover(p,l,r);
}
void Push_Up(int p)
{
	int l = p<<1,r = p<<1|1;
	tr[p].sum_x = tr[l].sum_x+tr[r].sum_x;
	tr[p].sum_y = tr[l].sum_y+tr[r].sum_y;
	tr[p].sum_x2 = tr[l].sum_x2+tr[r].sum_x2;
	tr[p].sum_xy = tr[l].sum_xy+tr[r].sum_xy;
}
void Build(int p,int l,int r)
{
	if(l==r)
	{
		tr[p].sum_x = vx[l];
		tr[p].sum_y = vy[l];
		tr[p].sum_x2 = vx[l]*vx[l];
		tr[p].sum_xy = vx[l]*vy[l];
		return ;
	}
	int mid = (l+r)>>1;
	Build(p<<1,l,mid);
	Build(p<<1|1,mid+1,r);
	Push_Up(p);
}
void Covers(int p,int l,int r,int a,int b,double S,double T)
{
	Push_Down(p,l,r);
	if(l>=a&&r<=b)
	{
		Covers(p,l,r,S,T);
		return ;
	}
	int mid = (l+r)>>1;
	if(a<=mid)Covers(p<<1,l,mid,a,b,S,T);
	if(b >mid)Covers(p<<1|1,mid+1,r,a,b,S,T);
	Push_Up(p);
}
void Add(int p,int l,int r,int a,int b,double S,double T)
{
	Push_Down(p,l,r);
	if(l>=a&&r<=b)
	{
		Add(p,l,r,S,T);
		return ;
	}
	int mid = (l+r)>>1;
	if(a<=mid)Add(p<<1,l,mid,a,b,S,T);
	if(b >mid)Add(p<<1|1,mid+1,r,a,b,S,T);
	Push_Up(p);
}
void Getans(int p,int l,int r,int a,int b)
{
	Push_Down(p,l,r);
	if(l>=a&&r<=b)
	{
		res.sum_x+=tr[p].sum_x,res.sum_y+=tr[p].sum_y;
		res.sum_x2+=tr[p].sum_x2,res.sum_xy+=tr[p].sum_xy;
		return ;
	}
	int mid = (l+r)>>1;
	if(a<=mid)Getans(p<<1,l,mid,a,b);
	if(b >mid)Getans(p<<1|1,mid+1,r,a,b);
}

int main()
{
	for(int i = 1;i<N;i++)sum_pre[i] = sum_pre[i-1]+(double)i*i;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)scanf("%lf",&vx[i]);
	for(int i = 1;i<= n;i++)scanf("%lf",&vy[i]);
	Build(1,1,n);
	int opt,l,r;
	double s,t;
	while(m--)
	{
		scanf("%d%d%d",&opt,&l,&r);
		if(opt==1)
		{
			res.sum_x = res.sum_y = 0;
			res.sum_x2 = res.sum_xy = 0;
			Getans(1,1,n,l,r);
			double len = r-l+1;
			double averx = res.sum_x/len;
			double avery = res.sum_y/len;
			printf("%.10lf\n",(res.sum_xy-len*averx*avery)/(res.sum_x2-len*averx*averx));
		}else if(opt==2)
		{
			scanf("%lf%lf",&s,&t);
			Add(1,1,n,l,r,s,t);
		}else
		{
			scanf("%lf%lf",&s,&t);
			Covers(1,1,n,l,r,s,t);
		}
	}
	return 0;
}
