
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const double eps = 1e-5;
const double INF = 1e11;
const int N = 5e5+500;
struct Point
{
	double x,y;
	Point(){}
	Point(double _x,double _y):x(_x),y(_y){}
};
struct Qurey
{
	int type,id;
	Point a;
	double k;
	Qurey(){}
	Qurey(int _type,double _x,double _y,int _id):type(_type),id(_id)
	{
		a.x = _x,a.y = _y;
		if(fabs(a.y)<eps)
			k = INF;
		else 
			k = -a.x/a.y;
	}
	bool operator <(const Qurey &s)const
	{
		return k<s.k;
	}
}q[N],nq[N];
double Distance(const Point &a,const Point &b)
{
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
double Slope(const Point &a,const Point &b)
{
	if(fabs(a.x-b.x)<eps)
		return INF;
	return (b.y-a.y)/(b.x-a.x);
}
int n,cnt,stk1[N],stk2[N];
bool ap[N];
void solve(int l,int r)
{
	if(l==r)return ;
	int mid = (l+r)>>1;
	int l1 = l,l2 = mid+1;
	for(int i = l;i<= r;i++)
	{
		if(q[i].id<=mid)
			nq[l1++]=q[i];
		else 
			nq[l2++]=q[i];
	}
	memcpy(q+l,nq+l,sizeof(q[0])*(r-l+1));
	solve(l,mid);
	int top1 = 0,top2 = 0;
	for(int i = l;i<= mid;i++)
	{
		if(q[i].type==1)continue;
		while(top1>1 && Slope(q[stk1[top1-1]].a,q[i].a)+eps>Slope(q[stk1[top1-1]].a,q[stk1[top1]].a))
			top1--;
		stk1[++top1] = i;
		while(top2>1 && Slope(q[stk2[top2-1]].a,q[i].a)<Slope(q[stk2[top2-1]].a,q[stk2[top2]].a)+eps)
			top2--;
		stk2[++top2] = i;
	}
	int j = 1;
	for(int i = mid+1;i<= r;i++)
	{
		if(q[i].type==0)continue;
		if(q[i].a.y<eps)
		{
			while(top1>1&&Slope(q[stk1[top1-1]].a,q[stk1[top1]].a)<q[i].k)
				top1--;
			if(top1>0&&Distance(q[stk1[top1]].a,q[0].a)<Distance(q[stk1[top1]].a,q[i].a))
				ap[q[i].id]=false;
		}else
		{
			while (j<top2 && Slope(q[stk2[j]].a,q[stk2[j+1]].a)<q[i].k)
				j++;
            if (j<=top2 && Distance(q[stk2[j]].a,q[0].a)<Distance(q[stk2[j]].a,q[i].a)) 
            	ap[q[i].id]=false;
		}
	}
	solve(mid+1,r);
	l1 = l,l2 = mid+1;
	for (int i = l;i<= r;i++)
        if (l1<=mid && q[l1].a.x<q[l2].a.x || l2>r)
        	nq[i]=q[l1++]; 
        else nq[i]=q[l2++];
    for (int i=l; i<=r; i++) q[i]=nq[i];
}
bool cmp(const Qurey &a,const Qurey &b)
{
	return a.id<b.id;
}
int main()
{
	int type;
	double x,y;
	scanf("%d",&n);
	bool flag = false;
	q[0].a = Point(0,0);
	for(int i = 1;i<= n;i++)
	{
		scanf("%d%lf%lf",&type,&x,&y);
		q[i] = Qurey(type,x,y,i);
		if(!q[i].type)flag = true;
		ap[i]=flag;
	}
	sort(q+1,q+n+1);
	solve(1,n);
	sort(q+1,q+n+1,cmp);
	for(int i = 1;i<= n;i++)
		if(q[i].type)
			puts(ap[i]?"Yes":"No");
	return 0;
}
